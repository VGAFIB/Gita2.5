#ifndef HOUSE_HPP
#define HOUSE_HPP
#include "GameObject.hpp"
#include "../graphics/Model.hpp"

class House : public GameObject {
	public:
		House(int x, int y, int width, int depth);
		virtual ~House();

		void draw() const;
	private:
		Model house;
};

#endif // HOUSE_HPP
