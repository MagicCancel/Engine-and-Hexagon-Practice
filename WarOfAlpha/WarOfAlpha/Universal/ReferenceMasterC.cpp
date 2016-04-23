
#include "ReferenceMasterC.h"
#include "ActorC.h"

ReferenceMasterC::ReferenceMasterC(std::map <int, ActorC*> *ActorMapPtr)
{
	ActorMap = ActorMapPtr;
}

int ReferenceMasterC::findReference(sf::Vector2i Target) const
{

	for (auto itr = ActorMap->begin()++; itr != ActorMap->end(); ++itr)
	{
		if (itr->second->HasCreatureComponent() == true)
		{
			sf::Vector2i thisOne = itr->second->GetCreatureComponent()->GetHexPosition();
			if (thisOne == Target)
				return itr->first;
		}
	}

	return -1;
}

int ReferenceMasterC::findReference(int x, int y) const
{

	for (auto itr = ActorMap->begin()++; itr != ActorMap->end(); ++itr)
	{
		if (itr->second->HasCreatureComponent() == true)
		{
			sf::Vector2i thisOne = itr->second->GetCreatureComponent()->GetHexPosition();
			if (thisOne.x == x && thisOne.y == y)
				return itr->first;
		}
	}

	return -1;
}

ActorC *ReferenceMasterC::getReference(int Reference) const
{
	if (Reference == -1)
	{
		std::cout << "ERROR: Tried to reference an actor with reference -1";
		return nullptr;
	}
	return ActorMap->at(Reference);
}