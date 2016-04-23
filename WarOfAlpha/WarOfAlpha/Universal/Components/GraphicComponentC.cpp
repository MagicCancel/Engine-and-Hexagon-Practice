
#include "GraphicComponentC.h"

GraphicComponentC::GraphicComponentC()
{
	//clip.quad = sf::VertexArray(sf::Quads, 4);
	clip = ClipS();
}

GraphicComponentC::~GraphicComponentC()
{

}

ClipS *GraphicComponentC::GetClip()
{
	return &clip;
}

sf::Texture *GraphicComponentC::GetTextue()
{
	return &clip.texture;
}

bool GraphicComponentC::LoadTexture(std::string FileAddress)
{
	if (!clip.loadFile(FileAddress))
	{
		return false;
	}

	return true;
}

bool GraphicComponentC::LoadTexture(std::string FileAddress, sf::Vector2u position, sf::Vector2u dimensions)
{
	if (!clip.loadFile(FileAddress, position, dimensions))
	{
		return false;
	}

	return true;
}

void GraphicComponentC::SetColor(int r, int g, int b, int a)
{
	clip.setColor(r, g, b, a);
}

void GraphicComponentC::draw(sf::RenderTarget& target, sf::RenderStates states, sf::Transform ActorTrans) const
{

	// apply the entity's transform -- combine it with the one that was passed by the caller
	states.transform *= ActorTrans; // getTransform() is defined by sf::Transformable
	
	// apply the texture
	states.texture = &clip.texture;

	// you may also override states.shader or states.blendMode if you want

	// draw the vertex array
	target.draw(clip.quad, states);
	
}