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
	bool _ValidInput = true;
private:
	bool _DirtyRender = true;
};

// Start State
// Play State
// End State

class StartState : public State {
public:
	void Update() override;
	void Render() override;
	ERROR_CODE Init() override { return GAME_OK; }
private:

	void DrawTitleScreen();

};

class SetupState : public State {
	void Update() override;
	void Render() override;
	ERROR_CODE Init() override { return GAME_OK; }
private:

	bool CheckInput(wstring& _Input);

	bool _PWJokers = false;
	bool _PWDuplicateCards = false;
	bool _PWCoins = false;
	bool _PWDlbNothing = false;
	int _NumRows = 2;

};

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
	ERROR_CODE Draw_Card(Card& _C, int _Indent);
	ERROR_CODE Draw_Cards(Card* _CardSet, int _C_Count, int _Columns, int _Indent);
	ERROR_CODE GenerateGraphics(Card& _C);
	bool CheckInput(wstring _Input);
	ERROR_CODE Reset_PlayState();

	void DrawSetupScreen();
	void DrawGameScreen();
	int randomNum(int _Min, int _Max) { return rand() % (_Max - _Min + 1) + _Min; }

	Card _Deck[DEFAULT_DECK_SIZE];
	Card _InPlay[10];
	Card _FaceDown;

	int _Score = 0;
	int _randomIndex = 0;
	int _CardIndex = 0;
	bool _GameIsSetup = false;
};

class EndState : public State {
public:
	void Update() override;
	void Render() override;
	ERROR_CODE Init() override { return GAME_OK; }
};