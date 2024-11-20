#pragma once

#include "Constants.h"
#include "Card.h"

class State {
public:
	State() {}
	~State() {};

	virtual void Update() = 0;
	virtual void Render() = 0;

	bool IsRenderDirty() { return _DirtyRender; }

protected:
	void SetDirtyRender(bool _Val) { _DirtyRender = _Val; }
	virtual ERROR_CODE Init() = 0;

private:
	bool _DirtyRender = true;
};

// Main Menu State
// Play State
// End State

class PlayState : public State {
public:
	PlayState() {
		ret_code = Init();
		assert(ret_code == GAME_OK && "Play State Initialised Incorrectly"); // Assert Game Initalisation
	};

	void Update() override;
	void Render() override;

private:
	ERROR_CODE Init() override;
	ERROR_CODE Draw_Card(Card& _C);
	ERROR_CODE Draw_Cards(Card* _CardSet, int _C_Count, int _Columns, int _Indent);
	ERROR_CODE GenerateGraphics(Card& _C);

	Card _Deck[DEFAULT_DECK_SIZE];
	Card _FaceDown;
};