#pragma once

#include "Constants.h"
#include "Card.h"
#include <sstream>

class State {
public:
	State() {}
	~State() {};

	virtual void Update() {
		char _Input = ' ';
		cin >> _Input;
		_Input = toupper(_Input);
		_ValidInput = CheckInput(_Input);
	};
	virtual void Render() = 0;

	bool IsRenderDirty() { return _DirtyRender; }

protected:
	void SetDirtyRender(bool _Val) { _DirtyRender = _Val; }
	bool _ValidInput = true;
private:
	virtual bool CheckInput(char _Input) = 0;
	bool _DirtyRender = true;
};

class StartState : public State {
public:
	void Render() override;

private:
	bool CheckInput(char _Input) override;
	void DrawTitleScreen();
	void DrawRulesScreen();
	bool _showingRules = false;
	ui8 _currentPage = 1;
};

class SetupState : public State {
	void Render() override;

private:
	bool CheckInput(char _Input) override;

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
	bool CheckInput(char _Input) override;

	ERROR_CODE Init();
	ERROR_CODE Draw_Card(Card& _C, int _Indent);
	ERROR_CODE Draw_Cards(Card* _CardSet, int _C_Count, int _Columns, int _Indent);
	ERROR_CODE GenerateGraphics(Card& _C);
	ERROR_CODE Reset_PlayState();

	void DrawGameScreen();
	int randomNum(int _Min, int _Max) { return rand() % (_Max - _Min + 1) + _Min; }

	Card _Deck[DEFAULT_DECK_SIZE];
	Card _InPlay[10];
	Card _FaceDown;

	int _Score = 0;
	int _randomIndex = 0;
	int _CardIndex = 0;
	bool _GameIsSetup = false;

	//wstringstream _Result;
	wstring _Result;
};

class EndState : public State {
public:
	void Render() override;
private:
	bool CheckInput(char _Input) override;
};