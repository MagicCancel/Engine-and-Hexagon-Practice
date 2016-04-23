#pragma once

#include <SFML/Graphics.hpp>

extern unsigned int SCREEN_WIDTH;
extern unsigned int SCREEN_HEIGHT;
extern float TimeDelta;

namespace Input
{
	//This is for checking if a key is being held down
	extern bool KeysDown[101];
	
	//This is for checking if a key was just pressed in this frame, not held
	extern bool KeysPressed[101];
	
	//Remembering mouse position
	extern sf::Vector2i MousePosition;

	//Mouse in HEX CORDS!
	extern sf::Vector2i MouseHexPosition;

	//Check to see if a mouse click is being held
	extern bool LeftClickDown;
	extern bool RightClickDown;

	//Check to see if a mouse button was just pressed in this frame
	extern bool LeftClickPressed;
	extern bool RightClickPressed;
}


namespace HexData
{
	extern const float PI_F;
	extern const float s;
	extern const float h;
	extern const float r;
	extern const float a; //Width of boinding boxed
	extern const float b; //Height of bounding boxed
}

enum State { IDLE, FOCUSED };

extern void DrawSquare(int x, int y, int w, int h, int r, int g, int b, int a);
extern void DrawSquare(sf::Vector2f position, sf::Vector2f size, sf::Color color);
extern void DrawText(std::string str, int x, int y);

//Hex related funcs
int GetHexDist(int q1, int r1, int q2, int r2);
sf::Vector2f ConvertCoordsHexToWorld(int nx, int ny);
sf::Vector2f ConvertCoordsHexToWorld(sf::Vector2i HexCoords);
sf::Vector2i ConvertCoordsWorldToHex(int nx, int ny);

extern void GetHexSpots(int r, std::vector<sf::Vector2i> &HexVec, int xoff, int yoff);

struct ClipS
{
	sf::Texture texture;
	sf::VertexArray quad;

	ClipS() : quad(sf::VertexArray(sf::Quads, 4)) {};

	bool ClipS::loadFile(std::string FileAddress)
	{
		if (!texture.loadFromFile(FileAddress))
		{
			return false;
		}

		const sf::Vector2u size = texture.getSize();

		int xHalf = size.x / 2;
		int yHalf = size.y / 2;

		quad[0].position = sf::Vector2f(-xHalf, -yHalf);
		quad[1].position = sf::Vector2f(xHalf, -yHalf);
		quad[2].position = sf::Vector2f(xHalf, yHalf);
		quad[3].position = sf::Vector2f(-xHalf, yHalf);

		quad[0].texCoords = sf::Vector2f(0, 0);
		quad[1].texCoords = sf::Vector2f(size.x, 0);
		quad[2].texCoords = sf::Vector2f(size.x, size.y);
		quad[3].texCoords = sf::Vector2f(0, size.y);

		return true;
	}

	bool ClipS::loadFile(std::string FileAddress, sf::Vector2u position, sf::Vector2u dimensions)
	{
		if (!texture.loadFromFile(FileAddress))
		{
			return false;
		}

		int xHalf = dimensions.x / 2;
		int yHalf = dimensions.y / 2;

		quad[0].position = sf::Vector2f(-xHalf, -yHalf);
		quad[1].position = sf::Vector2f(xHalf, -yHalf);
		quad[2].position = sf::Vector2f(xHalf, yHalf);
		quad[3].position = sf::Vector2f(-xHalf, yHalf);

		quad[0].texCoords = sf::Vector2f(position.x, position.y);
		quad[1].texCoords = sf::Vector2f(position.x + dimensions.x, position.y);
		quad[2].texCoords = sf::Vector2f(position.x + dimensions.x, position.y + dimensions.y);
		quad[3].texCoords = sf::Vector2f(position.x, position.y + dimensions.y);

		return true;
	}

	void ClipS::setColor(int r, int g, int b, int a)
	{
		quad[0].color.r = r; quad[0].color.g = g; quad[0].color.b = b; quad[0].color.a = a;
		quad[1].color.r = r; quad[1].color.g = g; quad[1].color.b = b; quad[1].color.a = a;
		quad[2].color.r = r; quad[2].color.g = g; quad[2].color.b = b; quad[2].color.a = a;
		quad[3].color.r = r; quad[3].color.g = g; quad[3].color.b = b; quad[3].color.a = a;
	}
};
