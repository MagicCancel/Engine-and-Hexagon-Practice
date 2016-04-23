
#include "Cursor.h"
#include "Game/GameC.h"

#include <iostream>
#include <math.h>

CursorC::CursorC(sf::View *CameraPtr, GameC* GamePtr) :
Camera(CameraPtr),
Game(GamePtr)
{
	WorldActorFocus = -1;

	CreateGraphicComponent();
	GetGraphicComponent()->LoadTexture("Assets/Cursor.png");

	CreateHighlightComponent();
	GetHighlightComponent()->SetColor(100, 0, 100, 50);
	GetHighlightComponent()->ActivateHighlight();
	GetHighlightComponent()->SetRadius(2);
}

void CursorC::update() //HEXAGONS YO!
{

	if (Input::KeysPressed[sf::Keyboard::Up])
	{
		unsigned int r = GetHighlightComponent()->GetRadius();
		GetHighlightComponent()->SetRadius(r + 1);
	}

	if (Input::KeysPressed[sf::Keyboard::Down])
	{
		unsigned int r = GetHighlightComponent()->GetRadius();
		if (r != 0)
			GetHighlightComponent()->SetRadius(r - 1);
	}

	//Where is the mouse in world space?
	sf::Vector2f CamCent = Camera->getCenter();
	sf::Vector2i CursPos(CamCent.x - 640 + Input::MousePosition.x,
		                 CamCent.y - 360 + Input::MousePosition.y);
	
	//Use the world coordinates to figure out the hex position and position the cursor
	//ontop of that hexagon. Update the Input::MouseHexPosition while we're at it
	Input::MouseHexPosition = ConvertCoordsWorldToHex(CursPos.x, CursPos.y);
	sf::Vector2f WorldCoords = ConvertCoordsHexToWorld(Input::MouseHexPosition.x, Input::MouseHexPosition.y);
	setPosition(WorldCoords.x, WorldCoords.y);

	//Now we need to see if we're selecting anything
	if (Input::LeftClickPressed)
		FindClickedObject();
}

void CursorC::FindClickedObject()
{
	//First we check the screen actors as they are essentially the UI and UI takes priority!
	for (auto itr = Game->ScreenActorMap.begin(); itr != Game->ScreenActorMap.end(); ++itr)
	{
		if (itr->second->IsMouseInDimension() == true)
		{
			std::cout << "GOT A HIT WITH " << itr->first << std::endl;
			itr->second->OnClick();
			return;
		}
	}

	//are we focused on an actor already?
	if (GameState->IsFocused() == true)
	{
		GameState->GetFocusedActor()->OnFocusClick();
		GameState->ClearFocusedActor();
		return;
	}

	//Else, check the world actors on the screen!
	int ref = ReferenceMaster->findReference(Input::MouseHexPosition.x, Input::MouseHexPosition.y);
	//std::cout << Input::MouseHexPosition.x << ", " <<Input::MouseHexPosition.y << " -> " << ref << "\n";
	if (ref != -1)
	{
		ActorC* Act = ReferenceMaster->getReference(ref);
		const Turn PlayerTurn = GameState->GetTurn();
		if ((PlayerTurn == T1 && Act->GetCreatureComponent()->GetOwner() == P1) || (PlayerTurn == T2 && Act->GetCreatureComponent()->GetOwner() == P2))
		{
			Act->OnClick();
			GameState->SetFocusedActor(Act);
		}
	}

}

void CursorC::DebugDraw()
{
	DrawText(std::to_string(Input::MouseHexPosition.x), 500, 20);
	DrawText(std::to_string(Input::MouseHexPosition.y), 515, 20);
}