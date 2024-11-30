
#include "Game.h"
#include "States.h"

ERROR_CODE PlayState::Init() {
	// Initalise the Deck
	ui8 num = 1;
	ui8 suit_index = 0;

	for (int i = 0; i < MAX_DECK_SIZE; ++i) {
		Card temp_Card(SUITS[suit_index], num++);
		GenerateGraphics(temp_Card);
		Game::getInstance().SetCard(i, temp_Card);
		if (num > 13) {
			if (suit_index < 3) {
				num = 1;
				suit_index++;
			}
			else {
				num = 14;
				suit_index = 4;
			}
		}
	}

	for (int i = 0; i < CARD_GRAPHIC_SIZE; ++i) {
		_FaceDown.GetCardGraphic(i) = _FaceDownCard[i];
	}

	Reset_PlayState();

	return GAME_OK;
}

ERROR_CODE PlayState::GenerateGraphics(Card& _C) {
	wstringstream ss;
	wstringstream mSuit; // │    ♦    │
	wstringstream dSuit; // │  ♦   ♦  │

	mSuit << L"│    " << _C.GetSuit() << L"    │";
	dSuit << L"│  " << _C.GetSuit() << L"   " << _C.GetSuit() << L"  │";

	if (_C.GetVal() > 1 && _C.GetVal() <= 3) {
		ss << L"│" << _C.GetVal() << L"   " << _C.GetSuit() << L"    │";
	}
	else if (_C.GetVal() > 3 && _C.GetVal() < 10) {
		ss << L"│" << _C.GetVal() << L" " << _C.GetSuit() << L"   " << _C.GetSuit() << L"  │";
	}

	switch (_C.GetVal()) {
		case 1: ss << L"│A        │"; // Display value 1 cards as an ace
		case 3:
		case 5: _C.GetCardGraphic(3) = mSuit.str(); // Ace, 3 and 5 card have suit graphic in the centre of the card.
			break;
		case 8: _C.GetCardGraphic(2) = mSuit.str();
		case 7: _C.GetCardGraphic(4) = mSuit.str();
		case 6: _C.GetCardGraphic(3) = dSuit.str(); 
			break;
		case 9:
			_C.GetCardGraphic(2) = dSuit.str();
			_C.GetCardGraphic(3) = mSuit.str();
			_C.GetCardGraphic(4) = dSuit.str();
			break;
		case 10:
			ss << L"│" << _C.GetVal() << _C.GetSuit() << L"   " << _C.GetSuit() << L"  │";
			_C.GetCardGraphic(2) = dSuit.str();
			_C.GetCardGraphic(3) = dSuit.str();
			_C.GetCardGraphic(4) = dSuit.str();
			break;
		case 11: ss << L"│J " << _C.GetSuit() << L"   " << _C.GetSuit() << L"  │"; break; // Jack Card
		case 12: ss << L"│Q " << _C.GetSuit() << L"   " << _C.GetSuit() << L"  │"; break; // Queen Card
		case 13: ss << L"│K " << _C.GetSuit() << L"   " << _C.GetSuit() << L"  │"; break; // King Card
		case 14: ss << L"│J O K E R│"; break; // Joker Card
	}

	_C.GetCardGraphic(1) = ss.str();
	_C.GetCardGraphic(5) = _C.GetCardGraphic(1);
	if (_C.GetVal() != 10) {
		std::reverse(_C.GetCardGraphic(5).begin(), _C.GetCardGraphic(5).end()); 
	}
	else { 
		_C.GetCardGraphic(5)[1] = L' ';
		_C.GetCardGraphic(5)[2] = L' ';
		_C.GetCardGraphic(5)[8] = L'1';
		_C.GetCardGraphic(5)[9] = L'0';
	}

	return GAME_OK;
}

void PlayState::Update() {
	if (Game::getInstance().GetGameConfig()._PWCoins && _Betting) {
		string _Bet = "";
		cin >> _Bet;
		trim(_Bet);
		_ValidInput = CheckBet(_Bet);
	}
	else {
		BasicInput();
	}

	// If game has reached a finish state
	if (_CardIndex >= 10 || Game::getInstance().GetGameConfig()._PWCoins && _PlayerScore <= 0) {
		// If there are multiple rows used in the game
		if ((_CardCount + _CardIndex) < PLAY_DECK_SIZE * Game::getInstance().GetGameConfig()._NumPlaySets) {
			_CardCount += _CardIndex;
			Reset_PlayCards();
		}
		else {
			// End the game
			Game::getInstance().SetScore(_PlayerScore);
			Reset_PlayState();
			Game::getInstance().SwitchState(END_STATE);
		}
	}
}

