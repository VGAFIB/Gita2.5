#ifndef CAMERACONTROLLER_HPP
#define CAMERACONTROLLER_HPP

#include "Commons.hpp"

class CameraController: public GameObject {
	public:
		CameraController();
		virtual ~CameraController();
		virtual void update(float deltaTime);
};

#endif // CAMERACONTROLLER_HPP
