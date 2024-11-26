
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
	if (_C.GetVal() != 10)std::reverse(_C.GetCardGraphic(5).begin(), _C.GetCardGraphic(5).end());

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

	if (_CardIndex >= 10 || _Coins <= 0) { // If game has finished
		if ((_CardCount + _CardIndex) < PLAY_DECK_SIZE * Game::getInstance().GetGameConfig()._NumPlaySets) {
			_CardCount += _CardIndex;
			Reset_PlayCards();
		}
		else {
			// End the game
			Game::getInstance().SetScore(_Score);
			Game::getInstance().SetCoins(_Coins);
			Reset_PlayState();
			Game::getInstance().SwitchState(END_STATE);
		}
	}

	SetDirtyRender(true);
}

void PlayState::SpecificRender() {
	DrawGameScreen();
	SetDirtyRender(false);
}

void PlayState::DrawGameScreen() {
	if (Game::getInstance().GetGameConfig()._PWCoins) {
		wcout << CARD_INDENT << L"COINS : £ " << _Coins;
	}
	else {
		wcout << CARD_INDENT << L"SCORE : " << _Score;
	}
	wcout << endl << CARD_INDENT << L"CARD  : " << (_CardIndex + _CardCount) + 1 << " / " << PLAY_DECK_SIZE * Game::getInstance().GetGameConfig()._NumPlaySets << endl << BOARDER << endl;
	Draw_Card(Game::getInstance().GetCard(_randomIndex), 3); // Focus Card
	wcout << BOARDER << endl;
	Draw_Cards(_InPlay, 9, 5, 1); // Player's Cards
	SetOutPromt(_Result);
	if (Game::getInstance().GetGameConfig()._PWCoins && _Betting) {
		SetCmdPromt(L"How much would you like to bet? ( Number )");
	}
	else {
		SetCmdPromt(L"Higher or Lower? ( H / L )");
	}
}

int PlayState::GetDeckSize() { 
	return (MAX_DECK_SIZE - (2 * !Game::getInstance().GetGameConfig()._PWJokers)) - 1; 
}

bool PlayState::isNumber(string& _Str) {
	for (char const& c : _Str) {
		if (std::isdigit(c) == 0)
			return false;
	}

	return true;
}

void PlayState::UpdateScore(bool _Res, wstring _Input) {
	wstringstream _MSG;
	if (Game::getInstance().GetGameConfig()._PWCoins) {
		if (_Res) {
			_Coins += _NumBet * 2;
			_MSG << _InPlay[_CardIndex].GetVal() << _InPlay[_CardIndex].GetSuit() << L" CARD WAS " + _Input + L" THAN " <<
					Game::getInstance().GetCard(_randomIndex).GetVal() << Game::getInstance().GetCard(_randomIndex).GetSuit() << L"! +£" << _NumBet * 2 << L" COINS!";
		}
		else {
			_Coins -= _NumBet;
			_MSG << _InPlay[_CardIndex].GetVal() << _InPlay[_CardIndex].GetSuit() << L" CARD WAS NOT " + _Input + L" THAN " <<
				Game::getInstance().GetCard(_randomIndex).GetVal() << Game::getInstance().GetCard(_randomIndex).GetSuit() << L". -£" << _NumBet * 2 << L" COINS!";
		}
	}
	else {
		if (_Res) {
			_Score += 150;
			_MSG << _InPlay[_CardIndex].GetVal() << _InPlay[_CardIndex].GetSuit() << L" CARD WAS " + _Input + L" THAN " <<
				Game::getInstance().GetCard(_randomIndex).GetVal() << Game::getInstance().GetCard(_randomIndex).GetSuit() << L"! +150 POINTS";

		}
		else {
			_Score -= 100;
			_MSG << _InPlay[_CardIndex].GetVal() << _InPlay[_CardIndex].GetSuit() << L" CARD WAS NOT " + _Input + L" THAN " <<
				Game::getInstance().GetCard(_randomIndex).GetVal() << Game::getInstance().GetCard(_randomIndex).GetSuit() << L". -100 POINTS";
		}
	}
	_Result = _MSG.str();
}

