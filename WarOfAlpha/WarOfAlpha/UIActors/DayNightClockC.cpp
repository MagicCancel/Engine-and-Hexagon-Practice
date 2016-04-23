#include "DayNightClockC.h"

DayNightClockC::DayNightClockC()
{
	CreateGraphicComponent();
	GetGraphicComponent()->LoadTexture("Assets/Clock_Strip.png", sf::Vector2u(0, 0), sf::Vector2u(100, 100));
}