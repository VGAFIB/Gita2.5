#include "SceneMain/SceneMain.hpp"


int main() {
	ZNEAR = 0.01f;
	ZFAR = 1000.0f;
	WINDOW_TITLE = "Gita";
	if(Game::init()) {
		Game::setRoot(new SceneMain());
		Game::run();
	}
	return 42;
}
