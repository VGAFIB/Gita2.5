#include "PerspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera(const vec3f& pos, const mat4f& view, const mat4f& projection)
	: pos(pos), view(view), projection(projection) {
}

void PerspectiveCamera::update(float deltaTime) {
	(void) deltaTime;
	transform = projection*view;
}
