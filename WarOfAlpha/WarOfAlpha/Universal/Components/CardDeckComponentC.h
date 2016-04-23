
#pragma once

#include <stack>

struct HandS
{
	int Size;
	int Cards[7];
	HandS()
	{
		Size = 0;
		for (int i = 0; i < 7; ++i)
			Cards[i] = -1;
	}
};

class CardDeckComponentC
{

private:

	std::stack <int> Deck;

	int Hand[7];

public:

	CardDeckComponentC();

	~CardDeckComponentC();

	HandS GetHand();

	void DrawFromDeck();

	void UseFromHand(int HandPos);

	void DiscardFromHand(int HandPos);

	void DiscardHand();

	void TESTFUNC(int j);

};