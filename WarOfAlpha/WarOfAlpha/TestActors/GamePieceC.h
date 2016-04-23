
#pragma once

#include "ActorC.h"

class GamePieceC : public ActorC
{
protected:

	State state;

	//sf::Thread IdleThread;
	//sf::Thread FocusedThread;

public:

	GamePieceC();
	GamePieceC(sf::Vector2u Position);
	~GamePieceC();

	void IdleThreadFunc();
	void FocusedThreadFunc();

	void SetPieceHexPosition(int x, int y);
	void MovePieceHexPosition(int x, int y);

	void update();

	void OnClick();
	void OnFocusClick();

};