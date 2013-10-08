#include "House.hpp"

const int House::houseTypeCount = HOUSE_COUNT;

const House::HouseData House::houseTypes[HOUSE_COUNT] = {
	HouseData(8,8,"ajuntament8x8"	,"ajuntament8x8", 1),
	HouseData(8,8,"construccio8x8"	,"construccio8x8", 1),
	HouseData(8,8,"hospital8x8"		,"hospital8x8", 1),
	HouseData(6,2,"2x6_0"		    ,"2x6_0",0.3),
	HouseData(6,2,"2x6_1"			,"2x6_1",0.3),
	HouseData(6,2,"2x6_2"		    ,"4x4_2",0.3),
	HouseData(6,2,"2x6_3"			,"4x4_3",0.3),
	HouseData(4,4,"4x4_0Alt"		,"4x4_0",0.3),
	HouseData(4,4,"4x4_0Baix"		,"4x4_0",0.3),
	HouseData(4,4,"4x4_0Centre"		,"4x4_0",0.3),
	HouseData(4,4,"4x4_1Alt"		,"4x4_1",0.3),
	HouseData(4,4,"4x4_1Baix"		,"4x4_1",0.3),
	HouseData(4,4,"4x4_1Centre"		,"4x4_1",0.3),
	HouseData(4,4,"4x4_2Alt"		,"4x4_2",0.3),
	HouseData(4,4,"4x4_2Baix"		,"4x4_2",0.3),
	HouseData(4,4,"4x4_2Centre"		,"4x4_2",0.3),
	HouseData(4,4,"4x4_3Alt"		,"4x4_3",0.3),
	HouseData(4,4,"4x4_3Baix"		,"4x4_3",0.3),
	HouseData(4,4,"4x4_3Centre"		,"4x4_3",0.3),
	HouseData(4,4,"4x4_4"			,"4x4_4",0.3)
};


House::House(int x, int y, int type) {
	VBE_ASSERT(type < houseTypeCount && type >= 0, type << " is not a valid house type");
	transform = glm::translate(mat4f(1.0),vec3f(x, 0, y));
	house.mesh = Meshes.get(houseTypes[type].model);
	texName = houseTypes[type].texture;
	house.program = Programs.get("house");
}

House::~House() {
}

void House::draw() const {
	house.program->uniform("sampler")->set(Textures.get(texName));
	house.program->uniform("modelViewProjectionMatrix")->set(fullTransform);
	house.draw();
}
