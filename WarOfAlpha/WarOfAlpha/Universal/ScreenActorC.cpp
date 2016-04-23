
#include "ScreenActorC.h"


ScreenActorC::ScreenActorC()
{
	clip.quad = sf::VertexArray(sf::Quads, 4);
	ScreenCoordiantes = sf::Vector2u(0, 0);
}

ScreenActorC::~ScreenActorC()
{

}

void ScreenActorC::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the entity's transform -- combine it with the one that was passed by the caller
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

	// apply the texture
	states.texture = &clip.texture;

	// you may also override states.shader or states.blendMode if you want
	
	sf::View ThisView = target.getView();
	sf::Vector2f ScreenCenter = ThisView.getCenter();
	sf::Vector2f ScreenSize = ThisView.getSize();
	sf::Vector2u TextureSize = clip.texture.getSize();
	float startX = ScreenCenter.x - ScreenSize.x;
	float startY = ScreenCenter.y - ScreenSize.y;

	sf::VertexArray ToScreen(sf::Quads, 4);
	ToScreen[0] = sf::Vector2f(startX + ScreenCoordiantes.x                 , startY + ScreenCoordiantes.y                );
	ToScreen[1] = sf::Vector2f(startX + ScreenCoordiantes.x + TextureSize.x , startY + ScreenCoordiantes.y                );
	ToScreen[2] = sf::Vector2f(startX + ScreenCoordiantes.x + TextureSize.x , startY + ScreenCoordiantes.y + TextureSize.y);
	ToScreen[3] = sf::Vector2f(startX + ScreenCoordiantes.x                 , startY + ScreenCoordiantes.y + TextureSize.y);

	// draw the vertex array
	target.draw(ToScreen, states);
}

void ScreenActorC::SetScreenCoordiantes(sf::Vector2u NewCoords)
{
	ScreenCoordiantes = NewCoords;
}

void ScreenActorC::SetScreenCoordiantes(unsigned int x, unsigned int y)
{
	ScreenCoordiantes.x = x;
	ScreenCoordiantes.y = y;
}

