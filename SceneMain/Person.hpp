#ifndef PERSON_HPP
#define PERSON_HPP

#include "Npc.hpp"

class Person : public Npc {
	public:
	Person();

	virtual vec2f moveCharacter(float deltaTime);

	void doDeath();
	void onHit();
	bool is_alive();

	enum State {
		STATE_WALKING,
		STATE_PANIC,
		STATE_DEAD,
		STATE_CONFUSED
	};

	int getState() { return state; }
	bool knowsPlayer(int i);

	private:
	float getClosestMenace(vec2f position, vec2f& menacePos);
	void lookAtRandomPlace();

	float ix, iy;
	std::vector<bool> knowsPlayers;
	std::vector<vec2f> lastSawPlayer;
	std::vector<float> playerActionTime;

	float velMult;

	float dissappearTime;
	float deathTimer;
	float panicTime, startPanicTime;
	vec2f panicSource;
	float walkingTime;
	float confuseCooldown;
	float confusedTime;
	float confusedTimeFacing;

	State state;

	//sf::SoundBuffer dieSoundBuff;
	//sf::Sound dieSound;
};

#endif // PERSON_H
