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

		_GameStates[START_STATE] = new StartState();
		_GameStates[SETUP_STATE] = new SetupState();
		_GameStates[PLAY_STATE] = new PlayState();
		_GameStates[END_STATE] = new EndState();

		_CurrentState = _GameStates[START_STATE];
		_GameRunning = true;
	};
	~Game() {};

	void Update() { _CurrentState->Update(); };
	void Render() {
		if (_CurrentState->IsRenderDirty())
			_CurrentState->Render();
	};

	const bool IsGameRunning() { return _GameRunning; }
	void setGameRunning(bool _Val) { _GameRunning = _Val; }

	const wstring GetUserName() { return _UserName; }
	void setUserName(wstring _Val) { _UserName = _Val; }

	const int GetScore() { return _Score; }
	void SetScore(int _Val) { _Score = _Val; }

	const int GetHighScore() { return _HighScore; }
	void SetHighScore(int _Val) { _HighScore = _Val; }

	void SwitchState(int _Index) { _CurrentState = _GameStates[_Index]; }

	void UpdateGameConfig(GameConfig _GC) { _Config = _GC; };
	const GameConfig GetGameConfig() { return _Config; }

private:
	State* _CurrentState;

	State* _GameStates[STATE_COUNT];

	bool _GameRunning = false;

	std::wstring _UserName = L"";
	int _HighScore = 0;
	int _Score = 0;

	GameConfig _Config;
};

