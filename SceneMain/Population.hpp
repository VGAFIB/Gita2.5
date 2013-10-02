#ifndef POPULATION_HPP
#define POPULATION_HPP
#include "Commons.hpp"

class Character;
class Population : GameObject {
		enum SearchType {
			SEARCH_ANY,
			SEARCH_DEAD,
			SEARCH_PANIC
		};

	public:
		Population();
		~Population();

		void update(float deltaTime);

		template<class T>
		std::vector<T*> getNearbyCharacters(vec2f pos, float r, SearchType st) {
			return std::vector<T*>();
		}

	private:
		std::vector<std::vector<std::list<Character*> > > population;
		void onObjectAdd(GameObject *object);
};

#endif // POPULATION_HPP
