
#include <iostream>
#include <map>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Universal/Universal.h"
#include "Game/GameC.h"

unsigned int SCREEN_WIDTH = 1280;
unsigned int SCREEN_HEIGHT = 720;

sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "War of Dieties: Alpha", sf::Style::Titlebar | sf::Style::Close);
sf::Vector2i ScreenPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
sf::View WorldView(sf::Vector2f(640, 360), sf::Vector2f(1280, 720));
sf::View ScreenView(sf::Vector2f(ScreenPos.x, ScreenPos.y), sf::Vector2f(1280, 720));

sf::Font GameFont;

enum GameTurn { P1Turn = 0, P2Turn, BoardTurn };

//Define those externs from the input.h file
float TimeDelta;
bool Input::KeysDown[101];
bool Input::KeysPressed[101];
sf::Vector2i Input::MousePosition;
sf::Vector2i Input::MouseHexPosition;
bool Input::LeftClickDown;
bool Input::RightClickDown;
bool Input::LeftClickPressed;
bool Input::RightClickPressed;

//Define the hex data
const float HexData::PI_F = 3.14159265358979f;
const float HexData::s = 34.0f;
const float HexData::h = HexData::s * sin(30.0f * HexData::PI_F / 180);
const float HexData::r = HexData::s * cos(30.0f * HexData::PI_F / 180);
const float HexData::a = 2 * HexData::r; //Width of boinding boxed
const float HexData::b = HexData::s + 2 * HexData::h; //Height of bounding boxed

//Pre:: x anf y are coordinates, w and h are diemsnions, rgba are color
void DrawSquare(int x, int y, int w, int h, int r, int g, int b, int a)
{
	// define a square
	sf::RectangleShape rectangle(sf::Vector2f(w, h));
	rectangle.setPosition(sf::Vector2f(x, y));
	rectangle.setFillColor(sf::Color(r, g, b, a));

	//draw it
	window.setView(ScreenView);
	window.draw(rectangle);
}
//Pre:: position is a sf::Vector2f cooridnate, size is a sf::Vector2f dimension, color is a af::Color
void DrawSquare(sf::Vector2f position, sf::Vector2f size, sf::Color color)
{
	// define a square
	sf::RectangleShape rectangle(size);
	rectangle.setPosition(position);
	rectangle.setFillColor(color);

	//draw it
	window.setView(ScreenView);
	window.draw(rectangle);
}

void DrawText(std::string str, int x, int y)
{
	sf::Text text;
	text.setFont(GameFont);
	text.setString(str);
	text.setCharacterSize(12);
	text.setColor(sf::Color::Red);
	text.setPosition(x, y);
	window.setView(ScreenView);
	window.draw(text);
}

//Pre: q1, r1, q2, and r2 are all ints
int GetHexDist(int HexCoordx1, int HexCoordy1, int HexCoordx2, int HexCoordy2)
{
	//convert them to cube
	int x1 = HexCoordx1 - (HexCoordy1 - (HexCoordy1 & 1)) / 2;
	int	z1 = HexCoordy1;
	int	y1 = -x1 - z1;

	int x2 = HexCoordx2 - (HexCoordy2 - (HexCoordy2 & 1)) / 2;
	int	z2 = HexCoordy2;
	int	y2 = -x2 - z2;

	return (abs(x1 - x2) + abs(y1 - y2) + abs(z1 - z2)) / 2;
}

//Pre: HexCoords is a hex coordinate
sf::Vector2f ConvertCoordsHexToWorld(sf::Vector2i HexCoords)
{
	int cx = (HexCoords.x)* HexData::a;
	int cy = (HexCoords.y)* (HexData::s + HexData::h);

	if (HexCoords.y % 2 == 1 || HexCoords.y % 2 == -1)
		cx += HexData::r;

	return sf::Vector2f(cx + 30, cy + 34);
}
sf::Vector2f ConvertCoordsHexToWorld(int nx, int ny)
{
	int cx = (nx)* HexData::a;
	int cy = (ny)* (HexData::s + HexData::h);

	if (ny % 2 == 1 || ny % 2 == -1)
		cx += HexData::r;

	return sf::Vector2f(cx + 30, cy + 34);
}

//Pre: World coordinates
sf::Vector2i ConvertCoordsWorldToHex(int nx, int ny)
{

	//What section are we on?
	sf::Vector2i Section(nx / (2 * HexData::r) + 1, ny / (HexData::h + HexData::s) + 1);

	int sectPosX = fmodf(nx, (2 * HexData::r));
	int sectPosY = fmodf(ny, (HexData::h + HexData::s));

	//std::cout << "(" << Section.x << ", " << Section.y << ")  :  ";
	//std::cout << "(" << sectPosX << ", " << sectPosY << ")\n";

	int arrayX = Section.x;
	int arrayY = Section.y;

	if (Section.y % 2 == 1) //If it's odd (type a)
	{
		// left Edge
		if (sectPosY < (HexData::h - sectPosX * HexData::h / HexData::r))
		{
			arrayY = Section.y - 1;
			arrayX = Section.x - 1;
			//std::cout << " AL ";
		}

		// right Edge
		if (sectPosY < (-HexData::h + sectPosX * HexData::h / HexData::r))
		{
			arrayY = Section.y - 1;
			//std::cout << " AR ";
		}
	}
	else //else it's even (type b)
	{
		// right side
		if (sectPosX >= HexData::r)
		if (sectPosY < (2 * HexData::h - sectPosX * HexData::h / HexData::r))
		{
			arrayY = Section.y - 1;
			//std::cout << " BR ";
		}
		// left side
		if (sectPosX < HexData::r)
		{
			if (sectPosY < (sectPosX * HexData::h / HexData::r))
			{
				arrayY = Section.y - 1;
				//std::cout << " BL1 ";
			}
			else
			{
				arrayX = Section.x - 1;
				//std::cout << " BL2 ";
			}
		}
	}
	
	//std::cout << "(" << sectPosX << ", " << sectPosY << ") " << arrayX << " , " << arrayY << std::endl;
	//std::cout << arrayX - 1 << " , " << arrayY - 1 << "\n";

	return sf::Vector2i(arrayX - 1, arrayY - 1);

}

