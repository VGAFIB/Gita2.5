#include "CameraController.hpp"
#include "Player.hpp"
#include "PerspectiveCamera.hpp"

CameraController::CameraController() {
	this->setUpdatePriority(1);
}

CameraController::~CameraController() {

}

void CameraController::update(float deltaTime) {
	(void) deltaTime;
	PerspectiveCamera* cam = static_cast<PerspectiveCamera*>(getGame()->getObjectByName("cam"));
	Player* player = static_cast<Player*>(getGame()->getObjectByName("player"));
	cam->pos = vec3f(player->getPosition().x,12,player->getPosition().y+12);
}
