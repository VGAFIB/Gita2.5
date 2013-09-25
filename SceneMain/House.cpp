#include "House.hpp"
#include "../Game.hpp"

const int House::houseTypes[][2] = {
	{8, 8},
	{4, 4},
	{5, 3},
	{2, 6},
	{6, 2}
};
const int House::houseTypeCount = 5;

House::House(int x, int y, int width, int depth) {
	house.mesh = MeshManager::get("house");
	house.program = ShaderManager::get("sample");

	transform = glm::translate(mat4f(1.0),vec3f(x, 0, y));
	transform = glm::scale(transform,vec3f(float(width)/10.0f,log(x*y)/15.0f + Utils::randomFloat(0.1,0.3),float(depth)/10.0f));
	transform = glm::translate(transform,vec3f(0, 0, 10));
}

House::~House() {
}

void House::draw() const {
	house.program->uniform("sampler")->set(TextureManager::get("housetex"));
	house.program->uniform("modelViewProjectionMatrix")->set(fullTransform);
	house.draw();
}
