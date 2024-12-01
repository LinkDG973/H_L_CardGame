#pragma once
//====================================================================================
// NAME: States.h
// DESC: Contains State Class and assosiated sub-states
// AUTH: Oliver Callaghan
//====================================================================================
#include "Constants.h"
#include "Card.h"
#include <sstream>
//====================================================================================

// SUMMARY: Base State Class Object used to store / manage functions and variables relating to states.
class State {
public:
	State() {};	 // Base Constructor
	~State() {};

	// SUMMARY: Virtual Update Function - Gets basic input from user - used in states where a specific update function is not neccessary.
	virtual void Update() { BasicInput(); };

	// SUMMARY: Render Function - Draws Frame around states and manages output/command messages - Specific Render used by child classes.
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

protected:
	bool _ValidInput = true; // Valid Input Bool

	virtual void SpecificRender() = 0; // Pure Virtual Function for Specific Rendering to be overriden by child classes.

	void SetCmdPromt(wstring _Msg) { _CmdPromt = _Msg; }	 // Sets Command Promt Message
	void SetOutPromt(wstring _Msg) { _OutPromt = _Msg; }	 // Sets Output Message
	void SetErrorPromt(wstring _Msg) { _ErrorPromt = _Msg; } // Sets Error Promt Message

	void MakeSpace(int _Val) { for (int y = 0; y < _Val; ++y) wcout << endl; }		// Outputs a specified number of clear lines to the console.
	int randomNum(int _Min, int _Max) { return rand() % (_Max - _Min + 1) + _Min; } // Generates a random number between and including specified values.

	// SUMMARY: Simple Input function used by multiple states. Contains validation and filtering to both expand and minimise potential inputs.
	// RETURNS: VOID
	void BasicInput() {
		string _Input = "";
		cin >> _Input; // Get user input
		trim(_Input);  // Remove spaces
		if (_Input.size() == 1) { // If input is size of a character command
			char _charInput = _Input[0]; // Make the command TYPE CHAR
			_charInput = toupper(_charInput); // Set Character to upper case.
			_ValidInput = CheckInput(_charInput); // Check validation for current state.
		}
		else _ValidInput = false; // If not a character command
		_ErrorPromt = DEFAULT_ERROR_MSG; // Update Error Message
	}

	// SUMMARY: Draws a single card in the centre of the screen.
	// PARAMETERS: CARD - Specified card to be drawn.
	// RETURNS: GAME_OK
	ERROR_CODE Draw_Card(Card _C) {
		for (int i = 0; i < CARD_GRAPHIC_SIZE; ++i)
			wcout << centreString(_C.GetCardGraphic(i)) << endl;
		return GAME_OK;
	}

	// SUMMARY: Calulates the number of spaces required to display a string in the centre of the screen.
	// PARAMETERS: WSTRING - String to be centred.
	// RETURNS: WSTRING - Centred String.
	wstring centreString(wstring _str) {
		wstring sp((SCREEN_WIDTH * 0.5f) - (_str.length() * 0.5f), L' ');
		return sp + _str;
	}

	//====================================================================================
	// AUTH: Jeromy Adofo - October 4th 2021
	// SOURCE: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring 
	// SUMMARY: Trims Strings, removing all spaces either side of the string.
	// PARAMETERS: STRING & - String, by reference, to be trimmed.
	// RETURNS: STRING - Trimmed String
	inline std::string trim(std::string& str) {
		str.erase(str.find_last_not_of(' ') + 1); //suffixing spaces
		str.erase(0, str.find_first_not_of(' ')); //prefixing spaces
		return str;
	}
	//====================================================================================

private:
	virtual bool CheckInput(char _Input) = 0; // Pure Virtual Function to Check Inputs
	wstring _CmdPromt = L"";	// Stores Current Command Promt Message
	wstring _OutPromt = L"";	// Stores Current Output Message
	wstring _ErrorPromt = L"";	// Stores Current Error Message
};

// SUMMARY: Start State Class Object used to store / manage functions and variables relating to the Title / Rules Screens.
class StartState : public State {
private:
	void SpecificRender() override;			// Overriding Function to Render the Start State.
	bool CheckInput(char _Input) override;  // Overriding Function to Check Inputs.
	void DrawTitleScreen(); // Draws Title Screen
	void DrawRulesScreen();	// Draws Rules Screen
	bool _showingRules = false; // Specifies which state the screen is in.
	ui8 _currentPage = 1; // Specifies which page to display on the rules screen.
};

