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

		bool onLeftCollision(int x, int j);
		bool onRightCollision(int x, int j);
		bool onUpCollision(int x, int j);
		bool onDownCollision(int x, int j);

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
		bool collided;
};

#endif // POLICE_H
