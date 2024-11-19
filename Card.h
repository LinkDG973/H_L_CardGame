#pragma once

class Card {
public:
	Card() {};
	Card(char _S, int _V) 
		: _Suit(_S), _Value(_V) {};
	~Card() {};

	char GetSuit() { return _Suit; }
	int GetVal() { return _Value; }

private:

	char _Suit = '_';
	unsigned __int8 _Value = 0;

};

