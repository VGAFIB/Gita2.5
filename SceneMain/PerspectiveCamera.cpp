#include "PerspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera(vec3f pos) : pos(pos) {
	transform = glm::perspective(FOV,float(SCRWIDTH)/float(SCRHEIGHT),ZNEAR,ZFAR);
	transform = glm::rotate(transform,90.0f,vec3f(1,0,0));
	transform = glm::translate(transform,pos);
}
