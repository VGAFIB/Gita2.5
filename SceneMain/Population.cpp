#include "Population.hpp"
#include "Character.hpp"
#include "Player.hpp"
#include "Map.hpp"

Population::Population() {
	Map* map = static_cast<Map*>(GameObject::getObjectByName("map"));
	population = std::vector<std::vector<std::list<Character*> > >
			(map->getWidth(),std::vector<std::list<Character*> >
			 (map->getHeight(),std::list<Character*>()));
	this->setName("population");
}

Population::~Population() {
}

void Population::update(float deltaTime) {
	(void) deltaTime;
	for(int x = 0; x < population.size(); ++x) {
		for(int y = 0; y < population[0].size(); ++y) {
			population[x][y].clear();
		}
	}
	for(std::list<GameObject*>::iterator it = children.begin(); it != children.end(); ++it) {
		Character* c = static_cast<Character*>(*it);
		population[floor(c->getPosition().x)][floor(c->getPosition().y)].push_back(c);
	}
}

void Population::onObjectAdd(GameObject* object) {
	Character* c = dynamic_cast<Character*>(object);
	VBE_ASSERT(c != NULL, "Population nodes should not have non-Character children");
}

int Population::getPlayerCount()
{
	return 1;
}

Player* Population::getPlayer(int i)
{
	return getFirstObjectOfType<Player>();
}
