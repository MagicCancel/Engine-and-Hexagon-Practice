#pragma once

#include <iostream>
#include "Universal.h"

class ActorC;

class ReferenceMasterC
{
private:

	std::map <int, ActorC*> *ActorMap;

public:

	ReferenceMasterC(std::map <int, ActorC*> *ActorMapPtr);

	int findReference(sf::Vector2i Target) const;
	
	int findReference(int x, int y) const;

	ActorC *getReference(int Reference) const;

};