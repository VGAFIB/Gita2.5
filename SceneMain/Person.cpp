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
	mark->color = vec4f(0,0,1,1);
	state = STATE_WALKING;
	knowsPlayers = std::vector<bool>(population->getPlayerCount(), false);
	lastSawPlayer = std::vector<vec2f>(population->getPlayerCount());
	anim.setAnimData(Animations.get(s_person_dataFilenames[Utils::randomInt(0, NUANIMS_DATA-1)]));
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
	switch(state) {
		case STATE_WALKING: {
			mark->visible = false;
			vel = 2.0*velMult;
			if(!hasGoal)
				setGoal(vec2f(map->getRandomStreet()));
			for(int i = 0; i < population->getPlayerCount(); i++) {
				if(population->getPlayer(i)->jailed) continue;
				if ((knowsPlayers[i] || population->getPlayer(i)->isDoingAction())
					&& canSee(population->getPlayer(i)->getPosition())) {
					state = STATE_PANIC;
					panicTimer = PERSON_PANIC_TIME;
					panicSource = population->getPlayer(i)->getPosition();
				}
			}
			return dirTowardsGoal();
		}
		case STATE_PANIC: {
			mark->visible = true;
			mark->sign = CharacterMark::EXCLAMATION;
			vel = 3.5*velMult;
			if (panicTimer > 0) panicTimer -= delta;
			else {
				state = STATE_WALKING;
				hasGoal = false;
			}
			for(int i = 0; i < population->getPlayerCount(); i++) {
				if (knowsPlayers[i] && canSee(population->getPlayer(i)->getPosition()))
					panicTimer = PERSON_PANIC_TIME;
			}

			return(vec2f(position - panicSource));
		}
		case STATE_CONFUSED: {
			mark->visible = true;
			mark->sign = CharacterMark::INTERROGATION;
			vel = 1.0*velMult;
			confusedTimer -= delta;
			if (confusedTimer < 0) {
				setGoal(vec2f(map->getRandomStreet())+0.5f);
				state = STATE_WALKING;
			}
			return dirTowardsGoal();
		}
		case STATE_DEAD: {
			mark->visible = false;
			deathTimer -= delta;
			action = "Idle";
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
	deathTimer = PERSON_DISSAPEAR_TIME;
	state = STATE_DEAD;
	drawDead = true;
	Blood* blood = new Blood(position);
	blood->addTo(map);
}

bool Person::knowsPlayer(int i){
	return knowsPlayers[i];
}
