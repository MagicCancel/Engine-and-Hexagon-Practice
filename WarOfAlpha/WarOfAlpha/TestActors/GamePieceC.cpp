
#include "GamePieceC.h"

#include <iostream>

GamePieceC::GamePieceC()
//IdleThread(&GamePieceC::IdleThreadFunc, this),
//FocusedThread(&GamePieceC::FocusedThreadFunc, this)
{
	/*
	CreateGraphicComponent();
	GetGraphicComponent()->LoadTexture("Assets/CreatureTokenP1.png");
	CreateCreatureComponent(P1, "Game-Piece", sf::Vector2u(0, 0), 100, 10, 3, 3, 3, HERO, 10, 10, 10, 10);
	CreateHighlightComponent();
	GetHighlightComponent()->SetColor(200, 150, 100, 100);
	*/

	state = IDLE;
	//IdleThread.launch();

	//SetPieceHexPosition(0, 0);
}

GamePieceC::GamePieceC(sf::Vector2u Position)
//IdleThread(&GamePieceC::IdleThreadFunc, this),
//FocusedThread(&GamePieceC::FocusedThreadFunc, this)
{
	/*
	CreateGraphicComponent();
	GetGraphicComponent()->LoadTexture("Assets/CreatureTokenP1.png");
	CreateCreatureComponent(P1, "Game-Piece", Position, 100, 10, 3, 3, 3, HERO, 10, 10, 10, 10);
	CreateHighlightComponent();
	GetHighlightComponent()->SetColor(200, 150, 100, 100);
	*/

	state = IDLE;
	//IdleThread.launch();

	//SetPieceHexPosition(Position.x, Position.y);
}

GamePieceC::~GamePieceC()
{
	//std::cout << "Game Piece Terminater called\n";
	//IdleThread.terminate();
	//FocusedThread.terminate();
}

/*
void GamePieceC::IdleThreadFunc()
{
	//wait
	while (Input::LeftClickPressed) {}
	//and go
	while (true)
	{

		if (Input::LeftClickPressed)
		{
			if (Input::MouseHexPosition.x == GetCreatureComponent()->GetHexPosition().x &&
				Input::MouseHexPosition.y == GetCreatureComponent()->GetHexPosition().y)
			{

				//change to focused func
				state = State::FOCUSED;
				FocusedThread.launch();
				return;
			}
		}

	}
}

void GamePieceC::FocusedThreadFunc()
{

	//turn on the highlight!
	GetHighlightComponent()->SetRadius(GetCreatureComponent()->GetLandMovement());
	GetHighlightComponent()->ActivateHighlight();

	//wait
	while (Input::LeftClickPressed) {}
	//and go
	while (true)
	{
		//std::cout << "P1 THREAD LIVES\n";
		if (Input::LeftClickPressed)
		{
			//Find out if this spot is occupied by a unit already
			int dist = GetHexDist(GetCreatureComponent()->GetHexPosition().x, GetCreatureComponent()->GetHexPosition().y, Input::MouseHexPosition.x, Input::MouseHexPosition.y);

			if (dist != 0 && dist <= GetHighlightComponent()->GetRadius())
			{
				//If this space is occupied, we do not advance
				int unit = ReferenceMaster->findReference(sf::Vector2u(Input::MouseHexPosition.x, Input::MouseHexPosition.y));
				if (unit == -1)
				{
					//Move duh unit
					SetPieceHexPosition(Input::MouseHexPosition.x, Input::MouseHexPosition.y);
				}
				else
				{
					//this unit was occupied, now we need to find out if this slot is an enemy that can be attacked
					ActorC* actor = ReferenceMaster->getReference(unit);
					POwner actOwner = actor->GetCreatureComponent()->GetOwner();
					POwner selfOwner = GetCreatureComponent()->GetOwner();
					if (actOwner != POwner::P0 && actOwner != selfOwner)
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
			GetHighlightComponent()->DeactivateHighlight();

			state = State::IDLE;
			IdleThread.launch();
			return;
		}

	}
}

*/

void GamePieceC::update()
{

}

void GamePieceC::SetPieceHexPosition(int nx, int ny)
{
	//Get the world coordinates
	sf::Vector2f hexPos = ConvertCoordsHexToWorld(nx, ny);

	//and alter position
	setPosition(hexPos.x, hexPos.y);
	GetCreatureComponent()->SetHexPosition(sf::Vector2i(nx, ny));
}

void GamePieceC::MovePieceHexPosition(int dx, int dy)
{
	//alter the currrent coordinates
	sf::Vector2i hexPos = GetCreatureComponent()->GetHexPosition();
	hexPos.x += dx;
	hexPos.y += dy;

	//just call this fun
	SetPieceHexPosition(hexPos.x, hexPos.y);
}

void GamePieceC::OnClick()
{
	GetHighlightComponent()->SetRadius(GetCreatureComponent()->GetLandMovement());
	GetHighlightComponent()->ActivateHighlight();
	state = State::FOCUSED;
}

void GamePieceC::OnFocusClick()
{

	//Find out if this spot is occupied by a unit already
	int dist = GetHexDist(GetCreatureComponent()->GetHexPosition().x, GetCreatureComponent()->GetHexPosition().y, Input::MouseHexPosition.x, Input::MouseHexPosition.y);

	if (dist != 0 && dist <= GetHighlightComponent()->GetRadius())
	{
		//If this space is occupied, we do not advance
		int unit = ReferenceMaster->findReference(sf::Vector2i(Input::MouseHexPosition.x, Input::MouseHexPosition.y));
		if (unit == -1)
		{
			//hack summon code
			if (Input::RightClickDown)
			{
				MessageHandler->QueueMessage(1, 0, sf::Vector2i(Input::MouseHexPosition.x, Input::MouseHexPosition.y));
			}
			else
			{
				//Move duh unit
				SetPieceHexPosition(Input::MouseHexPosition.x, Input::MouseHexPosition.y);
			}
		}
		else
		{
			//this unit was occupied, now we need to find out if this slot is an enemy that can be attacked
			ActorC* actor = ReferenceMaster->getReference(unit);
			POwner actOwner = actor->GetCreatureComponent()->GetOwner();
			POwner selfOwner = GetCreatureComponent()->GetOwner();
			if (actOwner != POwner::P0 && actOwner != selfOwner)
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
	GetHighlightComponent()->DeactivateHighlight();
	state = State::IDLE;
	return;

}