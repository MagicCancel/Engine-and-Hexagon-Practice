
#pragma once

#include "ActorC.h"
#include <SFML\Graphics.hpp>

class GameC;

class CursorC : public ActorC
{

private:

	sf::View *Camera;
	GameC* Game;

	int WorldActorFocus;

public:

	CursorC(sf::View *Camera, GameC* Game);

	void update();

	void FindClickedObject();

	void DebugDraw();
};