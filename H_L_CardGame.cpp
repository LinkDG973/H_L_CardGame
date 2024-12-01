//====================================================================================
// NAME: H_L_CardGame.cpp
// DESC: The Main Entry Point for the Code. Program execution begins and ends here.
// AUTH: Oliver Callaghan
//====================================================================================
#include "Game.h"
//====================================================================================

// SUMMARY: Declares and initalises the game. Operates main game loop.
// RETURNS: INT - EXIT CODE
int main() {
    Game _Game; // Declare and Initalise the game

    while (_Game.IsGameRunning()) { // While the game is not finished
        system("cls");  // Clear the screen
        _Game.Render(); // Render the current game screen
        _Game.Update(); // Update the game
    }
}
