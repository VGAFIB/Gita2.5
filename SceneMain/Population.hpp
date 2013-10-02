#ifndef POPULATION_HPP
#define POPULATION_HPP
#include "Commons.hpp"

class Character;
class Player;

class Population : public GameObject {

	public:
		Population();
		~Population();

		void update(float deltaTime);

		template<class T>
		std::vector<T*> getNearbyCharacters(vec2f pos, float r) {
			return std::vector<T*>();
		}

		template<class T>
		std::vector<T*> getSeenCharacters(vec2f pos) {
			return std::vector<T*>();
		}

		int getPlayerCount();
		Player* getPlayer(int i);

	private:
		std::vector<std::vector<std::list<Character*> > > population;
		void onObjectAdd(GameObject *object);
};

#endif // POPULATION_HPP
