
#include "CardDeckComponentC.h"

CardDeckComponentC::CardDeckComponentC()
{
	for (int i = 0; i < 10; ++i)
	{
		Deck.push(1);
	}

	for (int i = 0; i < 7; ++i)
	{
		Hand[i] = -1;
	}

	for (int i = 0; i < 5; ++i)
	{
		DrawFromDeck();
	}
}

CardDeckComponentC::~CardDeckComponentC()
{
	
}

HandS CardDeckComponentC::GetHand()
{
	HandS RetHand;

	for (int i = 0; i < 7; i++)
	{
		if (Hand[i] != -1)
		{
			RetHand.Cards[i] = Hand[i];
			RetHand.Size = i + 1;
		}
	}
	return RetHand;
}

void CardDeckComponentC::DrawFromDeck()
{
	int card = Deck.top();
	Deck.pop();

	//find an empty spot in the hand
	for (int i = 0; i < 7; ++i)
	{
		if (Hand[i] == -1)
		{
			Hand[i] = card;
			break;
		}
	}

}

void CardDeckComponentC::UseFromHand(int HandPos)
{
	//here is where the function to use the card would be
	Hand[HandPos] = -1;
}

void CardDeckComponentC::DiscardFromHand(int HandPos)
{
	Hand[HandPos] = -1;
}

void CardDeckComponentC::DiscardHand()
{
	for (int i = 0; i < 7; ++i)
	{
		Hand[i] = -1;
	}
}

void CardDeckComponentC::TESTFUNC(int j)
{
	for (int i = 0; i < 7; ++i)
	{
		if (i < j)
			Hand[i] = 1;
		else
			Hand[i] = -1;
	}
}