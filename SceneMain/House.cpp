#include "House.hpp"
#include "../Game.hpp"

House::House(GameObject* parent, int x, int y, int width, int depth) :
	GameObject(parent) {
	house.mesh = MeshManager::get("house");
	house.program = ShaderManager::get("sample");

	transform = glm::translate(mat4f(1.0),vec3f(x, 0, y));
	transform = glm::scale(transform,vec3f(float(width)/10.0f,log(x*y)/15.0f + Utils::randomFloat(0.1,0.3),float(depth)/10.0f));
	transform = glm::translate(transform,vec3f(0, 0, 10));
}

House::~House() {
}

void House::draw() const {
	house.program->uniform("sampler")->set(TextureManager::get("cubetex"));
	house.program->uniform("modelViewProjectionMatrix")->set(fullTransform);
	house.draw();
}
