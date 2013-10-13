#ifndef POLICE_H
#define POLICE_H

#include "Npc.hpp"

class Police : public Npc {
	public:
		Police();

		vec2f moveCharacter(float delta);

	private:

		vec2f getNewGoal(vec2f position);
		void lookAtRandomPlace();

		enum State  {
			STATE_PATROL_MOVING,
			STATE_PATROL_WATCHING,
			STATE_ALERT,
			STATE_CONFUSE,
			STATE_CHASING_PLAYER,
			STATE_PLAYER_LOST
		};

		State state;
		float watchingTime;
		float watchingTimeFacing;
		float alertTime;
		vec2f lastAlertPos;

		std::vector<float> lastPosSawTime;
		std::vector<vec2f> lastPosSawPlayer;
		std::vector<vec2f> lastDirSawPlayer;
		std::vector<bool> knowPlayer;
		int chasingPlayerNum;
};

#endif // POLICE_H
