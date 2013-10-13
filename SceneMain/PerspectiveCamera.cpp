#include "PerspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera(const vec3f& pos, const vec3f& rot, const mat4f& projection)
	: pos(pos), rot(rot), projection(projection) {
	this->setName("cam");
	this->setUpdatePriority(2);
	this->projection = glm::perspective(FOV,float(SCRWIDTH)/float(SCRHEIGHT),ZNEAR,ZFAR);
}

void PerspectiveCamera::update(float deltaTime) {
	(void) deltaTime;
	view = glm::rotate(mat4f(1.0),rot.x,vec3f(1,0,0));
	view = glm::rotate(view,rot.y,vec3f(0,1,0));
	view = glm::rotate(view,rot.z,vec3f(0,0,1));
	view = glm::translate(view, -pos);
}
