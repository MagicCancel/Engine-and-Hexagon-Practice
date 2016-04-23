
#pragma once

#include <string>
#include <vector>
#include "ActorC.h"

class MultiActorC : public ActorC
{

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	std::map<int, ActorC*> ActMap;

public:

	MultiActorC();

	~MultiActorC();

	void MapActor(int key, ActorC* act);
	
	ActorC* GetActorFromMap(int key);

	//OVERLOAD THIS SHIT
	virtual void update() {};

	bool IsMouseInDimension();

};