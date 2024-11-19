#pragma once

#include "Constants.h"
#include "Card.h"

class Game {
public:
	Game() {
		ret_code = Init();
		assert(ret_code == GAME_OK && "Game Initialised Incorrectly"); // Assert Game Initalisation
	
	};
	~Game() {};

private:


	ERROR_CODE Init();

	ERROR_CODE Draw_Card(Card& _C);

	Card _Deck[DEFAULT_DECK_SIZE];

};

