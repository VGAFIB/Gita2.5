#ifndef PERSON_HPP
#define PERSON_HPP

#include "Npc.hpp"

class Person : public Npc {
	public:
		Person();
		enum State {
			STATE_WALKING,
			STATE_PANIC,
			STATE_DEAD,
			STATE_CONFUSED
		};
		virtual vec2f moveCharacter(float deltaTime);
		int getState() { return state; }
		void doDeath();
		bool knowsPlayer(int i);
	private:
		std::vector<bool> knowsPlayers;
		std::vector<vec2f> lastSawPlayer;
		float velMult;
		float dissappearTime;
		float deathTimer;
		float panicTime, startPanicTime;
		vec2f panicSource;
		float confuseCooldown;
		float confusedTime;
		State state;
};

#endif // PERSON_H
