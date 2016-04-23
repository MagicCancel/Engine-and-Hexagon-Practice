#pragma once

#include "Universal.h"
#include <SFML\Graphics.hpp>

typedef unsigned int uint;

class HighlightComponentC
{
private:

	ClipS clip;

	bool active;
	unsigned int radius;

	unsigned int red;
	unsigned int green;
	unsigned int blue;
	unsigned int alpha;

	sf::VertexArray m_vertices;

public:

	//Constructor
	HighlightComponentC();
	
	//Destructor
	~HighlightComponentC();

	//Turn on the highlight to be drawn
	void ActivateHighlight();
	//Turn off the highlight to be drawn
	void DeactivateHighlight();
	//Toggle the highlight to be drawn
	void ToggleHighlight();

	//Set the radius to be drawn
	void SetRadius(uint NewRadius);
	//Get the radius
	unsigned int GetRadius();

	bool IsActive();

	//Set the color!
	void SetColor(unsigned int r, unsigned int g, unsigned int b);
	void SetColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
	
	//Draw the highlight
	void draw(sf::RenderTarget& target, sf::RenderStates states, sf::Transform ActorTrans) const;


};