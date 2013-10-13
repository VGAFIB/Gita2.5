#ifndef PERSON_HPP
#define PERSON_HPP
#define PERSON_DISSAPEAR_TIME 10.0f
#define PERSON_CONFUSED_TIME 10.0f
#define PERSON_PANIC_TIME 10.0f
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
		float deathTimer;
		float panicTimer;
		vec2f panicSource;
		float confusedTimer;
		State state;
};

#endif // PERSON_H
