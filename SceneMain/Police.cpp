#include "Police.hpp"
#include "SceneMain.hpp"
#include "Person.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Population.hpp"

Police::Police() : Npc()
{
	mark->color = vec4f(1,0,0,1);
	mark->visible = false;
	vel = 2.0f;

	int playerCount = population->getPlayerCount();

	lastPosSawTime = std::vector<float> (playerCount);
	lastPosSawPlayer = std::vector<vec2f> (playerCount);
	lastDirSawPlayer = std::vector<vec2f> (playerCount);
	knowPlayer = std::vector<bool> (playerCount, false);

	state = STATE_PATROL_WATCHING;

	anim.setAnimData(Animations.get("poli"));

	texName = "police";

	watchingTime = 0;
	watchingTimeFacing = 0;

	position = vec2f(map->getRandomStreet())+0.5f;
}

vec2f Police::moveCharacter(float delta)
{
	collided = false;

	//TODO Multiplayer logic
	//	Player* p = population->getPlayer(0];

	std::vector<Character*> personList = population->getSeenCharacters<Character>(this);

	for (std::vector<Character*>::iterator it = personList.begin(); it != personList.end(); it++)
	{
		Person* p = dynamic_cast<Person*>(*it);
		Police* p2;

		if(p)
		{
			Person &person = *p;

			switch(person.getState())
			{
				case Person::STATE_PANIC:
				{
					if(state == STATE_PATROL_MOVING ||
							state == STATE_PATROL_WATCHING) {
						if (person.knowsPlayer(0))
						{
							state = STATE_ALERT;
							alertTime = 20;
							lastAlertPos = person.getPosition();
							setGoal(lastAlertPos);
						}
						else
						{
							state = STATE_CONFUSE;
							alertTime = 15;
							lastAlertPos = person.getPosition();
							setGoal(lastAlertPos);
						}
					}
					break;
				}
				case Person::STATE_DEAD:
				{
					for(int i = 0; i < population->getPlayerCount(); i++)
					{
						Player* player = population->getPlayer(i);
						if(player->jailed) continue;
						if(canSee(player->getPosition()) && glm::distance(person.getPosition(), player->getPosition()))
							knowPlayer[i] = true;

						if (knowPlayer[i])
						{
							if(state == STATE_PATROL_MOVING ||
									state == STATE_PATROL_WATCHING ||
									state == STATE_CONFUSE) {
								state = STATE_ALERT;
								alertTime = 20;
								lastAlertPos = person.getPosition();
								setGoal(lastAlertPos);
								chasingPlayerNum = i;
							}
						}
					}

					if(state == STATE_PATROL_MOVING ||
							state == STATE_PATROL_WATCHING ||
							state == STATE_CONFUSE) {
						state = STATE_CONFUSE;
						alertTime = 20;
						lastAlertPos = person.getPosition();
						setGoal(lastAlertPos);
					}

					break;
				}
			}
		}
		else if(p2 = dynamic_cast<Police*>(*it))
		{

			Police &police = *p2;

			switch(police.state)
			{
				case Police::STATE_ALERT:
					if(state == STATE_PATROL_MOVING ||
							state == STATE_PATROL_WATCHING ||
							state == STATE_CONFUSE) {
						state = STATE_ALERT;
						alertTime = police.alertTime;
						lastAlertPos = police.lastAlertPos;
						chasingPlayerNum = police.chasingPlayerNum;
						setGoal(lastAlertPos);
					}
					break;
				case Police::STATE_CONFUSE:
					if(state == STATE_PATROL_MOVING ||
							state == STATE_PATROL_WATCHING) {
						state = STATE_CONFUSE;
						alertTime = police.alertTime;
						lastAlertPos = police.lastAlertPos;
						chasingPlayerNum = police.chasingPlayerNum;
						setGoal(lastAlertPos);
					}
					break;
				case Police::STATE_CHASING_PLAYER:
				case Police::STATE_PLAYER_LOST:
					if(state == STATE_PATROL_MOVING ||
							state == STATE_PATROL_WATCHING ||
							state == STATE_CONFUSE) {
						state = STATE_ALERT;
						alertTime = 30;
						chasingPlayerNum = police.chasingPlayerNum;
						lastAlertPos = lastPosSawPlayer[chasingPlayerNum];
						setGoal(lastAlertPos);
					}
					break;
			}
		}
	}

	if(state != STATE_CHASING_PLAYER)
		for(int i = 0; i < population->getPlayerCount(); i++)
		{
			Player* player = population->getPlayer(i);

			if(player->jailed) continue;

			if(canSee(player->getPosition())) {
				knowPlayer[i] = knowPlayer[i] || player->isDoingAction();
				if (knowPlayer[i]) {
					lastPosSawPlayer[i] = player->getPosition();
					lastDirSawPlayer[i] = lastPosSawPlayer[i] - position;
					lastPosSawTime[i] = 5;
					chasingPlayerNum = i;
					state = STATE_CHASING_PLAYER;
				}
			}
		}

	switch(state)
	{
		case STATE_PATROL_MOVING:
		{
			mark->visible = false;
			vel = 1.5f;
			if (!hasGoal) {
				state = STATE_PATROL_WATCHING;
				watchingTime = Utils::randomInt(2, 6);
				lookAtRandomPlace();
				watchingTimeFacing = Utils::randomInt(1, 2);
				setGoal(getNewGoal(position));
			}

			return dirTowardsGoal();
		}
		case STATE_PATROL_WATCHING:
		{
			mark->visible = false;
			vel = 1.5f;
			watchingTime -= delta;
			watchingTimeFacing -= delta;

			if (watchingTime < 0) {
				setGoal(getNewGoal(position));
				state = STATE_PATROL_MOVING;
			}

			if (watchingTimeFacing < 0) {
				lookAtRandomPlace();
				watchingTimeFacing = Utils::randomInt(1, 2);
			}

			return vec2f(0, 0);
		}
		case STATE_ALERT:
		{
			vel = 4.5f;
			mark->visible = true;
			mark->sign = CharacterMark::INTERROGATION;
			alertTime -= delta;

			if (!hasGoal)
				setGoal(getNewGoal(lastAlertPos));

			if (alertTime < 0)
				state = STATE_PATROL_MOVING;

			return dirTowardsGoal();
		}
		case STATE_CONFUSE:
		{
			vel = 2.0f;
			mark->visible = true;
			mark->sign = CharacterMark::INTERROGATION;
			alertTime -= delta;

			if (!hasGoal)
				setGoal(getNewGoal(lastAlertPos));

			if (alertTime < 0)
				state = STATE_PATROL_MOVING;

			return dirTowardsGoal();
		}
		case STATE_CHASING_PLAYER:
		{
			vel = 4.0f;
			mark->visible = true;
			mark->sign = CharacterMark::EXCLAMATION;

			lastPosSawTime[chasingPlayerNum] -= delta;

			Player* p = population->getPlayer(chasingPlayerNum);
			if(canSee(p->getPosition()))
			{
				lastDirSawPlayer[chasingPlayerNum] = p->getPosition()-lastPosSawPlayer[chasingPlayerNum];
				lastPosSawPlayer[chasingPlayerNum] = p->getPosition();
				lastPosSawTime[chasingPlayerNum] = 5;
			}

			if (glm::distance(position, lastPosSawPlayer[chasingPlayerNum]) <= 1)
				state = STATE_PLAYER_LOST;

			if (lastPosSawTime[chasingPlayerNum] < 0)
			{
				state = STATE_ALERT;
				alertTime = 20;
				lastAlertPos = lastPosSawPlayer[chasingPlayerNum];
			}

			if (glm::distance(position, p->getPosition()) <= 1)
			{
				state = STATE_PATROL_MOVING;
				p->gotCaught();
			}

			return lastPosSawPlayer[chasingPlayerNum]-position;
		}
		case STATE_PLAYER_LOST:
		{
			vel = 2.75f;
			mark->visible = true;
			mark->sign = CharacterMark::INTERROGATION;
			lastPosSawTime[chasingPlayerNum] -= delta;

			Player* p = population->getPlayer(chasingPlayerNum);
			if(canSee(p->getPosition()))
			{
				lastDirSawPlayer[chasingPlayerNum] = p->getPosition()-lastPosSawPlayer[chasingPlayerNum];
				lastPosSawPlayer[chasingPlayerNum] = p->getPosition();
				lastPosSawTime[chasingPlayerNum] = 5;
				state = STATE_CHASING_PLAYER;
			}
			else
			{
				if (collided) {
					lastDirSawPlayer[chasingPlayerNum].x *= -1;
					lastDirSawPlayer[chasingPlayerNum].y *= -1;
				}

				if (lastPosSawTime[chasingPlayerNum] < 0 || collided)
				{
					state = STATE_ALERT;
					alertTime = 20;
					lastAlertPos = lastPosSawPlayer[chasingPlayerNum];
				}
			}
			return lastDirSawPlayer[chasingPlayerNum];
		}
	}

	VBE_ASSERT(false, "wtf");
	return vec2f(0, 0);
}