//Pre: r is a radius, and HexVec is a vector of Vector2i. xoff and yoff can repreasent the center coordinates
void GetHexSpots(int r, std::vector<sf::Vector2i> &HexVec, int xoff = 0, int yoff = 0)
{
	HexVec.clear();

	int n = r;
	for (int dx = -n; dx <= n; dx++)
	{
		//Get Y
		int dy = fmax(-n, -dx - n);
		int end = fmin(n, -dx + n);

		for (; dy <= end; dy++)
		{
			//Get Z
			int dz = -dx - dy;

			//Take the square coordinates and convert them to hex
			int q = dx + (dz - (dz & 1)) / 2;
			int r = dz;

			HexVec.push_back(sf::Vector2i(xoff + q, yoff + r));
		}
	}

}

// For capturing input and changing the input data
void TakeInput(sf::Event *event)
{ 
	//Check for button presses
	if (event->type == sf::Event::KeyPressed)
	{
		if (event->key.code == sf::Keyboard::Unknown)
			return;

		Input::KeysDown[event->key.code] = true;
		Input::KeysPressed[event->key.code] = true;
		//std::cout << "Key pressed: " << event->key.code << std::endl;
	}

	//Check for key releases
	if (event->type == sf::Event::KeyReleased)
	{
		if (event->key.code == sf::Keyboard::Unknown)
			return;

		Input::KeysDown[event->key.code] = false;
		//std::cout << "Key released: " << event->key.code << std::endl;
	}

	//Check to see if a mouse was moved
	if (event->type == sf::Event::MouseMoved)
	{
		//actor.setPosition(event.mouseMove.x, event.mouseMove.y);
		Input::MousePosition.x = event->mouseMove.x;
		Input::MousePosition.y = event->mouseMove.y;
	}

	//Mouse
	if (event->type == sf::Event::MouseButtonPressed)
	{
		if (event->mouseButton.button == sf::Mouse::Left)
		{
			Input::LeftClickDown = true;
			Input::LeftClickPressed = true;
		}
		if (event->mouseButton.button == sf::Mouse::Right)
		{
			Input::RightClickDown = true;
			Input::RightClickPressed = true;
		}
	}

	if (event->type == sf::Event::MouseButtonReleased)
	{
		if (event->mouseButton.button == sf::Mouse::Left)
			Input::LeftClickDown = false;

		if (event->mouseButton.button == sf::Mouse::Right)
			Input::RightClickDown = false;
	}
}

//Nullifying key presses
void NullifyPresses()
{
	//Nullify the KeysPressed array
	for (int i = 0; i < 101; i++)
	{
		Input::KeysPressed[i] = false;
	}
	//Nullify the mouse presses
	Input::LeftClickPressed = false;
	Input::RightClickPressed = false;
}

int main()
{

	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	sf::Clock clock;

	if (!GameFont.loadFromFile("Anonymous_Pro.ttf"))
	{
		std::cout << "ERROR: Font failed to load!\n";
		return -1;
	}

	GameC Game(&window);
	Game.TestSetup();

	//set us up the keys
	for (int i = 0; i < 101; i++)
	{
		Input::KeysDown[i] = false;
		Input::KeysPressed[i] = false;
	}

	//The game loop
	while (window.isOpen())
	{
		//Update the timer
		TimeDelta = clock.restart().asSeconds();

		//Handle Input
		sf::Event event;
		while (window.pollEvent(event))
		{
			//Quit
			if (event.type == sf::Event::Closed)
				break;

			TakeInput(&event);
		}

		Game.Run();

		NullifyPresses();

	}

	return 0;
}


//Quick screen code
/*
if (Input::KeysDown[sf::Keyboard::A])
{
int speed = 100;

if (Input::KeysDown[sf::Keyboard::S])
speed *= 3;

if (Input::MousePosition.x > 100 + ScreenPos.x)
view.move(speed * TimeDelta, 0);

if (Input::MousePosition.x < -100 + ScreenPos.x)
view.move(-speed * TimeDelta, 0);

if (Input::MousePosition.y > 100 + ScreenPos.y)
view.move(0, speed * TimeDelta);

if (Input::MousePosition.y < -100 + ScreenPos.y)
view.move(0, -speed * TimeDelta);

sf::Vector2f center = view.getCenter();

std::cout << center.x << " , " << center.y << std::endl;
window.setView(view);
}*/