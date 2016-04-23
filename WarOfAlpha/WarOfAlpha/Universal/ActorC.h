#pragma once

#include <SFML\Graphics.hpp>
#include "Components\GraphicComponentC.h"
#include "Components\CreatureComponentC.h"
#include "Components\HighlightComponentC.h"
#include "Components\CardDeckComponentC.h"

#include "Game\GameStateC.h"
#include "MessageHandlerC.h"
#include "ReferenceMasterC.h"

//#include "GameC.h"
#include "Universal.h"

class ActorC : public sf::Drawable, public sf::Transformable
{

	friend class MultiActorC;

private:
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	GraphicComponentC *GraphicComponent;
	CreatureComponentC *CreatureComponent;
	HighlightComponentC *HighlightComponent;
	CardDeckComponentC *CardDeckComponent;

public:
	GameStateC *GameState;
	ReferenceMasterC *ReferenceMaster;
	MessageHandlerC *MessageHandler;

	//Constructors
	ActorC();
	//Destructors
	~ActorC();
	
	bool CreateGraphicComponent();
	bool CreateCreatureComponent(POwner NewOwner, std::string NewName, sf::Vector2i NewHexPosition, ushort NewHealth, ushort NewResource,
		ushort NewLandMovement, ushort NewWaterMovement, ushort NewAirMovement,
		CType NewType, ushort NewChaosValue, ushort NewLightValue, ushort NewDarkValue, ushort NewEntropyValue);
	bool CreateHighlightComponent();
	bool CreateCardDeckComponent();

	bool HasGraphicComponent();
	bool HasCreatureComponent();
	bool HasHighlightComponent();
	bool HasCardDeckComponent();

	GraphicComponentC *GetGraphicComponent();
	CreatureComponentC *GetCreatureComponent();
	HighlightComponentC *GetHighlightComponent();
	CardDeckComponentC *GetCardDeckComponent();

	void Attach(GameStateC *GameStatePtr, ReferenceMasterC *ReferenceMasterPtr, MessageHandlerC *MessageHandlerPtr);

	virtual bool IsMouseInDimension();
	bool IsMouseInDimension(sf::Vector2f PosOffset);

	virtual void update() {};

	virtual void OnClick() {};
	virtual void OnFocusClick() {};

	virtual void DebugDraw() {};
};