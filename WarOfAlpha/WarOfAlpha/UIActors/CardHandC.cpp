
#include "CardHandC.h"
#include "ReferenceMasterC.h"
#include "MessageHandlerC.h"
#include "Actor\Cursor.h"

CardHandC::CardHandC()
{
	MapActor(0, new ActorC());
	GetActorFromMap(0)->CreateGraphicComponent();
	GetActorFromMap(0)->GetGraphicComponent()->LoadTexture("Assets/CardHand.png");

	for (int i = 1; i <= 7; ++i)
	{
		MapActor(i, new ActorC());
		GetActorFromMap(i)->CreateGraphicComponent();
		GetActorFromMap(i)->GetGraphicComponent()->LoadTexture("Assets/Card.png");
		GetActorFromMap(i)->setPosition(125 * (-4 + i), 0);
		GetActorFromMap(i)->GetGraphicComponent()->SetColor(255, 255, 255, 0);
	}

}

void CardHandC::update()
{
	if (GameState->IsFocused())
	{
		if (GameState->GetFocusedActor() != ActorWithDeck)
		{
			ActorWithDeck = GameState->GetFocusedActor();
		}

		UpdateHand();

	}
	else
	{
		if (ActorWithDeck != nullptr)
		{
			ActorWithDeck = nullptr;
			ClearHand();
		}
	}
}

void CardHandC::UpdateHand()
{
	HandS hand = ActorWithDeck->GetCardDeckComponent()->GetHand();
	for (int i = 0; i < 7; i++)
	{
		/*
		if (i < hand)
			GetActorFromMap(i)->GetGraphicComponent()->SetColor(255, 255, 255, 255);
		else
			GetActorFromMap(i)->GetGraphicComponent()->SetColor(255, 255, 255, 0);
		*/
	}
}

void CardHandC::ClearHand()
{
	for (int i = 1; i <= 7; ++i)
		GetActorFromMap(i)->GetGraphicComponent()->SetColor(255, 255, 255, 0);

}

void CardHandC::OnClick()
{
	
	if (ActorWithDeck == nullptr)
		return;

	for (int i = 1; i <= 7; ++i)
	{
		if (GetActorFromMap(i)->IsMouseInDimension(getPosition()) == true)
		{
			std::cout << "Using card " << i << std::endl;
			return;
		}
	}

}