#include "SceneMain.hpp"
#include "../Game.hpp"
#include "PerspectiveCamera.hpp"
#include "Map.hpp"

SceneMain::SceneMain() : debugCounter(0.0), fpsCount(0) {
	this->setName("SCENE");
	//SCENE INIT
	if (!loadResources()) {
		VBE_LOG("Could not load resources for SceneMain" );
		Game::isRunning = false;
		return;
	}
	//Center mouse
	InputManager::setMousePos(SCRWIDTH/2,SCRHEIGHT/2,Game::getWindow());
	PerspectiveCamera* cam = new PerspectiveCamera();
	cam->pos = vec3f(-150,-200,-100);
	cam->projection = glm::perspective(FOV,float(SCRWIDTH)/float(SCRHEIGHT),ZNEAR,ZFAR);
	cam->view = glm::rotate(mat4f(1.0),90.0f,vec3f(1,0,0));
	cam->view = glm::translate(cam->view,cam->pos);
	addObject(cam);
	cam->addObject(new Map());
}

SceneMain::~SceneMain() {
	TextureManager::clear();
	MeshManager::clear();
	ShaderManager::clear();
	AudioManager::clear();
}

bool SceneMain::loadResources() {
	//shaders
	if(!ShaderManager::load("sample","data/shaders/sample.vert","data/shaders/sample.frag"))
		return false;
	if(!ShaderManager::load("sample2","data/shaders/sample2.vert","data/shaders/sample2.frag"))
		return false;
	//textures
	if(!TextureManager::load("housetex","data/textures/10x10tex.png",2))
		return false;
	//Create meshes
	MeshManager::add("house",new Mesh("data/models/10x10.obj"));
	return true;
}

void SceneMain::update(float deltaTime) {
	++fpsCount;
	debugCounter += deltaTime;
	if (debugCounter > 1) {
		VBE_LOG("FPS: " << fpsCount << ". Amount of GameObjects: " << GameObject::getObjectCount() );
		debugCounter--;
		fpsCount = 0;
	}
}


