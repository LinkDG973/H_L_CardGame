//====================================================================================
// NAME: EndState.cpp
// DESC: Manages the End Game Processes including Double or Nothing and Score Screen.
// AUTH: Oliver Callaghan
//====================================================================================
#include "Game.h"
#include "States.h"
//====================================================================================

// SUMMARY: Takes the player's input, (Switches if on Highscore / Double or Nothing / END Screen).
// PARAMETERS: CHAR - Player's Input Character Command.
// RETURNS: BOOL - Validation Result of Input
bool EndState::CheckInput(char _Input) {
	if (G_Conf._PWDlbNothing && !_DblN_Played && G_Conf._Score > 0 || _Holding) {
		if (!_Holding) {
			switch (_Input) {
				case 'Y':
					if (_PlayerCard.GetSuit() == _RandCard.GetSuit()) {
						G_Conf._Score *= 2; // Doubles the Player's Score
						_Result = L"SUITS MATCH, YOU WIN X2 SCORE!";
					}
					else {
						G_Conf._Score = 0; // Zeros the Player's Score
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
				if (G_Conf._PWCoins) G_Conf._Score = STARTING_COIN_COUNT;
				else G_Conf._Score = 0;
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

// SUMMARY: Draws and Manages the Highscore Screen.
// RETURNS: VOID
void EndState::DrawEndScreen() {
	MakeSpace(10);
	wcout << BOARDER << endl;

	if (G_Conf._Score > 0 && G_Conf._Score > Game::getInstance().GetHighScore()) {
		Game::getInstance().SetHighScore(G_Conf._Score);
		wcout << centreString(L"! NEW HIGH SCORE !") << endl;
	}

	wcout << centreString(L"HIGH SCORE : " + to_wstring(Game::getInstance().GetHighScore())) << endl;

	wstringstream _MSG;
	if (Game::getInstance().GetGameConfig()._PWCoins) _MSG << L"COINS : £";
	else _MSG << L"SCORE : ";

	_MSG << G_Conf._Score;

	wcout << centreString(_MSG.str()) << endl;
	wcout << BOARDER << endl;

	MakeSpace(11);
	SetCmdPromt(L"Play Again ? (Y / N)");
}

// SUMMARY: Draws and Manages the Double or Nothing Screen.
// RETURNS: VOID
void EndState::DrawDblN() {
	MakeSpace(4);
	Draw_Card(_RandCard);
	MakeSpace(4);
	if (_Holding) Draw_Card(_PlayerCard);
	else {
		for (int i = 0; i < CARD_GRAPHIC_SIZE; ++i) 
			wcout << centreString(_FaceDownCard[i]) << endl;
	}
	MakeSpace(4);
	if (_Holding) {
		SetOutPromt(_Result);
		SetCmdPromt(L"Press 'E' to continue... (E)");
	}
	else SetCmdPromt(L"Go for double or nothing? (Y / N)");
}

// SUMMARY: Manages if Double or Nothing Criteria is met and which screen to draw.
// RETURNS: VOID
void EndState::SpecificRender() {
	if (G_Conf._PWDlbNothing && !_DblN_Played && G_Conf._Score > 0 || _Holding) {
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
