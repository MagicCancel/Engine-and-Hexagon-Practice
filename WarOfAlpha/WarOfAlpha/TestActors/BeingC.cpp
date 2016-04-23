
#include "ReferenceMasterC.h"
#include "MessageHandlerC.h"
#include "BeingC.h"

#include <iostream>

BeingC::BeingC()
{
	CreateGraphicComponent();
	GetGraphicComponent()->LoadTexture("Assets/CreatureToken.png");

	CreateCreatureComponent(P1, "Thing", sf::Vector2u(2, 2), 100, 10, 3, 3, 3, HERO, 10, 10, 10, 10);

	CreateHighlightComponent();
	GetHighlightComponent()->SetColor(100, 100, 200, 100);
	//HighlightComponent->SetRadius(2);

	state = IDLE;

	int xp = 2;
	int yp = 2;

	int cx = (xp) * HexData::a;
	int cy = (yp) * (HexData::s + HexData::h);
	if (yp % 2 == 1)
		cx += HexData::r;

	setPosition(cx + 30, cy + 34);

}

BeingC::BeingC(sf::Vector2u Position)
{
	CreateGraphicComponent();
	GetGraphicComponent()->LoadTexture("Assets/CreatureToken.png");

	CreateCreatureComponent(P1, "Thing", Position, 100, 10, 3, 3, 3, HERO, 10, 10, 10, 10);

	CreateHighlightComponent();
	GetHighlightComponent()->SetColor(100, 100, 200, 100);
	//HighlightComponent->SetRadius(2);

	state = IDLE;

	int xp = Position.x;
	int yp = Position.y;

	int cx = (xp)* HexData::a;
	int cy = (yp)* (HexData::s + HexData::h);
	if (yp % 2 == 1)
		cx += HexData::r;

	setPosition(cx + 30, cy + 34);

}


int GetHexDist(int q1, int r1, int q2, int r2)
{
	//convert them to cube
	int x1 = q1 - (r1 - (r1 & 1)) / 2;
	int	z1 = r1;
	int	y1 = -x1 - z1;

	int x2 = q2 - (r2 - (r2 & 1)) / 2;
	int	z2 = r2;
	int	y2 = -x2 - z2;

	return (abs(x1 - x2) + abs(y1 - y2) + abs(z1 - z2)) / 2;
}

void BeingC::update()
{
	//mouse click?
	if (Input::LeftClickPressed)
	{

		if (state == State::IDLE)
		{
			if (Input::MouseHexPosition.x == GetCreatureComponent()->GetHexPosition().x &&
				Input::MouseHexPosition.y == GetCreatureComponent()->GetHexPosition().y)
			{
				state = State::FOCUSED;
				GetHighlightComponent()->ActivateHighlight();
				GetHighlightComponent()->SetRadius(GetCreatureComponent()->GetLandMovement());
			}
		}
		else if (state == State::FOCUSED)
		{
			//Find out if this spot is occupied by a unit already
			int dist = GetHexDist(GetCreatureComponent()->GetHexPosition().x, GetCreatureComponent()->GetHexPosition().y, Input::MouseHexPosition.x, Input::MouseHexPosition.y);
			
			if (dist != 0 && dist <= GetHighlightComponent()->GetRadius())
			{
				//If this space is occupied, we do not advance
				int unit = ReferenceMaster->findReference(sf::Vector2u(Input::MouseHexPosition.x, Input::MouseHexPosition.y));
				if (unit == -1)
				{
					//Move dun unit
					SetBeingPosition(Input::MouseHexPosition.x, Input::MouseHexPosition.y);
				}
				else
				{
					//this unit was occupied, now we need to find out if this slot is an enemy that can be attacked
					ActorC* actor = ReferenceMaster->getReference(unit);
					if (actor->GetCreatureComponent()->GetOwner() != POwner::P0)
					{
						ushort targetHealth = actor->GetCreatureComponent()->GetHealth();
						if (targetHealth <= 60)
						{
							actor->GetCreatureComponent()->SetHealth(0);
							MessageHandler->QueueMessage(0, unit, sf::Vector2i(0, 0));
							std::cout << "It's dead now\n";
						}
						else
						{
							actor->GetCreatureComponent()->SetHealth(targetHealth - 60);
							std::cout << "It's at " << actor->GetCreatureComponent()->GetHealth() << " now\n";
						}
					}
				}
				
			}

			//Regardless, we clicked and that means this actor is no longer the focus
			state = State::IDLE;
			GetHighlightComponent()->DeactivateHighlight();

		}
	}
	
	//46,26 is the final corner tile
	if (Input::KeysPressed[sf::Keyboard::W] || Input::KeysPressed[sf::Keyboard::A] || Input::KeysPressed[sf::Keyboard::S] || Input::KeysPressed[sf::Keyboard::D])
	{
		sf::Vector2u hexPos = GetCreatureComponent()->GetHexPosition();

		if (Input::KeysPressed[sf::Keyboard::W] && hexPos.y != 0)
			MoveBeing(0, -1);
		else if (Input::KeysPressed[sf::Keyboard::A] && hexPos.x != 0)
			MoveBeing(-1, 0);
		else if (Input::KeysPressed[sf::Keyboard::S] && hexPos.y != 26)
			MoveBeing(0, 1);
		else if (Input::KeysPressed[sf::Keyboard::D] && hexPos.x != 46)
			MoveBeing(1, 0);
	}

}

void BeingC::SetBeingPosition(int nx, int ny)
{
	sf::Vector2u hexPos = GetCreatureComponent()->GetHexPosition();

	hexPos.x = nx;
	hexPos.y = ny;
	int cx = (hexPos.x)* HexData::a;
	int cy = (hexPos.y)* (HexData::s + HexData::h);

	if (hexPos.y % 2 == 1)
		cx += HexData::r;

	setPosition(cx + 30, cy + 34);

	GetCreatureComponent()->SetHexPosition(hexPos);
}

void BeingC::MoveBeing(int dx, int dy)
{
	sf::Vector2u hexPos = GetCreatureComponent()->GetHexPosition();

	hexPos.x += dx;
	hexPos.y += dy;
	int cx = (hexPos.x)* HexData::a;
	int cy = (hexPos.y)* (HexData::s + HexData::h);
	
	if (hexPos.y % 2 == 1)
		cx += HexData::r;

	setPosition(cx + 30, cy + 34);

	GetCreatureComponent()->SetHexPosition(hexPos);
}