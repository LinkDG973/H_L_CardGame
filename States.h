#pragma once

#include "Constants.h"
#include "Card.h"
#include <sstream>

class State {
public:
	State() {};
	~State() {};

	virtual void Update() { BasicInput(); };
	void Render() {
		wcout << BOARDER << endl << BOARDER << endl; // Draw Screen Header Boarder
		SpecificRender(); // Draw State Respective Screen
		wcout << BOARDER << endl; // Draw State Screen Footer
		// Draw Input Dependent Message
		if (!_ValidInput) wcout << centreString(_ErrorPromt) << endl; // Output Error Message
		else wcout << centreString(_OutPromt) << endl; // Output Command Responce message
		wcout << BOARDER << endl; // Draw Command Message Footer
		wcout << centreString(_CmdPromt + L" \u2192 "); // Draw Command Prompt Message and Cursor
	};

	bool IsRenderDirty() { return _DirtyRender; }

protected:
	bool _ValidInput = true;

	virtual void SpecificRender() = 0;

	void SetCmdPromt(wstring _Msg) { _CmdPromt = _Msg; }
	void SetOutPromt(wstring _Msg) { _OutPromt = _Msg; }
	void SetErrorPromt(wstring _Msg) { _ErrorPromt = _Msg; }
	void SetDirtyRender(bool _Val) { _DirtyRender = _Val; }

	void MakeSpace(int _Val) { for (int y = 0; y < _Val; ++y) wcout << endl; }
	int randomNum(int _Min, int _Max) { return rand() % (_Max - _Min + 1) + _Min; }

	void BasicInput() {
		string _Input = "";
		cin >> _Input;
		trim(_Input);
		if (_Input.size() == 1) {
			char _charInput = _Input[0];
			_charInput = toupper(_charInput);
			_ValidInput = CheckInput(_charInput);
		}
		else _ValidInput = false;
		_ErrorPromt = DEFAULT_ERROR_MSG;
	}

	ERROR_CODE Draw_Card(Card _C) {
		for (int i = 0; i < CARD_GRAPHIC_SIZE; ++i)
			wcout << centreString(_C.GetCardGraphic(i)) << endl;
		return GAME_OK;
	}

	wstring centreString(wstring _str) {
		// (screenwidth / 2) - (_str/2) to nearest int
		int no_spaces = (SCREEN_WIDTH * 0.5f) - (_str.length() * 0.5f);
		wstring sp(no_spaces, L' ');
		return sp + _str;
	}

	inline std::string trim(std::string& str) {
		str.erase(str.find_last_not_of(' ') + 1);         //suffixing spaces
		str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
		return str;
	}

private:
	virtual bool CheckInput(char _Input) = 0;
	bool _DirtyRender = true;
	wstring _CmdPromt = L"";
	wstring _OutPromt = L"";
	wstring _ErrorPromt = L"";
};

class StartState : public State {
private:
	void SpecificRender() override;
	bool CheckInput(char _Input) override;
	void DrawTitleScreen();
	void DrawRulesScreen();
	bool _showingRules = false;
	ui8 _currentPage = 1;
};

class SetupState : public State {
private:
	void SpecificRender() override;
	bool CheckInput(char _Input) override;
	GameConfig _tempConfig;
};

class PlayState : public State {
public:
	PlayState(GameConfig& _GC) : G_Conf(_GC) {
		ret_code = Init();
		assert(ret_code == GAME_OK && "Play State Initialised Incorrectly"); // Assert Game Initalisation
	};

	void Update() override;

private:
	void SpecificRender() override;

	bool CheckInput(char _Input) override;
	bool CheckEqual(int _Val1, int _Val2);
	void UpdateScore(bool _Res, wstring _Input);

	ERROR_CODE Init();
	ERROR_CODE Draw_Cards(Card* _CardSet, int _C_Count, int _Columns);
	ERROR_CODE GenerateGraphics(Card& _C);
	ERROR_CODE Reset_PlayState();
	void Reset_PlayCards();

	int GetDeckSize();

	bool CheckBet(string _Bet);

	int GetNewCardIndex(int _DeckSize);

	Card _InPlay[PLAY_DECK_SIZE];

	bool _GameIsSetup = false;
	bool _Holding = false;
	bool _Betting = true;

	int _NumBet = 0;
	int _Difference = 0;

	int _randomIndex = 0;
	int _CardIndex = 0;
	int _CurrentRow = 0;	// Uses to note which row the Selector is on
	int _SelectorStart = 0;
	int _CardCount = 0;

	GameConfig& G_Conf;

	wstring _Result;
	wstring _RoundResult = L"";
};

class EndState : public State {
private:
	void SpecificRender() override;
	bool CheckInput(char _Input) override;
	void DrawEndScreen();
	void DrawDblN();
	bool _DblN_Played = false;
	bool _Dbln_Set = false;
	bool _Holding = false;
	Card _RandCard;
	Card _PlayerCard;
	wstring _Result;
};