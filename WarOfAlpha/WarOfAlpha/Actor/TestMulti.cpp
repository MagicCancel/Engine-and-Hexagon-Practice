
#include "TestMulti.h"

TestMulti::TestMulti()
{

	ActorC *left = new ActorC();
	left->CreateGraphicComponent();
	left->GetGraphicComponent()->LoadTexture("Assets/Clock_Strip.png", sf::Vector2u(0, 0), sf::Vector2u(100, 100));
	left->setPosition(300, 200);

	ActorC *right = new ActorC();
	right->CreateGraphicComponent();
	right->GetGraphicComponent()->LoadTexture("Assets/TwiFlip.png");
	right->setPosition(320, 200);

	MapActor(0, left);
	MapActor(1, right);
}

TestMulti::~TestMulti()
{

}

void TestMulti::update()
{
	if (Input::KeysDown[sf::Keyboard::W])
	{
		ActorC * act = GetActorFromMap(0);
		act->move(0, -1);
	}

	if (Input::KeysDown[sf::Keyboard::S])
	{
		GetActorFromMap(0)->move(0, 1);
	}

	if (Input::KeysDown[sf::Keyboard::A])
	{
		GetActorFromMap(1)->move(-1, 0);
	}

	if (Input::KeysDown[sf::Keyboard::D])
	{
		GetActorFromMap(1)->move(1, 0);
	}

		//ActMap["Rleft"];
}