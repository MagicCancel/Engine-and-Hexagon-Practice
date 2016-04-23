
#include <iostream>
#include "GameStateC.h"

GameStateC::GameStateC()
{
	PlayerTurn = T1;

	FocusedActor = nullptr;

	PlayerScore1 = 0;
	PlayerScore2 = 0;
}

GameStateC::~GameStateC()
{

}

const Turn GameStateC::GetTurn() const
{
	return PlayerTurn;
}

const int GameStateC::GetScore1() const
{
	return PlayerScore1;
}
const int GameStateC::GetScore2() const
{
	return PlayerScore2;
}

void GameStateC::AddScore1(int delta)
{
	PlayerScore1 += delta;
}
void GameStateC::AddScore2(int delta)
{
	PlayerScore2 += delta;
}

void GameStateC::NextTurn()
{
	if (PlayerTurn == T1)
	{
		PlayerTurn = T2;
		std::cout << "Turn is now Player 2\n";
	}
	else if (PlayerTurn == T2)
	{
		PlayerTurn = TG;
		std::cout << "Turn is now Game\n";
	}
	else if (PlayerTurn == TG)
	{
		PlayerTurn = T1;
		std::cout << "Turn is now Player 1\n";
	}
}

bool GameStateC::IsFocused() const
{
	if (FocusedActor == nullptr)
		return false;
	else
		return true;
}

void GameStateC::SetFocusedActor(ActorC* Focus)
{
	FocusedActor = Focus;
}

void GameStateC::ClearFocusedActor()
{
	FocusedActor = nullptr;
}

ActorC* GameStateC::GetFocusedActor() const
{
	return FocusedActor;
}