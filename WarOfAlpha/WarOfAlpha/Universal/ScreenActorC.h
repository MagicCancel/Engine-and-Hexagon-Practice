
#pragma once

#include <SFML\Graphics.hpp>
#include "Input.h"
#include "ActorC.h"

class ScreenActorC :ActorC
{

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2u ScreenCoordiantes;
	ClipS clip;

public:

	//Constructors
	ScreenActorC();
	//Destructors
	~ScreenActorC();

	bool LoadTexture(std::string FileAddress);
	bool LoadTexture(std::string FileAddress, sf::Vector2u position, sf::Vector2u dimensions);

	void SetScreenCoordiantes(sf::Vector2u);
	void SetScreenCoordiantes(unsigned int x, unsigned int y);

};