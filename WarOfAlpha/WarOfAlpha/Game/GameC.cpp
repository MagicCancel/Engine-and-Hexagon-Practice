
#include "GameC.h"

GameC::GameC(sf::RenderWindow *Window) :
GameWindow(Window),
GameState(),
ReferenceMaster(&this->WorldActorMap),
MessageHandler(&this->WorldActorMap)
{

	ScreenPos  = sf::Vector2i(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	WorldView  = sf::View(sf::Vector2f(640, 360), sf::Vector2f(1280, 720));
	ScreenView = sf::View(sf::Vector2f(ScreenPos.x, ScreenPos.y), sf::Vector2f(1280, 720));

}

GameC::~GameC()
{

	GameWindow = nullptr;

	for (auto itr = WorldActorMap.begin(); itr != WorldActorMap.end(); ++itr)
	{
		delete(itr->second);
	}

	for (auto itr = ScreenActorMap.begin(); itr != ScreenActorMap.end(); ++itr)
	{
		delete(itr->second);
	}

}

void GameC::GetWorldActorsOnScreen()
{
	//What si the screen's min and max?
	sf::Vector2f CameraPos = WorldView.getCenter();
	sf::Vector2f WorldMin(CameraPos.x - SCREEN_WIDTH/2, CameraPos.y - SCREEN_HEIGHT/2);
	sf::Vector2f WorldMax(CameraPos.x + SCREEN_WIDTH/2, CameraPos.y + SCREEN_HEIGHT/2);

	//empty the vector
	OnScreenWorldActorVector.clear();
	
	//put the map on the vector
	OnScreenWorldActorVector.push_back(WorldActorMap[0]);
	//OnScreenWorldActorVector.push_back(WorldActorMap[1]);
	
	//Get the actors on up
	for (auto itr = WorldActorMap.begin(); itr != WorldActorMap.end(); ++itr)
	{
		sf::Vector2f ActPos = itr->second->getPosition();
		if (ActPos.x >= WorldMin.x && ActPos.x <= WorldMax.x &&
			ActPos.y >= WorldMin.y && ActPos.y <= WorldMax.y)
		{
			OnScreenWorldActorVector.push_back(itr->second);
		}
	}
	//std::cout << OnScreenWorldActorVector.size() << std::endl;
}

int GameC::Run()
{

	if (Input::KeysPressed[sf::Keyboard::A] || GameState.GetTurn() == TG)
	{
		GameState.NextTurn();
	}

	MessageHandler.HandleMessages();

	Update();

	GetWorldActorsOnScreen();
	//std::cout << OnScreenWorldActorVector.size() << std::endl;

	Draw();
	
	return 0;
}

int GameC::Input()
{
	return 0;
}

int GameC::Update()
{
	//Handle messages
	//GameMessageHandler.HandleMessages();

	//update world actors
	for (auto itr = WorldActorMap.begin(); itr != WorldActorMap.end(); ++itr)
		itr->second->update();

	//Update the ui
	for (auto itr = ScreenActorMap.begin(); itr != ScreenActorMap.end(); ++itr)
		itr->second->update();

	return 0;
}

int GameC::Draw()
{
	//Draw Section
	GameWindow->clear();

	//draw the game
	GameWindow->setView(WorldView);
	for (auto itr = OnScreenWorldActorVector.begin(); itr != OnScreenWorldActorVector.end(); ++itr)
		GameWindow->draw(**itr);

	//draw the ui
	GameWindow->setView(ScreenView);
	for (auto itr = ScreenActorMap.begin(); itr != ScreenActorMap.end(); ++itr)
		GameWindow->draw(*itr->second);

	//now to handle debug draws?

	for (auto itr = WorldActorMap.begin(); itr != WorldActorMap.end(); ++itr)
		itr->second->DebugDraw();

	for (auto itr = ScreenActorMap.begin(); itr != ScreenActorMap.end(); ++itr)
		itr->second->DebugDraw();

	GameWindow->display();

	return 0;
}

int GameC::TestSetup()
{

	//entry 0 and 1 are reserved for map and cursor

	//The world map!
	WorldActorMap.insert(std::pair<int, ActorC *>(0, new GameBoardC()));
	WorldActorMap[0]->setPosition(1400, 700);
	
	//The cursor!
	WorldActorMap.insert(std::pair<int, ActorC *>(1, new CursorC(&WorldView, this)));
	
	//Some test actors
	WorldActorMap.insert(std::pair<int, ActorC *>(2, new P2PieceC(sf::Vector2i(6, 3))));
	
	WorldActorMap.insert(std::pair<int, ActorC *>(3, new P1PieceC(sf::Vector2i(4, 3))));
	
	WorldActorMap.insert(std::pair<int, ActorC *>(4, new EssenceNodeC(sf::Vector2i(5, 5))));
	
	//Making some ui actors here
	ScreenActorMap.insert(std::pair<std::string, HeroHealthBoxC *>("Hero1", new HeroHealthBoxC()));
	ScreenActorMap["Hero1"]->setPosition(50, 25);

	ScreenActorMap.insert(std::pair<std::string, HeroHealthBoxC *>("Hero2", new HeroHealthBoxC()));
	ScreenActorMap["Hero2"]->setPosition(50, 75);

	ScreenActorMap.insert(std::pair<std::string, HeroHealthBoxC *>("Hero3", new HeroHealthBoxC()));
	ScreenActorMap["Hero3"]->setPosition(50, 125);

	ScreenActorMap.insert(std::pair<std::string, VassalHealthBoxC *>("Vassal1", new VassalHealthBoxC()));
	ScreenActorMap["Vassal1"]->setPosition(50, 175);

	ScreenActorMap.insert(std::pair<std::string, VassalHealthBoxC *>("Vassal2", new VassalHealthBoxC()));
	ScreenActorMap["Vassal2"]->setPosition(50, 225);

	ScreenActorMap.insert(std::pair<std::string, VassalHealthBoxC *>("Vassal3", new VassalHealthBoxC()));
	ScreenActorMap["Vassal3"]->setPosition(50, 275);

	ScreenActorMap.insert(std::pair<std::string, GodHealthBoxC *>("God", new GodHealthBoxC()));
	ScreenActorMap["God"]->setPosition(50, 325);

	ScreenActorMap.insert(std::pair<std::string, DayNightClockC *>("Clock", new DayNightClockC()));
	ScreenActorMap["Clock"]->setPosition(SCREEN_WIDTH / 2 - 50, 50);

	{
		MiniMapC *MiniMap = new MiniMapC();
		MiniMap->SetMapView(&WorldView);
		ScreenActorMap.insert(std::pair<std::string, MiniMapC *>("MiniMap", MiniMap));
	}

	ScreenActorMap.insert(std::pair<std::string, CardHandC *>("CardHand", new CardHandC()));
	ScreenActorMap["CardHand"]->setPosition(875 / 2, SCREEN_HEIGHT - 220 / 2);

	ScreenActorMap.insert(std::pair<std::string, EssenceCounterC *>("EssenceCounter", new EssenceCounterC()));



	for (auto itr = ScreenActorMap.begin(); itr != ScreenActorMap.end(); ++itr)
	{
		itr->second->Attach(&GameState, &ReferenceMaster, &MessageHandler);
	}

	for (auto itr = WorldActorMap.begin(); itr != WorldActorMap.end(); ++itr)
	{
		itr->second->Attach(&GameState, &ReferenceMaster, &MessageHandler);
	}
	
	return 0;
}