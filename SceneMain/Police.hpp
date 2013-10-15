#ifndef POLICE_H
#define POLICE_H

#include "Npc.hpp"

class Police : public Npc {
	public:
		Police();
		vec2f moveCharacter(float deltaTime);
	private:
		enum State  {
			CHASE = 0,
			PATROL,
			CONFUSION
		};

		State state;
};

#endif // POLICE_H
