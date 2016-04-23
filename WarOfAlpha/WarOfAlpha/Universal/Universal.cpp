#pragma once

#include <SFML/Graphics.hpp>

namespace Input
{
	//This is for checking if a key is being held down
	bool KeysDown[101];

	//This is for checking if a key was just pressed in this frame, not held
	bool KeysPressed[101];

	//Remembering mouse position
	sf::Vector2i MousePosition;

	//Check to see if a mouse click is being held
	bool LeftClickDown;
	bool RightClickDown;

	//Check to see if a mouse button was just pressed in this frame
	bool LeftClickPressed;
	bool RightClickPressed;
}
