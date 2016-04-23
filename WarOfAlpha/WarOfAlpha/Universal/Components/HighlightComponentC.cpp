#include "HighlightComponentC.h"
#include <iostream>

//Constructor
HighlightComponentC::HighlightComponentC()
{
	clip = ClipS();
	clip.loadFile("Assets/whitelight.png");
	active = false;
	
	//This line is kind of a hack... fix later
	m_vertices = clip.quad;

	SetRadius(1);

	red = 0;
	green = 0;
	blue = 0;
	alpha = 100;

}

//Destructor
HighlightComponentC::~HighlightComponentC()
{

}

void HighlightComponentC::ActivateHighlight()
{
	active = true;
}

void HighlightComponentC::DeactivateHighlight()
{
	active = false;
}

void HighlightComponentC::ToggleHighlight()
{
	active = !active;
}

void HighlightComponentC::SetRadius(uint NewRadius)
{
	radius = NewRadius;

	//Discern how many hexagons the new radius would highlight
	int sum = 1;
	for (int i = 1; i <= NewRadius; i++)
		sum += i;
	sum *= 6;

	//Resize the vertex to how many hexagons can be highlighted
	m_vertices.clear();
	m_vertices.resize(sum * 4);

	std::vector <sf::Vector2i> HexVec;

	GetHexSpots(radius, HexVec, 0, 0);

	for (int i = 0; i < HexVec.size(); ++i)
	{

		sf::Vertex* quad = &m_vertices[i * 4];

		sf::Vector2f c = ConvertCoordsHexToWorld(HexVec[i]);
		
		//Now we need to figure out the location of every highlighted hexagon in the new radius and then fill in the space data 				
		quad[0].position = sf::Vector2f(c.x - 64, c.y - 70);
		quad[1].position = sf::Vector2f(c.x, c.y - 70);
		quad[2].position = sf::Vector2f(c.x, c.y);
		quad[3].position = sf::Vector2f(c.x - 64, c.y);

		quad[0].texCoords = sf::Vector2f(0, 0); quad[1].texCoords = sf::Vector2f(64, 0);
		quad[2].texCoords = sf::Vector2f(64, 70); quad[3].texCoords = sf::Vector2f(0, 70);

		quad[0].color.r = red; quad[0].color.g = green; quad[0].color.b = blue;	quad[0].color.a = alpha;
		quad[1].color.r = red; quad[1].color.g = green; quad[1].color.b = blue;	quad[1].color.a = alpha;
		quad[2].color.r = red; quad[2].color.g = green; quad[2].color.b = blue;	quad[2].color.a = alpha;
		quad[3].color.r = red; quad[3].color.g = green; quad[3].color.b = blue;	quad[3].color.a = alpha;
	}
				
}

unsigned int HighlightComponentC::GetRadius()
{
	return radius;
}

void HighlightComponentC::SetColor(unsigned int r, unsigned int g, unsigned int b)
{
	red = r;
	green = g;
	blue = b;

	for (int i = 0; i < m_vertices.getVertexCount(); ++i)
	{
		m_vertices[i].color.r = red;
		m_vertices[i].color.g = green;
		m_vertices[i].color.b = blue;
		m_vertices[i].color.a = alpha;
	}
}

void HighlightComponentC::SetColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	red = r;
	green = g;
	blue = b;
	alpha = a;

	for (int i = 0; i < m_vertices.getVertexCount(); ++i)
	{
		m_vertices[i].color.r = red;
		m_vertices[i].color.g = green;
		m_vertices[i].color.b = blue;
		m_vertices[i].color.a = alpha;
	}
}

bool HighlightComponentC::IsActive()
{
	return active;
}

void HighlightComponentC::draw(sf::RenderTarget& target, sf::RenderStates states, sf::Transform ActorTrans) const
{
	// apply the entity's transform -- combine it with the one that was passed by the caller
	states.transform *= ActorTrans; // getTransform() is defined by sf::Transformable

	// apply the texture
	states.texture = &clip.texture;

	// you may also override states.shader or states.blendMode if you want

	// draw the vertex array
	target.draw(m_vertices, states);
	//target.draw(clip.quad, states);

}

