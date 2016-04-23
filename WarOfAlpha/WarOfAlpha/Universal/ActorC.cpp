
#include "ActorC.h"
#include <iostream>

ActorC::ActorC()
{
	GraphicComponent = nullptr;
	CreatureComponent = nullptr;
	HighlightComponent = nullptr;
	CardDeckComponent = nullptr;
}

ActorC::~ActorC()
{
	if (HasGraphicComponent())
	{
		delete GraphicComponent;
		GraphicComponent = nullptr;
		std::cout << "Graphics deleted\n";
	}

	if (HasCreatureComponent())
	{
		delete CreatureComponent;
		CreatureComponent = nullptr;
		std::cout << "Creature deleted\n";
	}

	if (HasHighlightComponent())
	{
		delete HighlightComponent;
		HighlightComponent = nullptr;
		std::cout << "Highlightg deleted\n";
	}

	if (HasCardDeckComponent())
	{
		delete CardDeckComponent;
		CardDeckComponent = nullptr;
		std::cout << "Deck deleted\n";
	}

	GameState = nullptr;
	ReferenceMaster = nullptr;
	MessageHandler = nullptr;
}

bool ActorC::CreateGraphicComponent()
{
	if (GraphicComponent != nullptr)
	{
		std::cout << "ERROR: GRAPHIC COMPONENT ALREADY EXISTS!\n";
		return false;
	}

	GraphicComponent = new GraphicComponentC();
	if (GraphicComponent != nullptr)
	{
		//std::cout << "SUCCESSFULY CREATED A GRAPHIC COMPONENT!\n";
		return true;
	}
	else
	{
		std::cout << "FAILED TO CREATE GRAPHIC COMPONENT!\n";
		return false;
	}
}

bool ActorC::CreateCreatureComponent(POwner NewOwner, std::string NewName, sf::Vector2i NewHexPosition, ushort NewHealth, ushort NewResource,
	ushort NewLandMovement, ushort NewWaterMovement, ushort NewAirMovement,
	CType NewType, ushort NewChaosValue, ushort NewLightValue, ushort NewDarkValue, ushort NewEntropyValue)
{

	if (CreatureComponent != nullptr)
	{
		std::cout << "ERROR: CREATURE COMPONENT ALREADY EXISTS!\n";
		return false;
	}

	CreatureComponent = new CreatureComponentC(NewOwner, NewName, NewHexPosition, NewHealth, NewResource, NewLandMovement, NewWaterMovement, NewAirMovement, NewType, NewChaosValue, NewLightValue, NewDarkValue, NewEntropyValue);
	if (CreatureComponent != nullptr)
	{
		//std::cout << "SUCCESSFULY CREATED A CREATURE COMPONENT!\n";
		return true;
	}
	else
	{
		std::cout << "FAILED TO CREATE CREATURE COMPONENT!\n";
		return false;
	}
}

bool ActorC::CreateHighlightComponent()
{
	if (HighlightComponent != nullptr)
	{
		std::cout << "ERROR: HIGHLIGHT COMPONENT ALREADY EXISTS!\n";
		return false;
	}

	HighlightComponent = new HighlightComponentC();
	if (HighlightComponent != nullptr)
	{
		//std::cout << "SUCCESSFULY CREATED A HIGHLIGHT COMPONENT!\n";
		return true;
	}
	else
	{
		std::cout << "FAILED TO CREATE HIGHLIGHT COMPONENT!\n";
		return false;
	}
}

bool ActorC::CreateCardDeckComponent()
{
	if (CardDeckComponent != nullptr)
	{
		std::cout << "ERROR: CARDDECK COMPONENT ALREADY EXISTS!\n";
		return false;
	}

	CardDeckComponent = new CardDeckComponentC();
	if (CardDeckComponent != nullptr)
	{
		//std::cout << "SUCCESSFULY CREATED A CARDDECK COMPONENT!\n";
		return true;
	}
	else
	{
		std::cout << "FAILED TO CREATE CARDDECK COMPONENT!\n";
		return false;
	}
}

bool ActorC::HasGraphicComponent()
{
	if (GraphicComponent != nullptr)
		return true;

	return false;
}

bool ActorC::HasCreatureComponent()
{
	if (CreatureComponent != nullptr)
		return true;

	return false;
}

bool ActorC::HasHighlightComponent()
{
	if (HighlightComponent != nullptr)
		return true;

	return false;
}

bool ActorC::HasCardDeckComponent()
{
	if (CardDeckComponent != nullptr)
		return true;

	return false;
}

GraphicComponentC* ActorC::GetGraphicComponent()
{
	return GraphicComponent;
}

CreatureComponentC* ActorC::GetCreatureComponent()
{
	return CreatureComponent;
}

HighlightComponentC* ActorC::GetHighlightComponent()
{
	return HighlightComponent;
}

CardDeckComponentC* ActorC::GetCardDeckComponent()
{
	return CardDeckComponent;
}

void ActorC::Attach(GameStateC *GameStatePtr, ReferenceMasterC *ReferenceMasterPtr, MessageHandlerC *MessageHandlerPtr)
{
	GameState = GameStatePtr;
	ReferenceMaster = ReferenceMasterPtr;
	MessageHandler = MessageHandlerPtr;
}

//THIS FUNCTION MUST BE CHANGED LATER! AS IT IS NOW, IT'S ONLY FOR TESTING PURPOSES
bool ActorC::IsMouseInDimension()
{
	if (HasGraphicComponent())
	{
		//Get the quad and position of the actor and use them to find it's dimensions
		sf::VertexArray square = GetGraphicComponent()->GetClip()->quad;

		sf::Vector2f Pos = getPosition();

		//What are the dimensions of this actor?
		sf::Vector2i ActMin(Pos.x + square[0].position.x, Pos.y + square[0].position.y);
		sf::Vector2i ActMax(Pos.x + square[2].position.x, Pos.y + square[2].position.y);

		if (Input::MousePosition.x >= ActMin.x && Input::MousePosition.x <= ActMax.x &&
			Input::MousePosition.y >= ActMin.y && Input::MousePosition.y <= ActMax.y)
		{
			return true;
		}
	}
	return false;
}
bool ActorC::IsMouseInDimension(sf::Vector2f PosOffset)
{
	if (HasGraphicComponent())
	{
		//Get the quad and position of the actor and use them to find it's dimensions
		sf::VertexArray square = GetGraphicComponent()->GetClip()->quad;
		
		sf::Vector2f Pos = getPosition() + PosOffset;

		//What are the dimensions of this actor?
		sf::Vector2i ActMin(Pos.x + square[0].position.x, Pos.y + square[0].position.y);
		sf::Vector2i ActMax(Pos.x + square[2].position.x, Pos.y + square[2].position.y);

		if (Input::MousePosition.x >= ActMin.x && Input::MousePosition.x <= ActMax.x &&
			Input::MousePosition.y >= ActMin.y && Input::MousePosition.y <= ActMax.y)
		{
			return true;
		}
	}
	return false;
}

void ActorC::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (GraphicComponent != nullptr)
	{
		GraphicComponent->draw(target, states, getTransform());
	}

	if (HighlightComponent != nullptr && HighlightComponent->IsActive())
	{
		HighlightComponent->draw(target, states, getTransform());
	}	
}