void PlayState::SpecificRender() {
	if (Game::getInstance().GetGameConfig()._PWCoins) {
		wcout << CARD_INDENT << L"COINS : £ " << _PlayerScore << _RoundResult;
	}
	else {
		wcout << CARD_INDENT << L"SCORE : " << _PlayerScore << _RoundResult;
	}
	wcout << endl << CARD_INDENT << L"CARD  : " << (_CardIndex + _CardCount) + 1 << " / " << PLAY_DECK_SIZE * Game::getInstance().GetGameConfig()._NumPlaySets << endl << BOARDER << endl;
	Draw_Card(Game::getInstance().GetCard(_randomIndex)); // Focus Card
	wcout << BOARDER << endl;
	Draw_Cards(_InPlay, 9, 5); // Player's Cards
	SetOutPromt(_Result);
	if (!_Holding) {
		if (Game::getInstance().GetGameConfig()._PWCoins && _Betting) {
			SetCmdPromt(L"How much would you like to bet? ( Number )");
		}
		else {
			SetCmdPromt(L"Higher or Lower? ( H / L )");
		}
	}
	else {
		SetCmdPromt(L"Press 'E' to continue... ( E )");
	}
}

bool PlayState::CheckEqual(int _Val1, int _Val2) {
	wstringstream _MSG;
	wstringstream _ResMSG;
	if (_Val1 == _Val2) {
		if (Game::getInstance().GetGameConfig()._PWCoins) {
			_PlayerScore += _NumBet;
			_ResMSG << L"+ £" << _NumBet;
			_MSG << L"CARDS WERE EQUAL, RETURN BET";
			_RoundResult = _ResMSG.str();
		}
		else {
			_PlayerScore += 100;
			_RoundResult = L" +100";
			_MSG << L"CARDS WERE EQUAL +100 POINTS";
		}

		_Holding = true;
		_Result = _MSG.str();
		return true;
	}

	return false;
}

void PlayState::UpdateScore(bool _Res, wstring _Input) {
	wstringstream _MSG;
	wstringstream _ResMSG;
	if (Game::getInstance().GetGameConfig()._PWCoins) {
		if (_Res) {
			_Difference = _NumBet * 2;
			_ResMSG << L" + £" << _NumBet * 2;
			_MSG << INITALS[_InPlay[_CardIndex].GetVal()] << _InPlay[_CardIndex].GetSuit() << L" CARD WAS " + _Input + L" THAN " <<
				INITALS[Game::getInstance().GetCard(_randomIndex).GetVal()] << Game::getInstance().GetCard(_randomIndex).GetSuit() << L"! +£" << _NumBet * 2 << L" COINS!";
		}
		else {
			_Difference = -_NumBet;
			_ResMSG << L" - £" << _NumBet;
			_MSG << INITALS[_InPlay[_CardIndex].GetVal()] << _InPlay[_CardIndex].GetSuit() << L" CARD WAS NOT " + _Input + L" THAN " <<
				INITALS[Game::getInstance().GetCard(_randomIndex).GetVal()] << Game::getInstance().GetCard(_randomIndex).GetSuit() << L". -£" << _NumBet << L" COINS!";
		}
		_RoundResult = _ResMSG.str();
	}
	else {
		if (_Res) {
			_Difference = 150;
			_RoundResult = L" +150";
			_MSG << INITALS[_InPlay[_CardIndex].GetVal()] << _InPlay[_CardIndex].GetSuit() << L" CARD WAS " + _Input + L" THAN " <<
				INITALS[Game::getInstance().GetCard(_randomIndex).GetVal()] << Game::getInstance().GetCard(_randomIndex).GetSuit() << L"! +150 POINTS";
		}
		else {
			_Difference = -100;
			_RoundResult = L" -100";
			_MSG << INITALS[_InPlay[_CardIndex].GetVal()] << _InPlay[_CardIndex].GetSuit() << L" CARD WAS NOT " + _Input + L" THAN " <<
				INITALS[Game::getInstance().GetCard(_randomIndex).GetVal()] << Game::getInstance().GetCard(_randomIndex).GetSuit() << L". -100 POINTS";
		}
	}
	_Holding = true;
	_Result = _MSG.str();
}

