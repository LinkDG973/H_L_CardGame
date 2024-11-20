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

	void Update();
	void Render();

	bool IsGameRunning() { return _GameRunning; }
	bool IsRenderDirty() { return _DirtyRender; }

private:
	ERROR_CODE Init();

	ERROR_CODE GenerateGraphics(Card& _C);
	ERROR_CODE Draw_Card(Card& _C);
	ERROR_CODE Draw_Cards(Card* _CardSet, int _C_Count, int _Columns, int _Indent);

	Card _Deck[DEFAULT_DECK_SIZE];
	Card _FaceDown;

	bool _GameRunning = false;
	bool _DirtyRender = false;
};

