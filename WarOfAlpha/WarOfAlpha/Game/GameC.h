
#include <map>
#include <vector>
#include <memory>

#include <SFML\Graphics.hpp>

#include "GameStateC.h"

#include "Actor\Cursor.h"
#include "UIActors\UIActorsInclude.h"

#include "TestActors\P1PieceC.h"
#include "TestActors\P2PieceC.h"
#include "TestActors\EssenceNodeC.h"

#include "MessageHandlerC.h"
#include "ReferenceMasterC.h"

#include "Universal.h"


class ActorC;


extern ReferenceMasterC GameReferenceMaster;
extern MessageHandlerC GameMessageHandler;


class GameC
{
	friend CursorC;

private:

	//Reference to a window
	sf::RenderWindow *GameWindow;

	sf::Vector2i ScreenPos;
	sf::View WorldView;
	sf::View ScreenView;

	//Some important Actors
	//std::unique_ptr<ActorC> Cursor;
	GameStateC GameState;

	//World Actor Map
	std::map <int, ActorC*> WorldActorMap;

	//Screen Actor map;
	std::map <std::string, ActorC*> ScreenActorMap;

	//actors in world
	std::vector <ActorC*> OnScreenWorldActorVector;

	//These systems
	ReferenceMasterC ReferenceMaster;
	MessageHandlerC MessageHandler;

public:

	GameC(sf::RenderWindow *Window);
	~GameC();

	//The functions!

	void GetWorldActorsOnScreen();

	int Run();

	int Input();
	int Update();
	int Draw();

	int TestSetup();
};