#include "PerspectiveCamera.hpp"
#include "../Game.hpp"

PerspectiveCamera::PerspectiveCamera(const vec3f& pos, const vec3f& rot, const mat4f& projection)
	: pos(pos), rot(rot), projection(projection) {
	this->projection = glm::perspective(FOV,float(SCRWIDTH)/float(SCRHEIGHT),ZNEAR,ZFAR);
}

void PerspectiveCamera::update(float deltaTime) {
	(void) deltaTime;
	if(InputManager::isKeyDown(sf::Keyboard::A))
		pos.x -= 10*deltaTime;
	if(InputManager::isKeyDown(sf::Keyboard::D))
		pos.x += 10*deltaTime;
	if(InputManager::isKeyDown(sf::Keyboard::W))
		pos.z -= 10*deltaTime;
	if(InputManager::isKeyDown(sf::Keyboard::S))
		pos.z += 10*deltaTime;
	if(InputManager::isKeyDown(sf::Keyboard::Space))
		pos += vec3f(0,-5*deltaTime,-5*deltaTime);
	if(InputManager::isKeyDown(sf::Keyboard::LShift))
		pos += vec3f(0,5*deltaTime,5*deltaTime);
	transform = projection;
	transform = glm::rotate(transform,rot.x,vec3f(1,0,0));
	transform = glm::rotate(transform,rot.y,vec3f(0,1,0));
	transform = glm::rotate(transform,rot.z,vec3f(0,0,1));
	transform = glm::translate(transform, -pos);
}
