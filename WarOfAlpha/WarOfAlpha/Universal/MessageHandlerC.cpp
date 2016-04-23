
#include "MessageHandlerC.h"

#include "ActorC.h"
#include "TestActors\P1PieceC.h"

MessageHandlerC::MessageHandlerC(std::map <int, ActorC*> *ActorMapPtr)
{
	ActorMap = ActorMapPtr;
}

void MessageHandlerC::HandleMessages()
{
	while(MessageQueue.empty() != true)
	{

		//0: Kill
		//1: Spawn
		//2: Focus


		Message message = MessageQueue.front();
		//the kill command
		if (message.command == 0)
		{
			KillActor(message.ref);
		}
		//An impromptu spawn command I guess
		else if (message.command == 1)
		{
			SpawnActor(message.hexCoords);
		}

		//now get rid of the message
		MessageQueue.pop();
	}
}

void MessageHandlerC::SpawnActor(sf::Vector2i HexCoords)
{

	int ref = -1;

	if ( ! FreeMapSlots.empty()) //there is an empty spot in the map
	{
		ref = FreeMapSlots.front();
		FreeMapSlots.pop();
	}
	else //Just add to the top
	{
		ref = ActorMap->size();
	}

	Spawner* ActorSpawner = new SpawnerFor<P1PieceC>();
	ActorMap->insert( std::pair<int, ActorC*>(ref, ActorSpawner->SpawnActor()) );
	ActorMap->at(ref)->GetCreatureComponent()->SetHexPosition(sf::Vector2i(HexCoords.x, HexCoords.y));
	
	sf::Vector2f NewPos = ConvertCoordsHexToWorld(HexCoords.x, HexCoords.y);
	ActorMap->at(ref)->setPosition(NewPos);

}

void MessageHandlerC::KillActor(int ref)
{
	delete(ActorMap->at(ref));
	ActorMap->erase(ref);
	FreeMapSlots.push(ref);
}

void MessageHandlerC::QueueMessage(short command, int ref, sf::Vector2i coords)
{
	MessageQueue.push(Message(command, ref, coords));
}