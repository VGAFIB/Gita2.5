#ifndef HOUSE_HPP
#define HOUSE_HPP
#include "GameObject.hpp"
#include "../graphics/Model.hpp"

class House : public GameObject {
	public:
		static const int houseTypes[][2];
		static const int houseTypeCount;

		House(int x, int y, int type);
		virtual ~House();

		void draw() const;
	private:
		Model house;
		std::string texName;
};

#endif // HOUSE_HPP
