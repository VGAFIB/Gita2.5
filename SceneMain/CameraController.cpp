#include "CameraController.hpp"
#include "Player.hpp"
#include "PerspectiveCamera.hpp"

CameraController::CameraController() {
	this->setUpdatePriority(1);
}

CameraController::~CameraController() {

}

void CameraController::update(float deltaTime) {
	PerspectiveCamera* cam = static_cast<PerspectiveCamera*>(GameObject::getObjectByName("cam"));
	Player* player = static_cast<Player*>(GameObject::getObjectByName("player"));
	cam->pos = vec3f(player->getPosition().x,3,player->getPosition().y+3);
	VBE_LOG("controller" << this->getUpdatePriority());
}