// SUMMARY: Setup State Class Object used to store / manage functions and variables relating to the Settings Screen.
class SetupState : public State {
private:
	void SpecificRender() override;		   // Overriding Function to Render the Setup State.
	bool CheckInput(char _Input) override; // Overriding Function to Check Inputs.
	GameConfig _tempConfig;				   // Temporary Config for the Settings Screen.
};

// SUMMARY: Base State Class Object used to store / manage functions and variables relating to the Play Screen.
class PlayState : public State {
public:
	// Overriding Constructor to give reference to the Game Class's Config variable.
	PlayState(GameConfig& _GC) : G_Conf(_GC) {
		ret_code = Init();
		assert(ret_code == GAME_OK && "Play State Initialised Incorrectly"); // Assert Game Initalisation
	};

	void Update() override; // Overriding Update Function

private:
	ERROR_CODE Init(); // Initalises the Deck and the Play State.
	ERROR_CODE GenerateGraphics(Card& _C); // Generates the visuals for each card by it's value and suit.

	void SpecificRender() override;		   // Overriding Function to Render the Play State.
	bool CheckInput(char _Input) override; // Overriding Function to Check Inputs.
	bool CheckEqual(int _Val1, int _Val2); // Checks if card values are equal.
	void UpdateScore(bool _Res, wstring _Input); // Updates Score and Develops an output message relative to the rounds result.

	ERROR_CODE Draw_Cards(Card* _CardSet, int _C_Count, int _Columns); // Draws multiple cards in horozontal columns and rows.
	ERROR_CODE Reset_PlayState(); // Returns the play state back to default settings.
	void Reset_PlayCards(); // Resets the Player's selection of cards and the current card index.

	int GetDeckSize(); // Returns the Size of the Deck relative to if JOKERS are in play.

	bool CheckBet(string _Bet); // Checks the player's bet input and passes if valid.

	int GetNewCardIndex(int _DeckSize); // Returns Random index from cards that have not been played yet. (Unless using duplicate cards).

	Card _InPlay[PLAY_DECK_SIZE]; // Player's set of cards that are currently in play.

	bool _GameIsSetup = false; // If the game is set up.
	bool _Holding = false;	   // If the game is in it's holding state.
	bool _Betting = true;	   // If the player is currently betting.

	int _NumBet = 0;	 // Value of the player's bet.
	int _Difference = 0; // Point/Coin difference the current round's result will apply to the player's score.

	int _randomIndex = 0; // Random Index used to store the random CPU card each round.
	int _CardIndex = 0;	  // Index of the current card in Play.
	int _CardCount = 0;   // Count of Cards Played by the user. (Used for when the number of cards in play is greater than cardIndex).

	GameConfig& G_Conf;   // Reference to the Game Class's Config variable.

	wstring _Result;	  // Holds the current result message.
	wstring _RoundResult = L""; // Holds the current round result message.
};

// SUMMARY: Base State Class Object used to store / manage functions and variables relating to the Highscore / Double or Nothing / END Screens.
class EndState : public State {
public:
	EndState(GameConfig& _GC) : G_Conf(_GC) {}; // Overriding Constructor to give reference to the Game Class's Config variable.
private:
	void SpecificRender() override;        // Overriding Function to Render the End State.
	bool CheckInput(char _Input) override; // Overriding Function to Check Inputs.
	void DrawEndScreen(); // Draws the End Screen
	void DrawDblN();	  // Draws Double or Nothing Screen
	bool _DblN_Played = false; // If Double or Nothing is finished.
	bool _Dbln_Set = false;	   // If Double or Nothing has been setup.
	bool _Holding = false;	   // If Double or Nothing is in the holding state.
	Card _RandCard;		// Stores the Random Card given to the Computer during Double or Nothing.
	Card _PlayerCard;	// Stores the Random Card given to the player during Double or Nothing.
	wstring _Result;	// Holds the current result message.
	GameConfig& G_Conf; // Reference to the Game Class's Config variable.
};