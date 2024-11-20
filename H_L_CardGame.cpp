// H_L_CardGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Game.h"

int main() {

    Game _Game;

    while (_Game.IsGameRunning()) {
        _Game.Render();
        _Game.Update();
    }

}
