#pragma once

#include <iostream>
#include "ActorC.h"


class MiniMapC : public ActorC
{

private:

	sf::View *MapView;
	sf::Thread WorldScroll_thread;
	sf::Thread WindowActvivate_Thread;
	sf::Thread WindowDeactvivate_Thread;

	bool IsViewSet;
	bool IsWindowActive;

public:

	MiniMapC();

	void update();
	
	void SetMapView(sf::View *view);
	void MiniMapThread();
	void ActivateThread();
	void DeactivateThread();

	void OnClick();
};