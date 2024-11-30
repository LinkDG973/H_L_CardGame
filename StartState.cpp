#include "Game.h"
#include "States.h"

void StartState::DrawTitleScreen() {
	Card card1 = Game::getInstance().GetCard(randomNum(0, MAX_DECK_SIZE));
	Card card2 = Game::getInstance().GetCard(randomNum(0, MAX_DECK_SIZE));

	wcout << L"                     ┌─┒ ┌─┒┌─────┒┌─────┒┌─┒ ┌─┒┌─────┒┌────┒" << endl
		  << L"                     │ ┃ │ ┃┕━┑ ┏━┛│┏━━┑ ┃│ ┃ │ ┃│ ┏━━━┛│ ┏━┑┃" << endl
		  << L"                     │ ┖─┘ ┃  │ ┃  │┃  ┕━┛│ ┖─┘ ┃│ ┖───┒│ ┖─┘┖┒" << endl
		  << L"     " << card1.GetCardGraphic(0) << L"     │ ┏━┑ ┃  │ ┃  │┃ ┌──┒│ ┏━┑ ┃│ ┏━━━┛│ ┏━┑ ┃     " << card2.GetCardGraphic(0) << endl
		  << L"     " << card1.GetCardGraphic(1) << L"     │ ┃ │ ┃┌─┘ ┖─┒│┖─┴─ ┃│ ┃ │ ┃│ ┖───┒│ ┃ │ ┃     " << card2.GetCardGraphic(1) << endl
		  << L"     " << card1.GetCardGraphic(2) << L"     ┕━┛ ┕━┛┕━━━━━┛┕━━━━━┛┕━┛ ┕━┛┕━━━━━┛┕━┛ ┕━┛     " << card2.GetCardGraphic(2) << endl
		  << L"     " << card1.GetCardGraphic(3) << L"         ┌─┒    ┌─────┒┌┒   ┌┒┌─────┒┌────┒         " << card2.GetCardGraphic(3) << endl
		  << L"     " << card1.GetCardGraphic(4) << L"         │ ┃    │ ┏━┑ ┃│┃┌─┒│┃│ ┏━━━┛│ ┏━┑┃         " << card2.GetCardGraphic(4) << endl
		  << L"     " << card1.GetCardGraphic(5) << L"         │ ┃    │ ┃ │ ┃│┃│ ┃│┃│ ┖───┒│ ┖─┘┖┒        " << card2.GetCardGraphic(5) << endl
		  << L"     " << card1.GetCardGraphic(6) << L"         │ ┃    │ ┃ │ ┃│┃│ ┃│┃│ ┏━━━┛│ ┏━┑ ┃        " << card2.GetCardGraphic(6) << endl
		  << L"                         │ ┖───┒│ ┖─┘ ┃│┖┘ ┖┘┃│ ┖───┒│ ┃ │ ┃" << endl
		  << L"                         ┕━━━━━┛┕━━━━━┛┕━━━━━┛┕━━━━━┛┕━┛ ┕━┛" << endl;
	wcout << centreString(L"BY - OLIVER CALLAGHAN") << endl << endl;

	wcout << BOARDER << endl;
	wcout << centreString(L"MAIN MENU") << endl;
	wcout << BOARDER << endl << endl;
	wcout << centreString(L"PLAY GAME (P)") << endl << endl;
	wcout << centreString(L"SETTINGS (S)") << endl << endl;
	wcout << centreString(L"RULES (R)") << endl << endl << endl;
	SetCmdPromt(L"Select Option (P / S / R)");
}

