#pragma once

#include "Constants.h"
#include "States.h"
#include <fcntl.h>
#include <io.h>
#include "Singleton.h"
#include "Card.h"

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

	const int GetScore() { return _PlayerScore; }
	void SetScore(int _Val) { _PlayerScore = _Val; }

	const int GetHighScore() { return _HighScore; }
	void SetHighScore(int _Val) { _HighScore = _Val; }

	void SwitchState(int _Index) { _CurrentState = _GameStates[_Index]; }

	void UpdateGameConfig(GameConfig _GC) { _Config = _GC; };
	const GameConfig GetGameConfig() { return _Config; }

	Card GetCard(int _Index) { return _Deck[_Index]; }
	void SetCard(int _Index, Card& _Card) { _Deck[_Index] = _Card; }

private:
	State* _CurrentState;
	State* _GameStates[STATE_COUNT];

	bool _GameRunning = false;

	int _HighScore = 0;
	int _PlayerScore = 0; // Varible to hold both regular score and coins

	GameConfig _Config;
	Card _Deck[MAX_DECK_SIZE];
};

