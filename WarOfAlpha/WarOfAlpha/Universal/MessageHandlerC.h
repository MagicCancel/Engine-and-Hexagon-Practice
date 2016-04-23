#pragma once

#include <queue>
#include <iostream>
#include <SFML\Graphics.hpp>

#include "Universal.h"

class ActorC;
class P1PieceC;

struct Message
{
	short command;
	sf::Vector2i hexCoords;
	int ref;

	//constructor
	Message(short c, int r, sf::Vector2i h) : command(c), ref(r), hexCoords(h) {}
};

class Spawner
{
public:
	virtual ~Spawner() {}
	virtual ActorC* SpawnActor() = 0;
};
template <class T>
class SpawnerFor : public Spawner
{
public:
	virtual ActorC* SpawnActor() { return new T(); }
};

class MessageHandlerC
{
private:

	std::queue <Message> MessageQueue;

	std::queue <int> FreeMapSlots;
	std::map <int, ActorC*> *ActorMap;

public:

	MessageHandlerC(std::map <int, ActorC*> *ActorMapPtr);

	void HandleMessages();

	void SpawnActor(sf::Vector2i HexCoords);

	void KillActor(int ref);

	void QueueMessage(short command, int ref, sf::Vector2i coords);

};

