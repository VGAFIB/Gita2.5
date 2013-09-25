#include "PerspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera(const vec3f& pos) : pos(pos) {
	view = glm::perspective(FOV,float(SCRWIDTH)/float(SCRHEIGHT),ZNEAR,ZFAR);
	view = glm::rotate(view,45.0f,vec3f(1,0,0));
	view = glm::translate(view,pos);
	transform = view;
}

void PerspectiveCamera::setView(const mat4f& newView) {
	view = newView;
}

mat4f PerspectiveCamera::getView() {
	return view;
}
