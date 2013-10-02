#include "Input.hpp"
#include <iostream>

Input::Input()
{
	keyMap[PLAYER_UP] = sf::Keyboard::W;
	keyMap[PLAYER_DOWN] = sf::Keyboard::S;
	keyMap[PLAYER_LEFT] = sf::Keyboard::A;
	keyMap[PLAYER_RIGHT] = sf::Keyboard::D;

	keyMap[CAM_UP] = sf::Keyboard::Up;
	keyMap[CAM_DOWN] = sf::Keyboard::Down;
	keyMap[CAM_LEFT] = sf::Keyboard::Left;
	keyMap[CAM_RIGHT] = sf::Keyboard::Right;

	keyMap[CAM_ZOOM_IN] = sf::Keyboard::F1;
	keyMap[CAM_ZOOM_OUT] = sf::Keyboard::F2;

	keyMap[SHOP_BUY_1] = sf::Keyboard::Num1;
	keyMap[SHOP_BUY_2] = sf::Keyboard::Num2;
	keyMap[SHOP_BUY_3] = sf::Keyboard::Num3;

	keyMap[NEW_SCENE] = sf::Keyboard::Return;

	keyMap[PLAYER_ACTION] = sf::Keyboard::Space;

	keyMap[MENU_START] = sf::Keyboard::Return;

	keyMap[EXIT] = sf::Keyboard::Escape;

    for (int i = 0; i < K_SIZE; ++i)
		keyState[i] = keyStateOld[i] = false;

    firstUpdate = true;

}


std::string Input::encodeToString() {

    std::string encoded(K_SIZE, ' ');

    for (int i = 0; i < K_SIZE; ++i)
		encoded[i] = keyState[i] ? '1' : '0';

    return encoded;
}

void Input::decodeFromString(std::string encoded) {

    for (int i = 0; i < K_SIZE; ++i)
    {
		keyStateOld[i] = keyState[i];
		keyState[i] = encoded[i] == '1';
    }

    if(firstUpdate)
        for (int i = 0; i < K_SIZE; ++i)
			keyStateOld[i] = keyState[i];
    firstUpdate = false;
}

void Input::update()
{
    //MousePos = sf::Mouse::getPosition(*App);

    for (int i = 0; i < sf::Mouse::ButtonCount; ++i)
    {
		mouseState[i] = mouseState[i];
		mouseState[i] = sf::Mouse::isButtonPressed((sf::Mouse::Button)i);
    }

    for (int i = 0; i < K_SIZE; i++)
    {
		keyStateOld[i] = keyState[i];
		keyState[i] = sf::Keyboard::isKeyPressed(keyMap[i]);
    }


    if(firstUpdate)
        for (int i = 0; i < K_SIZE; ++i)
			keyStateOld[i] = keyState[i];
    firstUpdate = false;
}

bool Input::getKeyState(int key) {
	return keyState[key];
}

bool Input::getKeyUp(int key) {
	return keyStateOld[key] && !keyState[key];
}

bool Input::getKeyDown(int key) {
	return !keyStateOld[key] && keyState[key];
}

bool Input::getMouseDown(sf::Mouse::Button button) {
	return !mouseState[button] && mouseState[button];
}

bool Input::getMouseUp(sf::Mouse::Button button) {
	return mouseState[button] && !mouseState[button];
}

sf::Vector2f Input::getMousePos() {
    //return App->convertCoords(MousePos);
}

sf::Vector2f Input::getGlobalMousePos() {
    return globalMousePos;
}

void Input::setGlobalMousePos(const sf::Vector2f& pos) {
    globalMousePos = pos;
}

