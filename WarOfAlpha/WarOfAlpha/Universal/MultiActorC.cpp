
#include "MultiActorC.h"
#include <iostream>

MultiActorC::MultiActorC()
{


}

MultiActorC::~MultiActorC()
{
	for (auto itr = ActMap.begin(); itr != ActMap.end(); ++itr)
		delete(itr->second);
}

void MultiActorC::MapActor(int key, ActorC* act)
{
	ActMap.insert(std::pair<int, ActorC*>(key, act));
}

ActorC* MultiActorC::GetActorFromMap(int key)
{
	return ActMap[key];
}

void MultiActorC::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	for (auto itr = ActMap.begin(); itr != ActMap.end(); ++itr)
	{
		itr->second->draw(target, states);
	}
}

bool MultiActorC::IsMouseInDimension()
{
	//We're starting from the end of the map and working backwards.
	//Actors that are at the end of the map are given priority
	auto itr = ActMap.end(); --itr;
	
	//Check the map for hits
	while (true)
	{
		//Is there a hit
		if (itr->second->IsMouseInDimension(getPosition()) == true)
		{
			return true;
		}

		//Doing a strange thing here where we see if we're at the beginning before lowering the itr
		//This is supposed to allow us to check all the way to the beginning of the map and not skip the beginning
		if (itr == ActMap.begin())
			break;
		
		//Decreament the itr
		--itr;
	}

	//If not hits, return false
	return false;
}

