#pragma once

class Card {
public:
	Card() {};
	Card(wchar_t _S, int _V)
		: _Suit(_S), _Value(_V) {};
	~Card() {};

	wchar_t GetSuit() { return _Suit; }
	int GetVal() { return _Value; }

	std::wstring& GetCardGraphic(int _Index) { return _Graphic[_Index]; }

	bool GetFlipState() { return _Flipped; }
	void SetFlipState(bool _Val) { _Flipped = _Val; }

private:
	bool _Flipped = false;
	wchar_t _Suit = L'_';
	unsigned __int8 _Value = 0;
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

