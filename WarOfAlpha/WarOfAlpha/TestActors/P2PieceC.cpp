
#include "ReferenceMasterC.h"
#include "MessageHandlerC.h"
#include "P2PieceC.h"

#include <iostream>

P2PieceC::P2PieceC()
{
	CreateGraphicComponent();
	GetGraphicComponent()->LoadTexture("Assets/CreatureToken.png");

	CreateCreatureComponent(P2, "P2 - Piece", sf::Vector2i(0, 0), 100, 10, 3, 3, 3, HERO, 10, 10, 10, 10);

	//CreateHighlightComponent();
	//GetHighlightComponent()->SetColor(100, 100, 200, 100);
	//HighlightComponent->SetRadius(2);

	state = IDLE;

	SetPieceHexPosition(0, 0);

	CreateCardDeckComponent();
	GetCardDeckComponent()->TESTFUNC(5);
}

P2PieceC::P2PieceC(sf::Vector2i Position)
{
	CreateGraphicComponent();
	GetGraphicComponent()->LoadTexture("Assets/CreatureTokenP2.png");

	CreateCreatureComponent(P2, "P2-Piece", Position, 100, 10, 3, 3, 3, HERO, 10, 10, 10, 10);

	CreateHighlightComponent();
	GetHighlightComponent()->SetColor(100, 100, 200, 100);

	state = IDLE;

	SetPieceHexPosition(Position.x, Position.y);

	CreateCardDeckComponent();

}

void P2PieceC::DebugDraw()
{
	const sf::Vector2f pos = getPosition();
	DrawSquare(pos.x + 10, pos.y + 10, 100, 100, 0, 0, 0, 255);
	DrawText("Henriette", pos.x + 10, pos.y + 10);
}