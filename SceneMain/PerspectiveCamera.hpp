#ifndef PERSPECTIVECAMERA_HPP
#define PERSPECTIVECAMERA_HPP

#include "GameObject.hpp"

class PerspectiveCamera : public GameObject {
	public:
		PerspectiveCamera(const vec3f& pos);
		vec3f pos;

		void setView(const mat4f& newView);
		mat4f getView();
	private:
		mat4f view;
};

#endif // PERSPECTIVECAMERA_HPP
