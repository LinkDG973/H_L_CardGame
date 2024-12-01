//===============================================================================
// NAME: PlayState.cpp
// DESC: Operates and Manages the Main Game
// AUTH: Oliver Callaghan
//===============================================================================
#include "Game.h"
#include "States.h"
//===============================================================================

// SUMMARY: Initalises the Deck and the Play State
// RETURNS: GAME_OK
ERROR_CODE PlayState::Init() {
	for (int i = 0; i < 4; ++i) { // For each SUIT
		for (int j = 0; j < 13; ++j) { // For each card belonging to the suit
			Card temp_Card(SUITS[i], j + 1); // Set card's suit and value
			GenerateGraphics(temp_Card); // Generate card's graphics 
			Game::getInstance().SetCard(j + (13 * i), temp_Card); // Update relative card in the game deck
		}
	}
	// Create and Initalise Joker Cards
	Card temp_Card(SUITS[4], 14);
	GenerateGraphics(temp_Card);
	Game::getInstance().SetCard(52, temp_Card);
	Game::getInstance().SetCard(53, temp_Card);
	Reset_PlayState(); // Reset the playstate to defaults

	return GAME_OK;
}

// SUMMARY: Generates the visuals for each card by it's value and suit.
// PARAMETERS: CARD - containing a suit and value.
// RETURNS: GAME_OK
ERROR_CODE PlayState::GenerateGraphics(Card& _C) {

	wstringstream mSuit; // │    ♦    │
	mSuit << L"│    " << _C.GetSuit() << L"    │";

	wstringstream dSuit; // │  ♦   ♦  │
	dSuit << L"│  " << _C.GetSuit() << L"   " << _C.GetSuit() << L"  │";

	wstringstream ss;

	if (_C.GetVal() == 2 || _C.GetVal() == 3) {
		ss << L"│" << _C.GetVal() << L"   " << _C.GetSuit() << L"    │";
	}
	else if (_C.GetVal() > 3 && _C.GetVal() < 10) {
		ss << L"│" << _C.GetVal() << L" " << _C.GetSuit() << L"   " << _C.GetSuit() << L"  │";
	}
	else if (_C.GetVal() == 10) ss << L"│10" << _C.GetSuit() << L"   " << _C.GetSuit() << L"  │"; // IF value 10

	switch (_C.GetVal()) {
		case 1: ss << L"│A        │"; // Display value 1 cards as an ace
		case 3:
		case 5: _C.GetCardGraphic(3) = mSuit.str(); // Ace (1), 3 and 5 card have suit graphic in the centre of the card.
			break;
		case 8: _C.GetCardGraphic(2) = mSuit.str();
		case 7: _C.GetCardGraphic(4) = mSuit.str();
		case 6: _C.GetCardGraphic(3) = dSuit.str(); 
			break;
		case 10:
		case 9:
			_C.GetCardGraphic(2) = dSuit.str();
			_C.GetCardGraphic(3) = mSuit.str();
			_C.GetCardGraphic(4) = dSuit.str();
			break;
		case 11: ss << L"│J " << _C.GetSuit() << L"   " << _C.GetSuit() << L"  │"; break; // Jack Card
		case 12: ss << L"│Q " << _C.GetSuit() << L"   " << _C.GetSuit() << L"  │"; break; // Queen Card
		case 13: ss << L"│K " << _C.GetSuit() << L"   " << _C.GetSuit() << L"  │"; break; // King Card
		case 14: ss << L"│J O K E R│"; break; // Joker Card
	}

	_C.GetCardGraphic(1) = ss.str();
	_C.GetCardGraphic(5) = _C.GetCardGraphic(1);
	std::reverse(_C.GetCardGraphic(5).begin(), _C.GetCardGraphic(5).end());
	if (_C.GetVal() == 10) {
		_C.GetCardGraphic(3) = dSuit.str();
		_C.GetCardGraphic(5).replace(8,9,L"10│");
	}

	return GAME_OK;
}

// SUMMARY: Main Game Update Function
// RETURNS: VOID
void PlayState::Update() {
	if (G_Conf._PWCoins && _Betting) { // Betting inputs
		string _Bet = "";
		cin >> _Bet;
		_ValidInput = CheckBet(trim(_Bet));
	}
	else BasicInput(); // Basic Input Function

	// If game has reached a finish state
	if (_CardIndex >= 10 || G_Conf._PWCoins && G_Conf._Score <= 0) {
		// If there are multiple rows used in the game
		if ((_CardCount + _CardIndex) < PLAY_DECK_SIZE * G_Conf._NumPlaySets) {
			_CardCount += _CardIndex;
			Reset_PlayCards();
		}
		else { // End the game
			Reset_PlayState();
			Game::getInstance().SwitchState(END_STATE);
		}
	}
}

