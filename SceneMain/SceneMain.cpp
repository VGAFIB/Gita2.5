#include "SceneMain.hpp"
#include "../Game.hpp"
#include "PerspectiveCamera.hpp"
#include "Map.hpp"
#include "House.hpp"

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
	cam->pos = vec3f(-150,-20,-100);
	cam->projection = glm::perspective(FOV,float(SCRWIDTH)/float(SCRHEIGHT),ZNEAR,ZFAR);
	cam->view = glm::rotate(mat4f(1.0),45.0f,vec3f(1,0,0));
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
	if(!TextureManager::load("4x4_0","data/textures/4x4_0.png",2))
		return false;
	if(!TextureManager::load("4x4_3","data/textures/4x4_3.png",2))
		return false;
	if(!TextureManager::load("4x4_6","data/textures/4x4_6.png",2))
		return false;
	if(!TextureManager::load("4x4_9","data/textures/4x4_9.png",2))
		return false;
	if(!TextureManager::load("4x4_12","data/textures/4x4_12.png",2))
		return false;
	if(!TextureManager::load("8x8_0","data/textures/8x8_0.png",2))
		return false;
	//Create meshes
	MeshManager::add("4x4_0",new Mesh("data/models/4x4_0.obj"));
	MeshManager::add("4x4_1",new Mesh("data/models/4x4_1.obj"));
	MeshManager::add("4x4_2",new Mesh("data/models/4x4_2.obj"));
	MeshManager::add("4x4_3",new Mesh("data/models/4x4_3.obj"));
	MeshManager::add("4x4_4",new Mesh("data/models/4x4_4.obj"));
	MeshManager::add("4x4_5",new Mesh("data/models/4x4_5.obj"));
	MeshManager::add("4x4_6",new Mesh("data/models/4x4_6.obj"));
	MeshManager::add("4x4_7",new Mesh("data/models/4x4_7.obj"));
	MeshManager::add("4x4_8",new Mesh("data/models/4x4_8.obj"));
	MeshManager::add("4x4_9",new Mesh("data/models/4x4_9.obj"));
	MeshManager::add("4x4_10",new Mesh("data/models/4x4_10.obj"));
	MeshManager::add("4x4_11",new Mesh("data/models/4x4_11.obj"));
	MeshManager::add("4x4_12",new Mesh("data/models/4x4_12.obj"));
	MeshManager::add("8x8_0",new Mesh("data/models/8x8_0.obj"));
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


