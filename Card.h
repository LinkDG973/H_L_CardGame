#pragma once

class Card {
public:
	Card() {};
	Card(wchar_t _S, int _V)
		: _Suit(_S), _Value(_V) {};
	~Card() {};

	wchar_t GetSuit() { return _Suit; }
	int GetVal() { return _Value; }

private:

	wchar_t _Suit = L'_';
	unsigned __int8 _Value = 0;

};

