#include "Player.hpp"
#include "Person.hpp"
#include "SceneMain.hpp"
#include "Map.hpp"
#include "Population.hpp"
#include "PerspectiveCamera.hpp"
#include "CameraController.hpp"

Player::Player() : Character()
{
	position.x = 0;
	position.y = 0;

    actionDelay = 0;

    jailed = false;
	vel = 5;
	anim.setAnimData(Animations.get("takena"));
	texName = "playerTex";

	this->setName("player");
	position = vec2f(map->getRandomStreet())+0.5f;
	CameraController* controller = new CameraController();
	controller->addTo(this);
}

void Player::hitAction() {
	actionDelay = 0.18f;
}

vec2f Player::moveCharacter(float delta) {

	drawDead = jailed;
	if(jailed) {
        jailedTime += delta;
        return vec2f(0, 0);
	}

	if (Input::isKeyDown(sf::Keyboard::Space)) {
        hitAction();
		std::vector<Person*> persons = population->getNearbyCharacters<Person>(position, 1);
        for (std::vector<Person*>::iterator it = persons.begin(); it != persons.end(); ++it) {
			if ((*it)->getState() == Person::STATE_DEAD) continue;
			(*it)->doDeath();
        }
	}

	if (actionDelay <= 0) {
        vec2f dir (0, 0);
		if (Input::isKeyDown(sf::Keyboard::W) && !Input::isKeyDown(sf::Keyboard::S))
            dir.y = -1;
		if (Input::isKeyDown(sf::Keyboard::S) && !Input::isKeyDown(sf::Keyboard::W))
            dir.y = 1;
		if (Input::isKeyDown(sf::Keyboard::A) && !Input::isKeyDown(sf::Keyboard::D))
            dir.x = -1;
		if (Input::isKeyDown(sf::Keyboard::D) && !Input::isKeyDown(sf::Keyboard::A))
			dir.x = 1;
		action = "Idle";
		return dir*vel*delta;
    }
    else
    {
        actionDelay -= delta;
		action = "Attack";
        return vec2f(0, 0);
    }

}

void Player::gotCaught() {
    if(jailed) return;

    jailed = true;
    jailedTime = 0;
}
