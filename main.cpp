#include "SceneMain/SceneMain.hpp"

int main() {
	ZNEAR = 0.01f;
	ZFAR = 1000.0f;
	WINDOW_TITLE = "Gita";
	Game game;
	game.setRoot(new SceneMain());
	game.run();
	return 42;
}
