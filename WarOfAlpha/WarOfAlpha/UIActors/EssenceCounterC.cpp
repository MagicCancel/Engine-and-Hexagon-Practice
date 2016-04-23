
#include "EssenceCounterC.h"


void EssenceCounterC::DebugDraw()
{
	//boxes
	DrawSquare(sf::Vector2f(420, 20), sf::Vector2f(80, 50), sf::Color(100, 200, 100, 255));

	DrawSquare(sf::Vector2f(680, 20), sf::Vector2f(80, 50), sf::Color(100, 200, 100, 255));

	//player 1

	DrawText(std::to_string(GameState->GetScore1()), 420, 20);

	//player 2
	DrawText(std::to_string(GameState->GetScore2()), 680, 20);

}