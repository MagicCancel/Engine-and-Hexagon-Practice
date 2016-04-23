#pragma once

#include "MultiActorC.h"

class CursorC;

class CardHandC : public MultiActorC
{

private:

	ActorC *ActorWithDeck;

public:

	CardHandC();

	void update();

	void UpdateHand();
	void ClearHand();

	void OnClick();
};