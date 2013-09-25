#ifndef HOUSE_HPP
#define HOUSE_HPP
#include "GameObject.hpp"
#include "../graphics/Model.hpp"

class House : public GameObject {
	public:
		static const int houseTypes[][2];
		static const int houseTypeCount;

		House(int x, int y, int width, int depth);
		virtual ~House();

		void draw() const;
	private:
		Model house;
};

#endif // HOUSE_HPP