// SUMMARY: Play State Rendering Function
// RETURNS: VOID
void PlayState::SpecificRender() {
	if (G_Conf._PWCoins) wcout << CARD_INDENT << L"COINS : £ " << G_Conf._Score << _RoundResult;
	else wcout << CARD_INDENT << L"SCORE : " << G_Conf._Score << _RoundResult;
	wcout << endl << CARD_INDENT << L"CARD  : " << (_CardIndex + _CardCount) + 1 << " / " << PLAY_DECK_SIZE * G_Conf._NumPlaySets << endl << BOARDER << endl;

	Draw_Card(Game::getInstance().GetCard(_randomIndex)); // Focus Card
	wcout << BOARDER << endl;
	Draw_Cards(_InPlay, 9, 5); // Player's Cards
	SetOutPromt(_Result);

	if (!_Holding) {
		if (G_Conf._PWCoins && _Betting) SetCmdPromt(L"How much would you like to bet? ( Number )");
		else SetCmdPromt(L"Higher or Lower? ( H / L )");
	}
	else SetCmdPromt(L"Press 'E' to continue... ( E )");
}

// SUMMARY: Checks if card values are equal
// PARAMETERS: INT - Player Card Value, INT - Computer Card Value
// RETURNS: BOOL - Equal Result
bool PlayState::CheckEqual(int _Val1, int _Val2) {
	wstringstream _MSG;
	wstringstream _ResMSG;
	if (_Val1 == _Val2) {
		if (G_Conf._PWCoins) {
			G_Conf._Score += _NumBet;
			_ResMSG << L"+ £" << _NumBet;
			_MSG << L"CARDS WERE EQUAL, RETURN BET";
			_RoundResult = _ResMSG.str();
		}
		else {
			G_Conf._Score += 100;
			_RoundResult = L" +100";
			_MSG << L"CARDS WERE EQUAL +100 POINTS";
		}

		_Holding = true;
		_Result = _MSG.str();
		return true;
	}

	return false;
}

// SUMMARY: Updates Score and Develops an output message relative to the rounds result 
// PARAMETERS: BOOL - Round Result (Win/Lose), WSTRING - String of which input was selected (Higher/Lower)
// RETURNS: VOID
void PlayState::UpdateScore(bool _Res, wstring _Input) {
	wstringstream _MSG;
	_MSG << INITALS[_InPlay[_CardIndex].GetVal()] << _InPlay[_CardIndex].GetSuit() << L" CARD WAS ";
	if (!_Res) _MSG << L"NOT";
	_MSG << _Input + L" THAN " << INITALS[Game::getInstance().GetCard(_randomIndex).GetVal()] << Game::getInstance().GetCard(_randomIndex).GetSuit() << L"!";

	wstringstream _ResMSG;
	if (G_Conf._PWCoins) {
		if (_Res) {
			_Difference = _NumBet * 2;
			_ResMSG << L" + £" << _Difference << L" COINS!";
		}
		else {
			_Difference = -_NumBet;
			_ResMSG << L" - £" << _NumBet << L" COINS!";;
		}
	}
	else {
		if (_Res) {
			_Difference = 150;
			_ResMSG << L" + 150 POINTS!";
		}
		else {
			_Difference = -100;
			_ResMSG << L" - 100 POINTS!";
		}
	}

	_RoundResult = _ResMSG.str();
	_Holding = true;
	_Result = _MSG.str() + _ResMSG.str();
}