bool PlayState::CheckInput(char _Input) {
	switch (_Input) {
	case 'H':
		UpdateScore(_InPlay[_CardIndex].GetVal() >= Game::getInstance().GetCard(_randomIndex).GetVal(), L"HIGHER");
		break;
	case 'L':
		UpdateScore(_InPlay[_CardIndex].GetVal() <= Game::getInstance().GetCard(_randomIndex).GetVal(), L"LOWER");
		break;
	default: 
		SetErrorPromt(DEFAULT_ERROR_MSG);
		return false; break;
	}

	_InPlay[_CardIndex++].SetFlipState(false);
	// Sets Focus card for next round
	_randomIndex = GetNewCardIndex();
	_Betting = true;
	return true;
}

bool PlayState::CheckBet(string _Bet) {
	wstringstream _MSG;
	if (isNumber(_Bet)) {
		_NumBet = atoi(_Bet.c_str());
		if (_NumBet >= 0 && _NumBet <= _Coins) {
			string s = _Bet + " BET PLACED.";
			wstring ws(s.begin(), s.end());
			_Result = L"£" + ws;
			_Betting = false;
			SetErrorPromt(L"");
			return true;
		}
		else {
			_MSG << L"Invalid bet, please place a bet between or equal to £0 & £" << _Coins;
		}
	}
	else {
		_MSG << L"Invalid bet, please input an integer number.";
	}
	SetErrorPromt(_MSG.str());

	return false;
}

int PlayState::GetNewCardIndex() {
	int _RandNum = 0;
	if (!Game::getInstance().GetGameConfig()._PWDuplicateCards) {
		do {
			int ds = GetDeckSize();
			_RandNum = randomNum(0, GetDeckSize());
		} while (Game::getInstance().GetCard(_RandNum).GetPlayedState() == true);
		Game::getInstance().GetCard(_RandNum).SetPlayedState(true);
	}
	else {
		_RandNum = randomNum(0, GetDeckSize());
	}

	return _RandNum;
}

void PlayState::Reset_PlayCards() {
	for (Card& _C : _InPlay) {
		// Set InPlay Cards
		_C = Game::getInstance().GetCard(GetNewCardIndex());
		_C.SetFlipState(true);
	}
	_CardIndex = 0;
}

ERROR_CODE PlayState::Reset_PlayState() {
	system("cls");

	_ValidInput = true;
	_GameIsSetup = false;
	_Score = 0;
	_CardCount = 0;

	if (Game::getInstance().GetGameConfig()._PWCoins) {
		SetErrorPromt(L"");
		_Coins = STARTING_COIN_COUNT;
		_NumBet = 0;
	}

	srand(time(0));
	_randomIndex = GetNewCardIndex();

	for (int i = 0; i < MAX_DECK_SIZE; ++i) 
		Game::getInstance().GetCard(i).SetFlipState(false);

	Reset_PlayCards();

	return GAME_OK;
}

ERROR_CODE PlayState::Draw_Card(Card _C, int _Indent) {
	for (int i = 0; i < CARD_GRAPHIC_SIZE; ++i) 
		wcout << centreString(_C.GetCardGraphic(i)) << endl;
	return GAME_OK;
}

ERROR_CODE PlayState::Draw_Cards(Card* _CardSet, int _C_Count, int _Columns, int _Indent) {
	int num = 0;

	if (_CardIndex >= PLAY_DECK_SIZE * 0.5f) _CurrentRow = 5;
	else _CurrentRow = 0;

	for (int i = 0; i < _C_Count; i + 0) { // for the number of cards
		for (int x = 0; x < CARD_GRAPHIC_SIZE + 1; ++x) { // for the number of graphics
			wstring _line = L"";
			num = 0;
			int _tIndex = 0;
			for (int j = 0; j < _Columns; ++j) { // for the number of columns
				_tIndex = i + num;
				if (x == 7) {
					// Draw Selector Row
					if ((_tIndex) == _CardIndex) _line += _Selector;
					else _line += _EmptySelector;
				}
				else {
					if (_CardSet[_tIndex].GetFlipState()) _line += _FaceDown.GetCardGraphic(x);
					else _line += _CardSet[_tIndex].GetCardGraphic(x);
				}
				++num;
			}

			if (x != 7 || (_tIndex) >= _CurrentRow && (_tIndex) < _CurrentRow + 5) {
				wcout << centreString(_line) << endl;
			}
		}
		i += num;
	}

	return GAME_OK;
}
