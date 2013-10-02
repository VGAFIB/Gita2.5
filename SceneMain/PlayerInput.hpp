#ifndef INPUTENGINE_H
#define INPUTENGINE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class PlayerInput
{
public:
	enum Key
	{
		PLAYER_UP, PLAYER_DOWN, PLAYER_LEFT, PLAYER_RIGHT,
		PLAYER_ACTION,
                SHOP_BUY_1, SHOP_BUY_2, SHOP_BUY_3,
                CAM_UP, CAM_DOWN, CAM_LEFT, CAM_RIGHT,
                CAM_ZOOM_IN, CAM_ZOOM_OUT,
		EXIT, NEW_SCENE,
                MENU_START,
		K_SIZE
	};

	PlayerInput();

	void update();

	bool getKeyState(int key);
	bool getKeyUp(int key);
	bool getKeyDown(int key);

	bool isKeyDown(int key);

	bool getMouseDown(sf::Mouse::Button button);
	bool getMouseUp(sf::Mouse::Button button);
	sf::Vector2f getMousePos();
	sf::Vector2f getGlobalMousePos();
	void setGlobalMousePos(const sf::Vector2f& pos);

    std::string encodeToString();
    void decodeFromString(std::string str);

    bool firstUpdate;

private:

	bool keyState[K_SIZE];
	bool keyStateOld[K_SIZE];

	sf::Keyboard::Key keyMap[K_SIZE];

	bool mouseStateOld[sf::Mouse::ButtonCount];
	bool mouseState[sf::Mouse::ButtonCount];

	sf::Vector2i mousePos; //Window coords
	sf::Vector2f globalMousePos; //World coords
};

#endif // INPUTENGINE_H
