#include "PerspectiveCamera.hpp"
#include "../Game.hpp"

PerspectiveCamera::PerspectiveCamera(const vec3f& pos, const mat4f& view, const mat4f& projection)
	: pos(pos), view(view), projection(projection) {
}

void PerspectiveCamera::update(float deltaTime) {
	(void) deltaTime;
	if(InputManager::isKeyDown(sf::Keyboard::A)) {
		pos.x -= 10*deltaTime;
		view = glm::translate(view,vec3f(10*deltaTime,0,0));
	}
	if(InputManager::isKeyDown(sf::Keyboard::D)) {
		pos.x += 10*deltaTime;
		view = glm::translate(view,vec3f(-10*deltaTime,0,0));
	}
	if(InputManager::isKeyDown(sf::Keyboard::W)) {
		pos.z -= 10*deltaTime;
		view = glm::translate(view,vec3f(0,0,10*deltaTime));
	}
	if(InputManager::isKeyDown(sf::Keyboard::S)) {
		pos.z += 10*deltaTime;
		view = glm::translate(view,vec3f(0,0,-10*deltaTime));
	}
	if(InputManager::isKeyDown(sf::Keyboard::Space)) {
		pos += vec3f(0,-5*deltaTime,-5*deltaTime);
		view = glm::translate(view,vec3f(0,5*deltaTime,5*deltaTime));
	}
	if(InputManager::isKeyDown(sf::Keyboard::LShift)) {
		pos += vec3f(0,5*deltaTime,5*deltaTime);
		view = glm::translate(view,vec3f(0,-5*deltaTime,-5*deltaTime));
	}
	transform = projection*view;
}
