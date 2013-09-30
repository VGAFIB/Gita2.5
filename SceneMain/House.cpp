#include "House.hpp"

const int House::houseTypes[][2] = {
	{8, 8},
	{4, 4},
	{5, 3},
	{2, 6},
	{6, 2}
};
const int House::houseTypeCount = 5;

House::House(int x, int y, int type) {
	VBE_ASSERT(type < houseTypeCount && type >= 0, type << " is not a valid house type");
	transform = glm::translate(mat4f(1.0),vec3f(x, 0, y));
	switch(type) {
		case 0:
			house.mesh = MeshManager::get("8x8_0");
			texName =  "8x8_0";
			break;
		case 1: {
			int random = Utils::randomInt(0,12);
			house.mesh = MeshManager::get("4x4_"+Utils::toString(random));
			texName =  "4x4_"+Utils::toString(random-random%3);
			break;
		}
		default: {
			int random = Utils::randomInt(0,12);
			house.mesh = MeshManager::get("4x4_"+Utils::toString(random));
			texName =  "4x4_"+Utils::toString(random-random%3);
			transform = glm::scale(transform,vec3f(float(houseTypes[type][0])/4.0f,1.0f,float(houseTypes[type][1])/4.0f));
			break;
		}
	}
	house.program = ShaderManager::get("sample");
}

House::~House() {
}

void House::draw() const {
	house.program->uniform("sampler")->set(TextureManager::get(texName));
	house.program->uniform("modelViewProjectionMatrix")->set(fullTransform);
	house.draw();
}
