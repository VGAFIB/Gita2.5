#include "House.hpp"

const int House::houseTypeCount = HOUSE_COUNT;

const House::HouseData House::houseTypes[HOUSE_COUNT] = {
	HouseData(8,8,"ajuntament8x8Mesh"	,"ajuntament8x8Tex", 1),
	HouseData(8,8,"construccio8x8Mesh"	,"construccio8x8Tex", 1),
	HouseData(8,8,"hospital8x8Mesh"		,"hospital8x8Tex", 1),
	HouseData(6,2,"2x6_0Mesh"		    ,"2x6_0Tex",0.3),
	HouseData(6,2,"2x6_1Mesh"			,"2x6_1Tex",0.3),
	HouseData(6,2,"2x6_2Mesh"		    ,"4x4_2Tex",0.3),
	HouseData(6,2,"2x6_3Mesh"			,"4x4_3Tex",0.3),
	HouseData(4,4,"4x4_0AltMesh"		,"4x4_0Tex",0.3),
	HouseData(4,4,"4x4_0BaixMesh"		,"4x4_0Tex",0.3),
	HouseData(4,4,"4x4_0CentreMesh"		,"4x4_0Tex",0.3),
	HouseData(4,4,"4x4_1AltMesh"		,"4x4_1Tex",0.3),
	HouseData(4,4,"4x4_1BaixMesh"		,"4x4_1Tex",0.3),
	HouseData(4,4,"4x4_1CentreMesh"		,"4x4_1Tex",0.3),
	HouseData(4,4,"4x4_2AltMesh"		,"4x4_2Tex",0.3),
	HouseData(4,4,"4x4_2BaixMesh"		,"4x4_2Tex",0.3),
	HouseData(4,4,"4x4_2CentreMesh"		,"4x4_2Tex",0.3),
	HouseData(4,4,"4x4_3AltMesh"		,"4x4_3Tex",0.3),
	HouseData(4,4,"4x4_3BaixMesh"		,"4x4_3Tex",0.3),
	HouseData(4,4,"4x4_3CentreMesh"		,"4x4_3Tex",0.3),
	HouseData(4,4,"4x4_4Mesh"			,"4x4_4Tex",0.3)
};


House::House(int x, int y, int type) {
	VBE_ASSERT(type < houseTypeCount && type >= 0, type << " is not a valid house type");
	transform = glm::translate(mat4f(1.0),vec3f(x, 0, y));
	house.mesh = Meshes.get(houseTypes[type].mesh);
	texName = houseTypes[type].texture;
	house.program = Programs.get("houseProgram");
}

House::~House() {
}

void House::draw() const {
	house.program->uniform("sampler")->set(Textures.get(texName));
	house.program->uniform("modelViewProjectionMatrix")->set(fullTransform);
	house.draw();
}
