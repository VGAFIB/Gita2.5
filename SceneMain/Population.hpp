#ifndef POPULATION_HPP
#define POPULATION_HPP
#include "Commons.hpp"
#include "Character.hpp"
#include "Map.hpp"

class Player;
class Population : public GameObject {

	public:
		Population();
		~Population();

		void update(float deltaTime);

		template<class T>
		std::vector<T*> getNearbyCharacters(vec2f pos, float r) {
			vec2f min = pos - r;
			vec2f max = pos + r;

			vec2i imin = vec2i(min);
			vec2i imax = vec2i(max+1.0f);

			imin = glm::max(imin, vec2i(0, 0));
			imax = glm::min(imax, vec2i(map->getWidth()-1, map->getHeight()-1));

			std::vector<T*> res;
			for(int x = imin.x; x <= imax.x; x++) {
				for(int y = imin.y; y <= imax.y; y++) {
					std::vector<Character*>& v = population[x][y];
					for(int i = 0; i < (int) v.size(); i++)
						if(glm::distance(pos, v[i]->getPosition()) <= r) {
							T* p = dynamic_cast<T*>(v[i]);
							if(p) res.push_back(p);
						}
				}
			}
			return res;
		}

		template<class T>
		std::vector<T*> getSeenCharacters(Character* c) {
			float r = c->getSeeRadius();
			vec2f pos = c->getPosition();
			vec2f min = pos - r;
			vec2f max = pos + r;

			vec2i imin = vec2i(min);
			vec2i imax = vec2i(max+1.0f);

			imin = glm::max(imin, vec2i(0, 0));
			imax = glm::min(imax, vec2i(map->getWidth()-1, map->getHeight()-1));

			std::vector<T*> res;
			for(int x = imin.x; x <= imax.x; x++) {
				for(int y = imin.y; y <= imax.y; y++) {
					std::vector<Character*>& v = population[x][y];
					for(int i = 0; i < (int) v.size(); i++)
						if(glm::distance(pos, v[i]->getPosition()) <= r
								&& c->canSee(v[i]->getPosition())) {
							T* p = dynamic_cast<T*>(v[i]);
							if(p) res.push_back(p);
						}
				}
			}
			return res;
		}

		int getPlayerCount();
		Player* getPlayer(int i);

	private:
		void onObjectAdd(GameObject *object);

		std::vector<std::vector<std::vector<Character*> > > population;
		Map* map;
};

#endif // POPULATION_HPP
