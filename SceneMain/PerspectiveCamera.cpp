#include "PerspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera(const vec3f& pos, const vec3f& rot, const mat4f& projection)
	: pos(pos), rot(rot), projection(projection) {
	this->setName("cam");
	this->setUpdatePriority(2);
	this->projection = glm::perspective(FOV,float(SCRWIDTH)/float(SCRHEIGHT),ZNEAR,ZFAR);
}

void PerspectiveCamera::update(float deltaTime) {
	(void) deltaTime;
	transform = projection;
	transform = glm::rotate(transform,rot.x,vec3f(1,0,0));
	transform = glm::rotate(transform,rot.y,vec3f(0,1,0));
	transform = glm::rotate(transform,rot.z,vec3f(0,0,1));
	transform = glm::translate(transform, -pos);
	VBE_LOG("camera");
}
