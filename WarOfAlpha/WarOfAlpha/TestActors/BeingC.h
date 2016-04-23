
#include "ActorC.h"

enum State {IDLE, FOCUSED};

class BeingC : public ActorC
{
private:
	
	State state;

public:

	BeingC();

	BeingC(sf::Vector2u Position);

	void SetBeingPosition(int x, int y);

	void MoveBeing(int x, int y);

	void update();

};