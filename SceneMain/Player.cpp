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

    myMoney = 0;
    myKills = 0;

    jailed = false;
	vel = 5;
	anim.setAnimData(Animations.get("takena"));
	texName = "player";

	this->setName("player");
	position = vec2f(map->getRandomStreet())+0.5f;
	CameraController* controller = new CameraController();
	controller->addTo(this);
}

void Player::hitAction()
{
    actionDelay = 0.18f;
}

vec2f Player::moveCharacter(float delta) {

	drawDead = jailed;
	if(jailed) {
        jailedTime += delta;
        return vec2f(0, 0);
    }

	playerInput.update();


	if (playerInput.getKeyDown(PlayerInput::PLAYER_ACTION)) {

        hitAction();
		std::vector<Person*> persons = population->getNearbyCharacters<Person>(position, 1);
        for (std::vector<Person*>::iterator it = persons.begin(); it != persons.end(); ++it) {
			if ((*it)->getState() == Person::STATE_DEAD) continue;

			(*it)->doDeath();
            int n_moneys = Utils::randomInt(1, 3);
			//for (int i = 0; i < n_moneys; ++i) scene->spawnNewMoney((*it)->getPosition());
        }
    }


//    anim->Update(delta);

    /*
    for (std::list<Item>::iterator it = scene->itemList.begin(); it != scene->itemList.end(); ++it) {
        if (it->isTakeable()) {

            sf::FloatRect moneyBox = this->getBoundBox();
            moneyBox.left -= moneyBox.width/6;
            moneyBox.width *= 3;
            moneyBox.top -= moneyBox.height/6;
            moneyBox.height *= 3;

            if (Utils::rectCollision(it->getBoundBox(), moneyBox)) {
                it->takeAction();
                myMoney += it->getValue();
            }
        }
    }*/

    if (actionDelay <= 0)
    {
        vec2f dir (0, 0);

		if (playerInput.getKeyState(PlayerInput::PLAYER_UP) && !playerInput.getKeyState(PlayerInput::PLAYER_DOWN))
            dir.y = -1;
		if (playerInput.getKeyState(PlayerInput::PLAYER_DOWN) && !playerInput.getKeyState(PlayerInput::PLAYER_UP))
            dir.y = 1;
		if (playerInput.getKeyState(PlayerInput::PLAYER_LEFT) && !playerInput.getKeyState(PlayerInput::PLAYER_RIGHT))
            dir.x = -1;
		if (playerInput.getKeyState(PlayerInput::PLAYER_RIGHT) && !playerInput.getKeyState(PlayerInput::PLAYER_LEFT))
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
