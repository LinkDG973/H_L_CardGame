#pragma once

#include "Constants.h"
#include "Card.h"
#include <sstream>

class State {
public:
	State() {}
	~State() {};

	virtual void Update() { BasicInput(); };
	void Render() {
		wcout << BOARDER << endl << BOARDER << endl;

		SpecificRender();

		wcout << BOARDER << endl;
		if (!_ValidInput) wcout << _ErrorPromt << endl;
		else wcout << _OutPromt << endl;
		wcout << BOARDER << endl;
		wcout << _CmdPromt + L" \u2192 ";
	};

	bool IsRenderDirty() { return _DirtyRender; }

	void SetCmdPromt(wstring _Msg) { _CmdPromt = _Msg; }
	void SetOutPromt(wstring _Msg) { _OutPromt = _Msg; }
	void SetErrorPromt(wstring _Msg) { _ErrorPromt = _Msg; }

	inline std::string trim(std::string& str) {
		str.erase(str.find_last_not_of(' ') + 1);         //suffixing spaces
		str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
		return str;
	}

protected:
	virtual void SpecificRender() = 0;
	void SetDirtyRender(bool _Val) { _DirtyRender = _Val; }
	void MakeSpace(int _Val) { for (int y = 0; y < _Val; ++y) wcout << endl; }
	bool _ValidInput = true;
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
		else {
			_ValidInput = false;
		}
		_ErrorPromt = DEFAULT_ERROR_MSG;
	};
private:
	virtual bool CheckInput(char _Input) = 0;
	bool _DirtyRender = true;
	wstring _CmdPromt = L"";
	wstring _OutPromt = L"";
	wstring _ErrorPromt = L"";
};

class StartState : public State {
protected:
	void SpecificRender() override;
private:
	bool CheckInput(char _Input) override;
	void DrawTitleScreen();
	void DrawRulesScreen();
	bool _showingRules = false;
	ui8 _currentPage = 1;
};

class SetupState : public State {
protected:
	void SpecificRender() override;
private:
	bool CheckInput(char _Input) override;
	GameConfig _tempConfig;
};

class PlayState : public State {
public:
	PlayState() {
		ret_code = Init();
		assert(ret_code == GAME_OK && "Play State Initialised Incorrectly"); // Assert Game Initalisation
	};

	void Update() override;

protected:
	void SpecificRender() override;
private:

	bool CheckInput(char _Input) override;
	void UpdateScore(bool _Res, wstring _Input);

	ERROR_CODE Init();
	ERROR_CODE Draw_Card(Card _C, int _Indent);
	ERROR_CODE Draw_Cards(Card* _CardSet, int _C_Count, int _Columns, int _Indent);
	ERROR_CODE GenerateGraphics(Card& _C);
	ERROR_CODE Reset_PlayState();

	int GetDeckSize();

	void DrawGameScreen();

	bool CheckBet(string _Bet);
	bool isNumber(string& _Str);

	int GetNewCardIndex();

	Card _InPlay[10];
	Card _FaceDown;

	int _Score = 0;
	int _randomIndex = 0;
	int _CardIndex = 0;
	bool _GameIsSetup = false;

	int _Coins = STARTING_COIN_COUNT;
	int _NumBet = 0;
	bool _Betting = true;

	wstring _Result;
};

class EndState : public State {
protected:
	void SpecificRender() override;
private:
	bool CheckInput(char _Input) override;
};