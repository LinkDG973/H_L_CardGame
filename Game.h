#pragma once

#include "Constants.h"
#include "States.h"
#include <fcntl.h>
#include <io.h>
#include "Singleton.h"

class Game : public Singleton<Game> {
public:
	Game() {
		_setmode(_fileno(stdout), _O_U16TEXT);

		_GameStates[0] = new StartState();
		_GameStates[1] = new PlayState();

		_CurrentState = _GameStates[0];
		_GameRunning = true;
	};
	~Game() {};

	void Update() { _CurrentState->Update(); };
	void Render() {
		if (_CurrentState->IsRenderDirty())
			_CurrentState->Render();
	};

	bool IsGameRunning() { return _GameRunning; }

	wstring GetUserName() { return _UserName; }
	void setUserName(wstring _Val) { _UserName = _Val; }

	void SwitchState(int _Index) { _CurrentState = _GameStates[_Index]; }

private:
	State* _CurrentState;

	State* _GameStates[2];

	bool _GameRunning = false;

	std::wstring _UserName = L"";
	int _HighScore = 0;
};

