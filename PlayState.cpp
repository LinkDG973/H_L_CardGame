
#include "Game.h"
#include "States.h"

ERROR_CODE PlayState::Init() {
	// Initalise the Deck
	ui8 num = 1;
	ui8 suit_index = 0;
	for (Card& _C : _Deck) {
		Card temp_Card(SUITS[suit_index], num++);
		GenerateGraphics(temp_Card);
		_C = temp_Card;
		if (num > 13) {
			num = 1;
			suit_index++;
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
	}

	_C.GetCardGraphic(1) = ss.str();
	_C.GetCardGraphic(5) = _C.GetCardGraphic(1);
	if (_C.GetVal() != 10)std::reverse(_C.GetCardGraphic(5).begin(), _C.GetCardGraphic(5).end());

	return GAME_OK;
}

void PlayState::Update() {
	char _Input = ' ';
	cin >> _Input;
	_Input = toupper(_Input);
	_ValidInput = CheckInput(_Input);
	if (_CardIndex >= 10) { // If game has finished
		Game::getInstance().SetScore(_Score);
		Reset_PlayState();
		Game::getInstance().SwitchState(END_STATE);
	}

	SetDirtyRender(true);
}

void PlayState::SpecificRender() {
	DrawGameScreen();
	SetDirtyRender(false);
}

void PlayState::DrawGameScreen() {
	wcout << CARD_INDENT << L"SCORE : " << _Score << endl;
	wcout << BOARDER << endl;
	Draw_Card(_Deck[_randomIndex], 3); // Focus Card
	wcout << BOARDER << endl;
	Draw_Cards(_InPlay, 9, 5, 1); // Player's Cards
	SetOutPromt(CARD_INDENT + _Result);
	SetCmdPromt(CARD_INDENT + L"Higher or Lower? ( H / L )");
}

void PlayState::UpdateScore(bool _Res, wstring _Input) {
	if (_Res) {
		_Score += 150;
		_Result = L"CARD WAS " + _Input + L"! +150 POINTS!";
	}
	else {
		_Score -= 100;
		_Result = L"CARD NOT " + _Input + L". -100 POINTS.";
	}
}

bool PlayState::CheckInput(char _Input) {
	switch (_Input) {
		case 'H':  UpdateScore(_InPlay[_CardIndex].GetVal() >= _Deck[_randomIndex].GetVal(), L"HIGHER"); break;
		case 'L':  UpdateScore(_InPlay[_CardIndex].GetVal() <= _Deck[_randomIndex].GetVal(), L"LOWER"); break;
		default: return false; break;
	}

	_InPlay[_CardIndex++].SetFlipState(false);
	_randomIndex = randomNum(0, DEFAULT_DECK_SIZE - 1);
	return true;
}

ERROR_CODE PlayState::Reset_PlayState() {
	system("cls");

	_ValidInput = true;
	_GameIsSetup = false;
	_CardIndex = 0;
	_Score = 0;

	srand(time(0));
	_randomIndex = randomNum(0, DEFAULT_DECK_SIZE - 1);

	for (Card& _C : _InPlay) {
		_C = _Deck[randomNum(0, DEFAULT_DECK_SIZE - 1)];
		_C.SetFlipState(true);
	}

	return GAME_OK;
}

ERROR_CODE PlayState::Draw_Card(Card& _C, int _Indent) {
	for (int i = 0; i < CARD_GRAPHIC_SIZE - 1; ++i) {
		wstring _line = L"";
		for (int y = 0; y < _Indent; ++y) _line += CARD_INDENT;
		wcout << _line << _C.GetCardGraphic(i) << endl;
	}
	return GAME_OK;
}

ERROR_CODE PlayState::Draw_Cards(Card* _CardSet, int _C_Count, int _Columns, int _Indent) {
	int num = 0;
	for (int i = 0; i < _C_Count; i + 0) { // for the number of cards
		for (int x = 0; x < CARD_GRAPHIC_SIZE; ++x) { // for the number of graphics
			wstring _line = L"";
			for (int y = 0; y < _Indent; ++y) _line += CARD_INDENT;
			num = 0;
			for (int j = 0; j < _Columns; ++j) { // for the number of columns
				if (x == 7 && (i+num) == _CardIndex) {
					_line += _Selector;
				}
				else {
					if (_CardSet[i + num].GetFlipState()) {
						_line += _FaceDown.GetCardGraphic(x);
					}
					else {
						_line += _CardSet[i + num].GetCardGraphic(x);
					}
				}
				++num;
			}
			wcout << _line << endl;
		}
		i += num;
	}

	return GAME_OK;
}
