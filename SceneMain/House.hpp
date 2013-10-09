#ifndef HOUSE_HPP
#define HOUSE_HPP
#include "Commons.hpp"
#define HOUSE_COUNT 20

class House : public GameObject {
	public:
		struct HouseData {
				HouseData(unsigned int w, unsigned int d, std::string m, std::string t, float probability)
					: width(w), depth(d), mesh(m), texture(t), probability(probability) {}
				unsigned int width;
				unsigned int depth;
				std::string mesh;
				std::string texture;
				float probability;
		};
		static const int houseTypeCount;
		static const HouseData houseTypes[HOUSE_COUNT];

		House(int x, int y, int type);
		virtual ~House();

		void draw() const;
	private:
		Model house;
		std::string texName;
};

#endif // HOUSE_HPP
