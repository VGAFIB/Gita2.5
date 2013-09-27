#ifndef PERSPECTIVECAMERA_HPP
#define PERSPECTIVECAMERA_HPP

#include "GameObject.hpp"

class PerspectiveCamera : public GameObject {
	public:
		PerspectiveCamera(const vec3f& pos = vec3f(0.0f), const vec3f& rot = vec3f(0.0f), const mat4f& projection = mat4f(1.0f));

		void update(float deltaTime);

		vec3f pos;
		vec3f rot;
		mat4f projection;
};

#endif // PERSPECTIVECAMERA_HPP
