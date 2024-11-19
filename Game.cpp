
#include "Game.h"

ERROR_CODE Game::Init() {

	// Initalise the Deck

	// H = Hearts, S = Spades, D = Diamonds, C = Clubs

	ui8 num = 1;
	ui8 suit_index = 0;
	for (Card& _C : _Deck) {
		Card temp_Card(SUITS[suit_index], num++);
		_C = temp_Card;
		if (num > 13) {
			num = 1;
			suit_index++;
		}
		Draw_Card(_C);

	}

	// Draw Cards
	//Draw_Card(_Deck[0]);

	return GAME_OK;
}

ERROR_CODE Game::Draw_Card(Card& _C) {


		//"┌─────────┐"
		//"│{}{}     │"
		//"│         │"
		//"│         │"
		//"│    {}   │"
		//"│         │"
		//"│         │"
		//"│     {}{}│"
		//"└─────────┘"


	//std::cout << "┌─────────┐\n" << "│{}{}     │\n" << "│    {}   │\n" << "│     {}{}│\n" << "└─────────┘";
	std::cout << "__________\n" 
		      << "| " << _C.GetVal() << _C.GetSuit() << "     |\n" 
			  << "|   " << _C.GetSuit() << "    |\n" 
			  << "|     " << _C.GetSuit() << _C.GetVal() << " |\n" 
			  << "----------\n";


	return GAME_OK;
}
