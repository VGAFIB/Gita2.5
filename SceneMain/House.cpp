#include "House.hpp"

const int House::houseTypeCount = 18;

const House::HouseData House::houseTypes[18] = {
	HouseData(8,8,"8x8_0", "8x8_0"),
	HouseData(4,4,"4x4_0", "4x4_0"),
	HouseData(4,4,"4x4_1", "4x4_0"),
	HouseData(4,4,"4x4_2", "4x4_0"),
	HouseData(4,4,"4x4_3", "4x4_3"),
	HouseData(4,4,"4x4_4", "4x4_3"),
	HouseData(4,4,"4x4_5", "4x4_3"),
	HouseData(4,4,"4x4_6", "4x4_6"),
	HouseData(4,4,"4x4_7", "4x4_6"),
	HouseData(4,4,"4x4_8", "4x4_6"),
	HouseData(4,4,"4x4_9", "4x4_9"),
	HouseData(4,4,"4x4_10", "4x4_9"),
	HouseData(4,4,"4x4_11", "4x4_9"),
	HouseData(4,4,"4x4_12", "4x4_12"),
	HouseData(6,2,"6x2_0", "6x2_0"),
	HouseData(6,2,"6x2_1", "6x2_1"),
	HouseData(6,2,"6x2_2", "4x4_9"),
	HouseData(6,2,"6x2_3", "4x4_6")
};

House::House(int x, int y, int type) {
	VBE_ASSERT(type < houseTypeCount && type >= 0, type << " is not a valid house type");
	transform = glm::translate(mat4f(1.0),vec3f(x, 0, y));
	house.mesh = Meshes.get(houseTypes[type].model);
	texName = houseTypes[type].texture;
	house.program = Programs.get("sample");
}

House::~House() {
}

void House::draw() const {
	house.program->uniform("sampler")->set(Textures.get(texName));
	house.program->uniform("modelViewProjectionMatrix")->set(fullTransform);
	house.draw();
}
