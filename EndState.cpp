#include "Game.h"
#include "States.h"

bool EndState::CheckInput(char _Input) {
	switch (_Input) {
	case 'Y': Game::getInstance().SwitchState(START_STATE); break;
	case 'N':
		system("cls");
		wcout << BOARDER << endl << BOARDER << endl;
		MakeSpace(12);
		wcout << BOARDER << endl;
		wcout << CARD_INDENT << CARD_INDENT << L"THE GAME HAS ENDED. THANK YOU FOR PLAYING." << endl;
		wcout << BOARDER << endl;
		MakeSpace(11);
		wcout << BOARDER << endl << endl << BOARDER << endl;
		wcout << L"                            PRESS ANY KEY TO EXIT..." << endl;
		Game::getInstance().setGameRunning(false);
		break;
	default: 
		return false; 
		break;
	}

	return true;
}

void EndState::SpecificRender() {
	MakeSpace(10);
	wcout << BOARDER << endl;

	int tempVal = 0;
	wstring mode = L" COINS : £";
	if (Game::getInstance().GetGameConfig()._PWCoins) {
		tempVal = Game::getInstance().GetCoins();
	}
	else {
		tempVal = Game::getInstance().GetScore();
		mode = L" SCORE : ";
	}

	if (tempVal > Game::getInstance().GetHighScore()) {
		Game::getInstance().SetHighScore(tempVal);
		wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << "! NEW HIGH SCORE !" << endl;
		wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << "HIGH SCORE : " << Game::getInstance().GetHighScore() << endl;
	}
	else {
		wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << "HIGH SCORE : " << Game::getInstance().GetHighScore() << endl << endl;
	}

	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT
		<< Game::getInstance().GetUserName() << mode << tempVal << endl;
	wcout << BOARDER << endl;
	MakeSpace(11);
	SetCmdPromt(L"Play Again ? (Y / N)");
}
