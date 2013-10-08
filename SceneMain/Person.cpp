#include "Person.hpp"
#include "Population.hpp"
#include "Player.hpp"
#include "Blood.hpp"

#define NUANIMS_DATA 6

const char* s_person_dataFilenames[NUANIMS_DATA] = {
	"calvo",
	"tupe",
	"gordo",
	"rubiaca",
	"morenaca",
	"moderno"
};

Person::Person() {
	dissappearTime = 10.0f;
	walkingTime = 0.0f;

	startPanicTime = 10.0f;
	state = STATE_WALKING;

	knowsPlayers = std::vector<bool>(population->getPlayerCount(), false);
	lastSawPlayer = std::vector<vec2f>(population->getPlayerCount());
	playerActionTime = std::vector<float>(population->getPlayerCount(), 10000);

	confuseCooldown = 0.0f;

	int rand = Utils::randomInt(0, NUANIMS_DATA-1);
	anim.setAnimData(Animations.get(s_person_dataFilenames[rand]));

	velMult = Utils::randomFloat(0.7, 1.5);

	position = vec2f(map->getRandomStreet())+0.5f;
}

static vec2i dirInc[] = {
	vec2i(0,-1),
	vec2i(0, 1),
	vec2i(-1,0),
	vec2i( 1,0)
};

vec2f Person::moveCharacter(float delta) {
	for(int i = 0; i < population->getPlayerCount(); i++)
	{
		if(population->getPlayer(i)->jailed) continue;
		playerActionTime[i] += delta;
		vec2f currPlayerPosition = population->getPlayer(i)->getPosition();
		bool seesPlayerNow = canSee(currPlayerPosition);
		if(seesPlayerNow)
		{
			if(population->getPlayer(i)->isDoingAction())
				playerActionTime[i] = 0;
			lastSawPlayer[i] = currPlayerPosition;
		}
	}

	switch(state)
	{
		case STATE_WALKING:
		{
			mark = MARK_NONE;
			vel = 2.0*velMult;
			if(!hasGoal)
				setGoal(vec2f(map->getRandomStreet()));

			for(int i = 0; i < population->getPlayerCount(); i++)
			{
				if(population->getPlayer(i)->jailed) continue;
				if ((knowsPlayers[i] || population->getPlayer(i)->isDoingAction()) && canSee(population->getPlayer(i)->getPosition()))
				{
					state = STATE_PANIC;
					panicTime = startPanicTime;
					panicSource = population->getPlayer(i)->getPosition();
				}
			}

//			std::vector<Person*> v = population->getSeenCharacters<Person>(this);
//			for(int j = 0; j < (int) v.size(); j++)
//			{
//				state = STATE_PANIC;
//				panicTime = startPanicTime;
//				panicSource = v[j]->getPosition();

//				for(int i = 0; i < population->getPlayerCount(); i++)
//				{
//					if(population->getPlayer(i)->jailed) continue;
//					if (glm::distance(v[j]->position, lastSawPlayer[i]) < 4) knowsPlayers[i] = true;
//				}
//			}

//			if (confuseCooldown <= 0.0f) {
//				for(int i = 0; i < (int) v.size(); i++)
//				{
//					state              = STATE_CONFUSED;
//					confusedTime       = (float) Utils::randomInt(2,4);
//					confusedTimeFacing = (float) Utils::randomInt(1, 3)/4.0;
//					confuseCooldown    = (float) Utils::randomInt(6,12);
//				}
//			}
//			else
//				confuseCooldown -= delta;
			return dirTowardsGoal();
		}
		case STATE_PANIC:
		{
			vel = 3.5*velMult;
			if (panicTime > 0) panicTime -= delta;
			else {
				state = STATE_WALKING;
				hasGoal = false;
			}

			mark = MARK_BLUE_EXCLAMATION;

			for(int i = 0; i < population->getPlayerCount(); i++) {
				if (knowsPlayers[i] && canSee(population->getPlayer(i)->getPosition()))
					panicTime = startPanicTime;
			}

			return(vec2f(position - panicSource));
		}
		case STATE_CONFUSED: {
			mark = MARK_BLUE_QUESTION;
			vel = 1.0*velMult;

			confusedTime -= delta;
			confusedTimeFacing -= delta;

			if (confusedTime < 0) {
				setGoal(vec2f(map->getRandomStreet())+0.5f);
				state = STATE_WALKING;
			}


			std::vector<Person*> v = population->getSeenCharacters<Person>(this);
			for(int j = 0; j < (int)v.size(); j++) {
				state = STATE_PANIC;
				panicTime = startPanicTime;
				panicSource = v[j]->getPosition();
				for(int i = 0; i < population->getPlayerCount(); i++)
					if (glm::distance(v[j]->position, lastSawPlayer[i]) < 3) knowsPlayers[i] = true;
			}


			for(int i = 0; i < population->getPlayerCount(); i++)
			{
				if(population->getPlayer(i)->jailed) continue;
				if ((knowsPlayers[i] || population->getPlayer(i)->isDoingAction()) && canSee(population->getPlayer(i)->getPosition()))
				{
					state = STATE_PANIC;
					panicTime = startPanicTime;
					panicSource = population->getPlayer(i)->getPosition();
				}
			}

			if (confusedTimeFacing < 0) {
				//FIXME
				confusedTimeFacing = Utils::randomInt(1, 3)/4.0f;
				return vec2f(Utils::randomFloat(-1, 1), Utils::randomFloat(-1, 1));
			}
			else
				return dirTowardsGoal();
		}
		case STATE_DEAD: {
			mark = MARK_NONE;
			deathTimer -= delta;
			if (deathTimer < 0)
				removeAndDelete();

			return vec2f(0, 0);
		}
		default:
			return vec2f(0, 0);
	}

	VBE_ASSERT(false, "wtf");
	return vec2f(0, 0);
}

void Person::doDeath() {
	deathTimer = dissappearTime;
	state = STATE_DEAD;
	drawDead = true;
	Blood* blood = new Blood(position);
	blood->addTo(map);
}

bool Person::knowsPlayer(int i){
	return knowsPlayers[i];
}
