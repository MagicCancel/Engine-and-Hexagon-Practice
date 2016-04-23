
#include "EssenceNodeC.h"

EssenceNodeC::EssenceNodeC(sf::Vector2i Position)
{

	CreateGraphicComponent();
	GetGraphicComponent()->LoadTexture("Assets/EssenceNodeToken.png");

	CreateCreatureComponent(P0, "Essence Node", Position, 1000, 1000, 0, 0, 0, HERO, 0, 0, 0, 0);

	CreateHighlightComponent();
	GetHighlightComponent()->SetColor(100, 200, 100, 100);
	//GetHighlightComponent()->SetRadius(1);
	GetHighlightComponent()->ActivateHighlight();
	
	int xp = Position.x;
	int yp = Position.y;

	int cx = (xp)* HexData::a;
	int cy = (yp)* (HexData::s + HexData::h);
	if (yp % 2 == 1)
		cx += HexData::r;

	setPosition(cx + 30, cy + 34);
}

EssenceNodeC::~EssenceNodeC()
{

}

void EssenceNodeC::update()
{
	if (GameState->GetTurn() == TG)
	{
		GameState->AddScore1(50);
		GameState->AddScore2(20);
	}
}