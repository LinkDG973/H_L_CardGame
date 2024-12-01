#pragma once
//====================================================================================
// NAME: Card.h
// DESC: Contains Card Class
// AUTH: Oliver Callaghan
//====================================================================================

// SUMMARY: Card Class Object used to store / manage functions and variables relating to cards.
class Card {
public:
	Card() {};
	Card(wchar_t _S, int _V) : _Suit(_S), _Value(_V) {}; // Constructor initalises card with a suit and value
	~Card() {};

	wchar_t GetSuit() { return _Suit; } // Returns Card Suit
	int GetVal() { return _Value; }		// Returns Card Value

	// SUMMARY: Returns a line of the card's graphic by the specified index.
	// PARAMETERS: INT - Specified Index.
	// RETURNS: WSTRING & - Line of Card's Graphic.
	std::wstring& GetCardGraphic(int _Index) { return _Graphic[_Index]; }

	bool GetFlipState() { return _Flipped; }		  // Returns Flip State
	void SetFlipState(bool _Val) { _Flipped = _Val; } // Sets Flip State
	
	bool GetPlayedState() { return _Played; }		   // Returns Played State
	void SetPlayedState(bool _Val) { _Played = _Val; } // Sets Played State

private:
	bool _Flipped = false;		// FlipState - If the facedown graphic should be displayed or the card's relative graphic.
	wchar_t _Suit = L'_';		// Card's relative Suit  (♠, ♦, ♥, ♣, J) 
	unsigned __int8 _Value = 0; // Card's relative Value (1-14)
	bool _Played = false;		// PlayedState - If the card has been played in the current game session or not.
	// Storage for the Card's relative graphic.
	std::wstring _Graphic[CARD_GRAPHIC_SIZE] = {
		L"┌─────────┐",
		L"│         │", 
		L"│         │", 
		L"│         │", 
		L"│         │", 
		L"│         │", 
		L"└─────────┘"
	};
};