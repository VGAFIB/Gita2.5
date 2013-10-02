#include "Population.hpp"
#include "Character.hpp"

Population::Population() {
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
	for(std::list<GameObject*>::iterator it; it != children.end(); ++it) {
		Character* c = static_cast<Character*>(*it);
		population[floor(c->getPosition().x)][floor(c->getPosition().y)].push_back(c);
	}
}

void Population::onObjectAdd(GameObject* object) {
	Character* c = dynamic_cast<Character*>(object);
	VBE_ASSERT(c != NULL, "Population nodes should not have non-Character children");
}
