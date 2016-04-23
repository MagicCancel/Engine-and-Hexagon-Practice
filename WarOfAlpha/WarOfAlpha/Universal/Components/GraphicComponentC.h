
#pragma once

#include "Universal.h"
#include "SFML\Graphics.hpp"

class GraphicComponentC
{
private:

	ClipS clip;

public:

	GraphicComponentC();
	~GraphicComponentC();
	
	bool LoadTexture(std::string FileAddress);
	bool LoadTexture(std::string FileAddress, sf::Vector2u position, sf::Vector2u dimensions);

	ClipS *GetClip();
	sf::Texture *GetTextue();

	void SetColor(int r, int g, int b, int a);

	void draw(sf::RenderTarget& target, sf::RenderStates states, sf::Transform ActorTrans) const;

};