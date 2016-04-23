
#pragma once

#include "Universal.h"

enum Turn { T1, T2, TG };
extern Turn PlayerTurn;

class ActorC;

class GameStateC
{
private:

	Turn PlayerTurn;

	ActorC *FocusedActor;

	int PlayerScore1;
	int PlayerScore2;

public:

	GameStateC();
	~GameStateC();

	const Turn GetTurn() const;

	const int GetScore1() const;
	const int GetScore2() const;
	
	void AddScore1(int delta);
	void AddScore2(int delta);

	void NextTurn();

	bool IsFocused() const;
	void SetFocusedActor(ActorC* Focus);
	void ClearFocusedActor();
	ActorC *GetFocusedActor () const;

};