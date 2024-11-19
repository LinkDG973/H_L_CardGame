#pragma once

class Card {
public:
	Card(char _S, int _V) 
		: _Suit(_S), _Value(_V) {};
	~Card() {};

private:

	char _Suit = '_';
	unsigned __int8 _Value = 0;

};

