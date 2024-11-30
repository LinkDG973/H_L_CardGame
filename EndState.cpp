#include "Game.h"
#include "States.h"

bool EndState::CheckInput(char _Input) {
	if (Game::getInstance().GetGameConfig()._PWDlbNothing && !_DblN_Played && Game::getInstance().GetScore() > 0 || _Holding) {
		if (!_Holding) {
			switch (_Input) {
				case 'Y':
					if (_PlayerCard.GetSuit() == _RandCard.GetSuit()) {
						Game::getInstance().SetScore(Game::getInstance().GetScore() * 2); // Doubles the Player's Score
						_Result = L"SUITS MATCH, YOU WIN X2 SCORE!";
					}
					else {
						Game::getInstance().SetScore(0); // Zeros the Player's Score
						_Result = L"SUITS DON'T MATCH, YOU LOSE.";
					}
					_Holding = true;
					break;
				case 'N': _DblN_Played = true; break;
				default: return false; break;
			}
		}
		else {
			switch (_Input) {
				case 'E': 
					_DblN_Played = true; 
					_Holding = false;
					break;
				default: return false; break;
			}
		}
	}
	else {
		switch (_Input) {
			case 'Y':
				_DblN_Played = false;
				_Dbln_Set = false;
				Game::getInstance().SwitchState(START_STATE); 
				break;
			case 'N':
				// DRAW FINAL STATE
				system("cls");
				wcout << BOARDER << endl << BOARDER << endl;
				MakeSpace(12);
				wcout << BOARDER << endl;
				wcout << centreString(L"THE GAME HAS ENDED. THANK YOU FOR PLAYING.") << endl;
				wcout << BOARDER << endl;
				MakeSpace(11);
				wcout << BOARDER << endl << endl << BOARDER << endl;
				wcout << centreString(L"PRESS ANY KEY TO EXIT...") << endl;
				Game::getInstance().setGameRunning(false);
				break;
			default: return false; break;
		}
	}

	return true;
}

void EndState::DrawEndScreen() {
	MakeSpace(10);
	wcout << BOARDER << endl;

	int tempVal = 0;
	wstringstream _MSG;
	wstring mode = L"SCORE : ";
	tempVal = Game::getInstance().GetScore();
	if (Game::getInstance().GetGameConfig()._PWCoins) {
		wstring mode = L"COINS : £";
	}

	if (tempVal > 0 && tempVal > Game::getInstance().GetHighScore()) {
		wstringstream _MSG2;
		Game::getInstance().SetHighScore(tempVal);
		wcout << centreString(L"! NEW HIGH SCORE !") << endl;
		_MSG2 << L"HIGH SCORE : " << Game::getInstance().GetHighScore() << endl;
		wcout << centreString(_MSG2.str()) << endl;
	}
	else {
		wstringstream _MSG2;
		_MSG2 << "HIGH SCORE : " << Game::getInstance().GetHighScore();
		wcout << centreString(_MSG2.str()) << endl << endl;
	}

	_MSG << mode << tempVal;

	wcout << centreString(_MSG.str()) << endl;
	wcout << BOARDER << endl;

	MakeSpace(11);
	SetCmdPromt(L"Play Again ? (Y / N)");
}

void EndState::DrawDblN() {
	MakeSpace(4);
	Draw_Card(_RandCard);
	MakeSpace(4);
	if (_Holding) {
		Draw_Card(_PlayerCard);
	}
	else {
		for (int i = 0; i < CARD_GRAPHIC_SIZE; ++i) {
			wcout << centreString(_FaceDownCard[i]) << endl;
		}
	}
	MakeSpace(4);
	if (_Holding) {
		SetOutPromt(_Result);
		SetCmdPromt(L"Press 'E' to continue... (E)");
	}
	else {
		SetCmdPromt(L"Go for double or nothing? (Y / N)");
	}
}

void EndState::SpecificRender() {
	if (Game::getInstance().GetGameConfig()._PWDlbNothing && !_DblN_Played && Game::getInstance().GetScore() > 0 || _Holding) {
		if (!_Dbln_Set) {
			_RandCard = Game::getInstance().GetCard(randomNum(0, FOCUS_DECK_SIZE));
			_PlayerCard = Game::getInstance().GetCard(randomNum(0, MAX_DECK_SIZE - 1));
			_Dbln_Set = true;
		}
		DrawDblN();
	}
	else {
		SetOutPromt(L"");
		DrawEndScreen();
	}
}