void StartState::DrawRulesScreen() {
	wcout << centreString(L"RULES") << endl;
	wcout << BOARDER << endl;

	switch (_currentPage) {
	case 2: 
		wcout << L"     ┌───────────────────────────────────────────────────────────────────────┒" << endl;
		wcout << L"     │ PLAY WITH JOKERS                                                      ┃" << endl;
		wcout << L"     ├───────────────────────────────────────────────────────────────────────┨" << endl;
		wcout << L"     │ ⌂ Adds Jokers to the game pool.                                       ┃" << endl;
		wcout << L"     │ ⌂ Joker cards beat all cards regardless of if the player selects      ┃" << endl;
		wcout << L"     │   higher or lower.                                                    ┃" << endl;
		wcout << L"     │ ⌂ Joker cards can only be drawn in the player's card and not the      ┃" << endl;
		wcout << L"     │   computer's card.                                                    ┃" << endl;
		wcout << L"     ├───────────────────────────────────────────────────────────────────────┨" << endl;
		wcout << L"     │ PLAY WITH DUPLICATE CARDS                                             ┃" << endl;
		wcout << L"     ├───────────────────────────────────────────────────────────────────────┨" << endl;
		wcout << L"     │ ⌂ Turns off the limits of playing with a single deck by allowing any  ┃" << endl;
		wcout << L"     │   card to be in any position.                                         ┃" << endl;
		wcout << L"     ├───────────────────────────────────────────────────────────────────────┨" << endl;
		wcout << L"     │ PLAY WITH COINS                                                       ┃" << endl;
		wcout << L"     ├───────────────────────────────────────────────────────────────────────┨" << endl;
		wcout << L"     │ ⌂ Adds betting coins to the game. This gives the player the option to ┃" << endl;
		wcout << L"     │   bet a certain amount on their choice of higher or lower.            ┃" << endl;
		wcout << L"     │ ⌂ A winning bet rewards the player with double their placed bet.      ┃" << endl;
		wcout << L"     │   A loosing bet looses the players bet.                               ┃" << endl;
		wcout << L"     │                                                                       ┃" << endl;
		wcout << L"     │                                                                       ┃" << endl;
		wcout << L"     ┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
		break;
	case 3: 
		wcout << L"     ┌───────────────────────────────────────────────────────────────────────┒" << endl;
		wcout << L"     │ DOUBLE OR NOTHING MODE                                                ┃" << endl;
		wcout << L"     ├───────────────────────────────────────────────────────────────────────┨" << endl;
		wcout << L"     │ ⌂ This mode adds a the opition to play a double or nothing mini game  ┃" << endl;
		wcout << L"     │   at the end of the higher-lower game. This mini game provides a high ┃" << endl;
		wcout << L"     │   risk-high reward game.                                              ┃" << endl;
		wcout << L"     │ ⌂ The player bets all their points on if their card suit matched the  ┃" << endl;
		wcout << L"     │   shuffled card.                                                      ┃" << endl;
		wcout << L"     ├───────────────────────────────────────────────────────────────────────┨" << endl;
		wcout << L"     │ OTHER                                                                 ┃" << endl;
		wcout << L"     ├───────────────────────────────────────────────────────────────────────┨" << endl;
		wcout << L"     │                                                                       ┃" << endl;
		wcout << L"     │                                                                       ┃" << endl;
		wcout << L"     │                                                                       ┃" << endl;
		wcout << L"     │                                                                       ┃" << endl;
		wcout << L"     │                                                                       ┃" << endl;
		wcout << L"     │                                                                       ┃" << endl;
		wcout << L"     ├───────────────────────────────────────────────────────────────────────┨" << endl;
		wcout << L"     │ OTHER                                                                 ┃" << endl;
		wcout << L"     ├───────────────────────────────────────────────────────────────────────┨" << endl;
		wcout << L"     │                                                                       ┃" << endl;
		wcout << L"     │                                                                       ┃" << endl;
		wcout << L"     ┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
		break;
	default:
		wcout << L"     ┌───────────────────────────────────────────────────────────────────────┒" << endl;
		wcout << L"     │ HOW TO PLAY                                                           ┃" << endl;
		wcout << L"     ├───────────────────────────────────────────────────────────────────────┨" << endl;
		wcout << L"     │ ⌂ The player is presented with one card face-up and several face-down ┃" << endl;
		wcout << L"     │   cards. They must make an educated guess whether they or not their   ┃" << endl;
		wcout << L"     │   card is higher or lower than the card shown above.                  ┃" << endl;
		wcout << L"     │ ⌂ If they guess correctly, they are awarded with 150 points.          ┃" << endl;
		wcout << L"     │ ⌂ If they guess incorrectly, they are deducted 100 points.            ┃" << endl;
		wcout << L"     ├───────────────────────────────────────────────────────────────────────┨" << endl;
		wcout << L"     │ CONTROLS                                                              ┃" << endl;
		wcout << L"     ├───────────────────────────────────────────────────────────────────────┨" << endl;
		wcout << L"     │ ⌂ Each operation in the game can be selected by inputing a single     ┃" << endl;
		wcout << L"     │   character. Character codes are shown next to their respective       ┃" << endl;
		wcout << L"     │   operation.                                                          ┃" << endl;
		wcout << L"     │ ⌂ For Example : 'Back (B)' allows the player to go back by inputing   ┃" << endl;
		wcout << L"     │   'B'. Inputs work regardless of capitalisation. Inputing 'b' works   ┃" << endl;
		wcout << L"     │   the same as 'B'.                                                    ┃" << endl;
		wcout << L"     ├───────────────────────────────────────────────────────────────────────┨" << endl;
		wcout << L"     │ NUMBER OF CARD ROWS                                                   ┃" << endl;
		wcout << L"     ├───────────────────────────────────────────────────────────────────────┨" << endl;
		wcout << L"     │ ⌂ There are 10 face-down cards in the game be defualt. This number    ┃" << endl;
		wcout << L"     │   can be increased to 15 or decreased to 5 in the Settings Menu.      ┃" << endl;
		wcout << L"     ┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
		break;
	}

	wcout << L"     Select Page (1 / 2 / 3)                                        PAGE " << _currentPage << L" - 3" << endl;
	SetCmdPromt(L"Input (B) to Return to the Title Screen");
}

bool StartState::CheckInput(char _Input) {
	if (!_showingRules) {
		switch (_Input) { // TITLE Screen Inputs
			case 'P': Game::getInstance().SwitchState(PLAY_STATE);  break;
			case 'S': Game::getInstance().SwitchState(SETUP_STATE); break;
			case 'R': _showingRules = true; break;
			default: return false; break;
		}
	}
	else { // RULE Screen Inputs
		switch (_Input) {
			case 'B': // Back input
				_showingRules = false; // Switch back to the title screen.
				_currentPage = 1; // Reset the rules screen
				break;
			case '1': case '2': case '3': // Set the current page to the input number
				_currentPage = int(_Input) - ASCII_NUM_SHIFT; break;
			default: return false; break;
		}
	}

	return true;
}

void StartState::SpecificRender() {
	if (!_showingRules) DrawTitleScreen();
	else DrawRulesScreen();
}