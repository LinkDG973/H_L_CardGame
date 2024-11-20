#pragma once

#include "Constants.h"
#include "States.h"
#include <fcntl.h>
#include <io.h>

class Game {
public:
	Game() {
		_setmode(_fileno(stdout), _O_U16TEXT);
		_CurrentState = new PlayState();
		_GameRunning = true;
	};
	~Game() {};

	void Update() { _CurrentState->Update(); };
	void Render() {
		if (_CurrentState->IsRenderDirty())
			_CurrentState->Render();
	};

	bool IsGameRunning() { return _GameRunning; }

private:
	State* _CurrentState;

	bool _GameRunning = false;

	std::wstring _UserName = L"";
};

