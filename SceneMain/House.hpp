#ifndef HOUSE_HPP
#define HOUSE_HPP
#include "Commons.hpp"

class House : public GameObject {
	public:
		struct HouseData {
				HouseData(unsigned int w, unsigned int d, std::string m, std::string t)
					: width(w), depth(d), model(m), texture(t) {}
				unsigned int width;
				unsigned int depth;
				std::string model;
				std::string texture;
		};
		static const int houseTypeCount;
		static const HouseData houseTypes[19];

		House(int x, int y, int type);
		virtual ~House();

		void draw() const;
	private:
		Model house;
		std::string texName;
};

#endif // HOUSE_HPP
