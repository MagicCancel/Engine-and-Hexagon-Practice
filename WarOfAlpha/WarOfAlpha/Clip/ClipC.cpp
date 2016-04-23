
#include "ClipC.h"

ClipS::ClipS(std::string FileAddress)
{
	texture.loadFromFile(FileAddress);

	const sf::Vector2u size = texture.getSize();

	quad[0].position = sf::Vector2f(0, 0);
	quad[1].position = sf::Vector2f(size.x, 0);
	quad[2].position = sf::Vector2f(size.x, size.y);
	quad[3].position = sf::Vector2f(0, size.y);

	quad[0].texCoords = sf::Vector2f(0, 0);
	quad[1].texCoords = sf::Vector2f(size.x, 0);
	quad[2].texCoords = sf::Vector2f(size.x, size.y);
	quad[3].texCoords = sf::Vector2f(0, size.y);
}