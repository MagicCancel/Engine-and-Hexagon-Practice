
#include "ReferenceMasterC.h"
#include "MessageHandlerC.h"
#include "P1PieceC.h"

#include <iostream>


P1PieceC::P1PieceC()
{
	CreateGraphicComponent();
	GetGraphicComponent()->LoadTexture("Assets/CreatureTokenP1.png");

	CreateCreatureComponent(P1, "P1-Piece", sf::Vector2i(0, 0), 100, 10, 3, 3, 3, HERO, 10, 10, 10, 10);

	//CreateHighlightComponent();
	//GetHighlightComponent()->SetColor(200, 150, 100, 100);
	//HighlightComponent->SetRadius(2);

	state = IDLE;

	SetPieceHexPosition(0, 0);

	CreateCardDeckComponent();
	GetCardDeckComponent()->TESTFUNC(3);
}

P1PieceC::P1PieceC(sf::Vector2i Position)
{
	CreateGraphicComponent();
	GetGraphicComponent()->LoadTexture("Assets/CreatureTokenP1.png");

	CreateCreatureComponent(P1, "P1-Piece", Position, 100, 10, 3, 3, 3, HERO, 10, 10, 10, 10);

	CreateHighlightComponent();
	GetHighlightComponent()->SetColor(200, 150, 100, 100);

	state = IDLE;

	SetPieceHexPosition(Position.x, Position.y);

	CreateCardDeckComponent();
}

