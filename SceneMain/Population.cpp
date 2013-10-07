#include "Population.hpp"
#include "Character.hpp"
#include "Player.hpp"
#include "Map.hpp"

Population::Population() {
	map = static_cast<Map*>(getGame()->getObjectByName("map"));
	population = std::vector<std::vector<std::vector<Character*> > >
			(map->getWidth(),std::vector<std::vector<Character*> >
			 (map->getHeight(),std::vector<Character*>()));
	this->setName("population");
}

Population::~Population() {
}


void collide(Character* a, Character* b)
{
	vec2f pa = a->getPosition();
	vec2f pb = b->getPosition();

	vec2f dir = pb-pa;

	float dist = 0.25;
	float len = glm::length(dir);
	if(len < dist && len > 0.01)
	{
		dir *= 1/len;
		dir *= dist*0.5;
		vec2f mean = (pa+pb)*0.5f;
		a->move(mean-dir);
		b->move(mean+dir);
	}
}


void doCollisions2(std::vector<Character*>& a, std::vector<Character*>& b)
{
	for(unsigned int i = 0; i < a.size(); i++)
		for(unsigned int j = 0; j < b.size(); j++)
			collide(a[i], b[j]);
}

void doCollisions1(std::vector<Character*>& a)
{
	for(unsigned int i = 0; i < a.size(); i++)
		for(unsigned int j = i+1; j < a.size(); j++)
			collide(a[i], a[j]);
}


void Population::update(float deltaTime) {
	(void) deltaTime;
	for(unsigned int x = 0; x < population.size(); ++x) {
		for(unsigned int y = 0; y < population[0].size(); ++y) {
			population[x][y].clear();
		}
	}

	const std::list<GameObject*>& children = getChildren();

	for(std::list<GameObject*>::const_iterator it = children.begin(); it != children.end(); ++it) {
		Character* c = static_cast<Character*>(*it);
		population[floor(c->getPosition().x)][floor(c->getPosition().y)].push_back(c);
	}

	//COLLISIONS PLOX

	int tx = map->getWidth();
	int ty = map->getHeight();

	int add[4][2] = {
		{1, 0}, {0, -1}, {0, 1}, {1, 1}
	};

	for(int y = 0; y < ty; y++)
		for(int x = 0; x < tx; x++)
		{
			doCollisions1 (population[x][y]);

			for(int j = 0; j < 4; j++)
			{
				int x2 = x+add[j][0];
				int y2 = y+add[j][1];

				if(x2 < 0 || x2 >= tx) continue;
				if(y2 < 0 || y2 >= ty) continue;

				doCollisions2 (population[x][y], population[x2][y2]);
			}
		}
}

void Population::onObjectAdd(GameObject* object) {
	Character* c = dynamic_cast<Character*>(object);
	VBE_ASSERT(c != NULL, "Population nodes should not have non-Character children");
}

int Population::getPlayerCount() {
	return 1;
}

Player* Population::getPlayer(int i) {
	(void) i;
	return getFirstObjectOfType<Player>();
}
