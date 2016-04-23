
#include "MiniMapC.h"

MiniMapC::MiniMapC() : //Initialization list
WorldScroll_thread(&MiniMapC::MiniMapThread, this) ,
WindowActvivate_Thread(&MiniMapC::ActivateThread, this) ,
WindowDeactvivate_Thread(&MiniMapC::DeactivateThread, this)
{
	CreateGraphicComponent();
	GetGraphicComponent()->LoadTexture("Assets/Minimap.png");
	IsViewSet = false;
	IsWindowActive = true;
	//setPosition(1280 - 400 / 2, 720 - 200 / 2);
	WindowActvivate_Thread.launch();
}

void MiniMapC::SetMapView(sf::View *view)
{
	MapView = view;
	IsViewSet = true;
}

void MiniMapC::update()
{

}

void MiniMapC::MiniMapThread()
{
	while (Input::LeftClickDown && IsWindowActive)
	{
		if (Input::MousePosition.x > 880 && Input::MousePosition.x < 1280 && Input::MousePosition.y > 520 && Input::MousePosition.y < 720)
		{
			//take the coordinates and translate it to ZAWORLDO!

			float newX = (Input::MousePosition.x - 880) * 7;
			float newY = (Input::MousePosition.y - 520) * 7;

			if (newX < 640)
				newX = 640;
			else if (newX > 2160)
				newX = 2160;

			if (newY < 360)
				newY = 360;
			else if (newY > 1040)
				newY = 1040;
			
			if (IsViewSet)
			{
				MapView->setCenter(newX, newY);
			}
		}
	}
}

void MiniMapC::ActivateThread()
{
	setPosition(1280 - 400/2, 820);
	while (getPosition().y > 620)
	{
		//std::cout << getPosition().y << std::endl;
		move(0, -60.0f * TimeDelta);
		sf::sleep(sf::milliseconds(1));
	}
	setPosition(1280 - 400/2, 620);
	
	while (true)
	{
		if (Input::KeysPressed[sf::Keyboard::M])
		{
			IsWindowActive = false;
			WindowDeactvivate_Thread.launch();
			return;
		}
	}
}

void MiniMapC::DeactivateThread()
{
	setPosition(1280 - 400/2, 620);
	while (getPosition().y < 820)
	{
		//std::cout << getPosition().y << std::endl;
		move(0, 60.0f * TimeDelta);
		sf::sleep(sf::milliseconds(1));
	}
	setPosition(1280 - 400/2, 820);

	while (true)
	{
		if (Input::KeysPressed[sf::Keyboard::M])
		{
			IsWindowActive = true;
			WindowActvivate_Thread.launch();
			return;
		}
	}
}

void MiniMapC::OnClick()
{
	WorldScroll_thread.launch();
}