static vec2i dirInc[] = {
	vec2i(0,-1),
	vec2i(0, 1),
	vec2i(-1,0),
	vec2i( 1,0)
};

vec2f Police::getNewGoal(vec2f pos)
{
	int distGoal = 10;
	std::vector<vec2i> goals;

	vec2i from = vec2i(pos);

	std::vector<std::vector<int> > vis(map->getWidth(), std::vector<int>(map->getHeight(), -1));

	std::queue<vec2i> q;
	q.push(from);
	vis[from.x][from.y] = 0;
	while(!q.empty())
	{
		vec2i v = q.front();
		int dist = vis[v.x][v.y];
		q.pop();

		if (dist > distGoal) continue;
		else goals.push_back(v);

		for(int i = 0; i < 4; i++)
		{
			vec2i v2 = v + dirInc[i];
			if(v2.x < 0 || v2.x >= map->getWidth()) continue;
			if(v2.y < 0 || v2.y >= map->getHeight()) continue;
			if(map->tile(v2.x, v2.y).isSolid()) continue;
			if(vis[v2.x][v2.y] != -1) continue;
			vis[v2.x][v2.y] = dist+1;
			q.push(v2);
		}
	}

	vec2i goal = goals[Utils::randomInt(0, goals.size()-2)];
	return vec2f(goal.x + Utils::randomFloat(0.3, 0.7), goal.y + Utils::randomFloat(0.3, 0.7));

}

void Police::lookAtRandomPlace()
{
	vec2i v = vec2i(position);

	int i = 0;
	while(i < 4) {
		faceDir = (FaceDir)Utils::randomInt(FACE_UP, FACE_RIGHT);
		vec2i v2 = v + dirInc[faceDir];
		if(map->validTile(v2) && !map->tile(v2).isSolid()) break;
		i++;
	}
}


bool Police::onLeftCollision(int x, int j)
{
	(void)x; (void)j;
	collided = true;
	return state != STATE_CHASING_PLAYER;
}

bool Police::onRightCollision(int x, int j)
{
	(void)x; (void)j;
	collided = true;
	return state != STATE_CHASING_PLAYER;
}

bool Police::onUpCollision(int x, int j)
{
	(void)x; (void)j;
	collided = true;
	return state != STATE_CHASING_PLAYER;
}

bool Police::onDownCollision(int x, int j)
{
	(void)x; (void)j;
	collided = true;
	return state != STATE_CHASING_PLAYER;
}