// SUMMARY: Main Input Function For Play State, switches dependent on the progression of the game.
// PARAMETERS: CHAR - Player's input character commmand.
// RETURNS: BOOL - If the input was valid or not.
bool PlayState::CheckInput(char _Input) {
	if (!_Holding) { // If the game state is not paused between rounds
		if (_InPlay[_CardIndex].GetVal() != 14) { // If Player Card is not a JOKER
			switch (_Input) { // <- HIGHER - LOWER - Playstate
			case 'H': // If the player selects HIGHER
				if (!CheckEqual(_InPlay[_CardIndex].GetVal(), Game::getInstance().GetCard(_randomIndex).GetVal()))
					UpdateScore(_InPlay[_CardIndex].GetVal() >= Game::getInstance().GetCard(_randomIndex).GetVal(), L"HIGHER");
				break;
			case 'L': // If the player selects LOWER
				if (!CheckEqual(_InPlay[_CardIndex].GetVal(), Game::getInstance().GetCard(_randomIndex).GetVal()))
					UpdateScore(_InPlay[_CardIndex].GetVal() <= Game::getInstance().GetCard(_randomIndex).GetVal(), L"LOWER");
				break;
			default:
				SetErrorPromt(DEFAULT_ERROR_MSG); // Set Default Error Promt
				return false; break;
			}
		}
		else { // If the player's card is a JOKER
			wstringstream _MSG;
			if (G_Conf._PWCoins) {
				G_Conf._Score += _NumBet * 2;
				_MSG << L"JOKER CARD PLAYED! BEATING ANY CARD! + £" << _NumBet * 2 << L" COINS!";
			}
			else {
				G_Conf._Score += 150;
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
			G_Conf._Score += _Difference; // Add the round result score to the Player's score
			break;
		default:
			SetErrorPromt(DEFAULT_ERROR_MSG); // Set Default Error Promt
			return false; break;
		}
	}
	return true;
}

// SUMMARY: Checks if the input string only contains numeric digits.
// PARAMETERS: STRING - Player Input
// RETURNS: BOOL - Result of Check
bool isNumber(string& _Str) {
	for (char const& c : _Str) if (std::isdigit(c) == 0) return false;
	return true; // If String only contains numeric digits.
}

// SUMMARY: Checks the player's bet input and passes if valid.
// PARAMETERS: STRING - Player's Bet
// RETURNS: BOOL - Validation Result
bool PlayState::CheckBet(string _Bet) {
	wstringstream _MSG;
	if (isNumber(_Bet)) {
		_NumBet = atoi(_Bet.c_str());
		if (_NumBet >= 0 && _NumBet <= G_Conf._Score) {
			string s = _Bet + " BET PLACED.";
			wstring ws(s.begin(), s.end());
			_Result = L"£" + ws;
			_Betting = false;
			SetErrorPromt(L"");
			return true;
		}
		else _MSG << L"Invalid bet, please place a bet between or equal to £0 & £" << G_Conf._Score;
	}
	else _MSG << L"Invalid bet, please input an integer number.";
	SetErrorPromt(_MSG.str());

	return false;
}

// SUMMARY: Returns the Size of the Deck relative to if JOKERS are in play.
// RETURNS: INT - Size of Deck under current settings
int PlayState::GetDeckSize() {
	return (MAX_DECK_SIZE - (2 * !G_Conf._PWJokers)) - 1;
}

// SUMMARY: Returns Random index from cards that have not been played yet. (Unless using duplicate cards).
// PARAMETERS: INT - Size of Current Deck.
// RETURNS: INT - Random Index of Card.
int PlayState::GetNewCardIndex(int _DeckSize) {
	int _RandNum = 0;
	if (!G_Conf._PWDuplicateCards) { // If using a single deck
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

// SUMMARY: Resets the Player's selection of cards and the current card index.
// RETURNS: VOID
void PlayState::Reset_PlayCards() {
	int _DeckSize = GetDeckSize();
	for (Card& _C : _InPlay) {
		_C = Game::getInstance().GetCard(GetNewCardIndex(_DeckSize));
		_C.SetFlipState(true);
	}
	_CardIndex = 0;
}

// SUMMARY: Returns the play state back to default settings.
// RETURNS: GAME_OK
ERROR_CODE PlayState::Reset_PlayState() {
	system("cls");

	_ValidInput = true;
	_GameIsSetup = false;
	_CardCount = 0;

	if (G_Conf._PWCoins) {
		SetErrorPromt(L"");
		_NumBet = 0;
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

// SUMMARY: Draws multiple cards in horozontal columns and rows.
// PARAMETERS: CARD* - Array ptr of Cards to Draw, INT - Number of Cards, INT - Numer of Columns
// RETURNS: GAME_OK
ERROR_CODE PlayState::Draw_Cards(Card* _CardSet, int _C_Count, int _Columns) {
	for (int i = 0; i < _C_Count; i += _Columns) { // For the number of cards
		for (int x = 0; x < CARD_GRAPHIC_SIZE; ++x) { // For each line in each card's graphic (+1 to include a selector line)
			wstring _line = L""; // Variable to align each card graphic segment onto a single line
			for (int j = 0; j < _Columns; ++j) { // for the number of columns
				if (_CardSet[i + j].GetFlipState()) _line += _FaceDownCard[x];
				else _line += _CardSet[i + j].GetCardGraphic(x);
			}
			wcout << centreString(_line) << endl;
		}

		// Make selector line
		int adjustedIndex = _CardIndex;
		if (_CardIndex >= 10) adjustedIndex -= 10;
		if (adjustedIndex >= i && adjustedIndex < (i + _Columns)) { // If card index is on the current Row
			wstring _SelSpace(11 * (adjustedIndex - i) + 14, L' ');
			wcout << _SelSpace << _Selector << endl;
		}
	}
	return GAME_OK;
}