bool PlayState::CheckInput(char _Input) {
	if (!_Holding) { // If the game state is not paused between rounds
		if (_InPlay[_CardIndex].GetVal() != 14) { // If Player Card is not a joker
			switch (_Input) { // <- HIGHER - LOWER - Playstate
			case 'H': // If the player selects HIGHER
				if (!CheckEqual(_InPlay[_CardIndex].GetVal(), Game::getInstance().GetCard(_randomIndex).GetVal())) {
					UpdateScore(_InPlay[_CardIndex].GetVal() >= Game::getInstance().GetCard(_randomIndex).GetVal(), L"HIGHER");
				}
				break;
			case 'L': // If the player selects LOWER
				if (!CheckEqual(_InPlay[_CardIndex].GetVal(), Game::getInstance().GetCard(_randomIndex).GetVal())) {
					UpdateScore(_InPlay[_CardIndex].GetVal() <= Game::getInstance().GetCard(_randomIndex).GetVal(), L"LOWER");
				}
				break;
			default:
				SetErrorPromt(DEFAULT_ERROR_MSG); // Set Default Error Promt
				return false; break;
			}
		}
		else { // If the player's card is a JOKER
			wstringstream _MSG;
			if (Game::getInstance().GetGameConfig()._PWCoins) {
				_PlayerScore += _NumBet * 2;
				_MSG << L"JOKER CARD PLAYED! BEATING ANY CARD! £" << _NumBet * 2 << L" COINS!";
			}
			else {
				_PlayerScore += 150;
				_MSG << L"JOKER CARD PLAYED! BEATING ANY CARD! +150 POINTS!";
			}
			_Holding = true;
			_Result = _MSG.str();
		}
		_InPlay[_CardIndex].SetFlipState(false);
	}
	else { 
		switch (_Input) { // <- HOLDING STATE (Between rounds)
		case 'E':
			++_CardIndex; // Switch to the new card in play
			_Holding = false; // Stop the holding phase
			_randomIndex = GetNewCardIndex(FOCUS_DECK_SIZE); // Get new random card for the computer card
			_Betting = true; // Switch back to the betting state (If playing with coins)
			_Result = L""; // Reset the Output Message
			_RoundResult = L""; // Reset the round specific message
			_PlayerScore += _Difference; // Add the round result score to the Player's score
			break;
		default:
			SetErrorPromt(DEFAULT_ERROR_MSG); // Set Default Error Promt
			return false; 
			break;
		}
	}

	return true;
}

bool isNumber(string& _Str) {
	for (char const& c : _Str) {
		if (std::isdigit(c) == 0) return false;
	}
	return true;
}

bool PlayState::CheckBet(string _Bet) {
	wstringstream _MSG;
	if (isNumber(_Bet)) {
		_NumBet = atoi(_Bet.c_str());
		if (_NumBet >= 0 && _NumBet <= _PlayerScore) {
			string s = _Bet + " BET PLACED.";
			wstring ws(s.begin(), s.end());
			_Result = L"£" + ws;
			_Betting = false;
			SetErrorPromt(L"");
			return true;
		}
		else {
			_MSG << L"Invalid bet, please place a bet between or equal to £0 & £" << _PlayerScore;
		}
	}
	else {
		_MSG << L"Invalid bet, please input an integer number.";
	}
	SetErrorPromt(_MSG.str());

	return false;
}

int PlayState::GetDeckSize() {
	return (MAX_DECK_SIZE - (2 * !Game::getInstance().GetGameConfig()._PWJokers)) - 1;
}

int PlayState::GetNewCardIndex(int _DeckSize) {
	int _RandNum = 0;
	if (!Game::getInstance().GetGameConfig()._PWDuplicateCards) { // If using a single deck
		do {
			_RandNum = randomNum(0, _DeckSize);
		} while (Game::getInstance().GetCard(_RandNum).GetPlayedState() == true);
		Game::getInstance().GetCard(_RandNum).SetPlayedState(true);
	}
	else { // If using duplicate cards
		_RandNum = randomNum(0, _DeckSize);
	}

	return _RandNum;
}

void PlayState::Reset_PlayCards() {
	int _DeckSize = GetDeckSize();
	for (Card& _C : _InPlay) {
		_C = Game::getInstance().GetCard(GetNewCardIndex(_DeckSize));
		_C.SetFlipState(true);
	}
}

ERROR_CODE PlayState::Reset_PlayState() {
	system("cls");

	_ValidInput = true;
	_GameIsSetup = false;
	_CardCount = 0;
	_CardIndex = 0;

	if (Game::getInstance().GetGameConfig()._PWCoins) {
		SetErrorPromt(L"");
		_PlayerScore = STARTING_COIN_COUNT;
		_NumBet = 0;
	}
	else {
		_PlayerScore = 0;
	}

	srand(time(0));
	_randomIndex = GetNewCardIndex(FOCUS_DECK_SIZE);

	for (int i = 0; i < MAX_DECK_SIZE; ++i) {
		Game::getInstance().GetCard(i).SetFlipState(false);
		Game::getInstance().GetCard(i).SetPlayedState(false);
	}

	Reset_PlayCards();

	return GAME_OK;
}

ERROR_CODE PlayState::Draw_Cards(Card* _CardSet, int _C_Count, int _Columns) {
	for (int i = 0; i < _C_Count; i += _Columns) { // For the number of cards
		for (int x = 0; x < CARD_GRAPHIC_SIZE; ++x) { // For each line in each card's graphic (+1 to include a selector line)
			wstring _line = L""; // Variable to align each card graphic segment onto a single line

			for (int j = 0; j < _Columns; ++j) { // for the number of columns
				if (_CardSet[i + j].GetFlipState()) _line += _FaceDown.GetCardGraphic(x);
				else _line += _CardSet[i + j].GetCardGraphic(x);
			}

			wcout << centreString(_line) << endl;
		}

		// Make selector line
		if (_CardIndex >= i && _CardIndex < (i + _Columns)) { // If card index is on the current Row
			wstring _SelSpace(11 * (_CardIndex - i) + 14, L' ');
			wcout << _SelSpace << _Selector << endl;
		}
	}

	return GAME_OK;
}