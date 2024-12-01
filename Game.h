#pragma once
//====================================================================================
// NAME: Game.h
// DESC: Contains Game Class
// AUTH: Oliver Callaghan
//====================================================================================
#include "Constants.h"
#include "States.h"
#include <fcntl.h>
#include <io.h>
#include "Singleton.h"
#include "Card.h"
//====================================================================================

// SUMMARY: Game Class Object used to store / manage functions and variables relating to the Sinlgeton Instance of the Game.
class Game : public Singleton<Game> {
public:
	Game() {
		_setmode(_fileno(stdout), _O_U16TEXT); // Sets Console Mode to output UTF-16 Characters.

		// Declare and Initalise States.
		_GameStates[START_STATE] = new StartState();
		_GameStates[SETUP_STATE] = new SetupState();
		_GameStates[PLAY_STATE] = new PlayState(_Config);
		_GameStates[END_STATE] = new EndState(_Config);

		_CurrentState = _GameStates[START_STATE]; // Set the current state to the start state.
		_GameRunning = true; // Set the Game Running state to true.
	};
	~Game() {};

	void Update() { _CurrentState->Update(); }; // Updates the current state.
	void Render() { _CurrentState->Render(); }; // Renders the current state.

	const bool IsGameRunning() { return _GameRunning; }	// Returns if the game is currently running.

	void setGameRunning(bool _Val) { _GameRunning = _Val; } // Sets the Game Running Status.

	const int GetHighScore() { return _HighScore; }	// Returns the current High Score.
	void SetHighScore(int _Val) { _HighScore = _Val; } // Sets the current High Score.

	void SwitchState(int _Index) { _CurrentState = _GameStates[_Index]; } // Switches the current state using a specified index.

	GameConfig& GetGameConfig() { return _Config; }	// Returns the game config by reference.
	void UpdateGameConfig(GameConfig _GC) { _Config = _GC; }; // Updates the current game config.

	Card& GetCard(int _Index) { return _Deck[_Index]; }	// Returns Card by reference using a specified index.
	void SetCard(int _Index, Card& _Card) { _Deck[_Index] = _Card; } // Updates a card using a specified index.

private:
	State* _CurrentState; // Current State pointer (Updated to point to the currently active state).
	State* _GameStates[STATE_COUNT]; // Array of pointers to states.

	bool _GameRunning = false; // Bool to mange if the game is running.

	int _HighScore = 0; // Main Highscore Variable.

	GameConfig _Config; // Main Game Config Variable.
	Card _Deck[MAX_DECK_SIZE]; // Full Deck of Cards used in game.
};

