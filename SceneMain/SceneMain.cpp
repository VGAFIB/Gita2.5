#include "SceneMain.hpp"
#include "PerspectiveCamera.hpp"
#include "Map.hpp"
#include "House.hpp"
#include "Person.hpp"
#include "Population.hpp"
#include "Police.hpp"
#include "Player.hpp"

SceneMain::SceneMain() : debugCounter(0.0), fpsCount(0) {
	this->setName("SCENE");
	//SCENE INIT
	if (!loadResources()) {
		VBE_LOG("Could not load resources for SceneMain" );
		Game::isRunning = false;
		return;
	}
	//Center mouse
	Input::setMousePos(SCRWIDTH/2,SCRHEIGHT/2,Game::getWindow());
	PerspectiveCamera* cam = new PerspectiveCamera();
	cam->pos = vec3f(150,20,100);
	cam->rot.x = 45.0f;
	addObject(cam);
	cam->addObject(new Map());
	Population* p = new Population();
	cam->addObject(p);
	p->addObject(new Player());
	for(int i = 0; i < 1000; ++i) {
		p->addObject(new Person());
	}
	for(int i = 0; i < 100; ++i) {
		p->addObject(new Police());
	}
}

SceneMain::~SceneMain() {
	Textures.clear();
	Meshes.clear();
	Programs.clear();
	Animations.clear();

	AudioManager::clear();
}

bool SceneMain::loadResources() {
	//shaders
	ShaderProgram* p = new ShaderProgram();
	if(!p->makeProgram("data/shaders/sample.vert","data/shaders/sample.frag")) return false;
	Programs.add("sample",p);
	p = new ShaderProgram();
	if(!p->makeProgram("data/shaders/sample2.vert","data/shaders/sample2.frag")) return false;
	Programs.add("sample2",p);
	p = new ShaderProgram();
	if(!p->makeProgram("data/shaders/tex.vert","data/shaders/tex.frag")) return false;
	Programs.add("tex",p);
	//textures
	Texture* tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/4x4_0.png",true)) return false;
	Textures.add("4x4_0",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/4x4_3.png",true)) return false;
	Textures.add("4x4_3",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/4x4_6.png",true)) return false;
	Textures.add("4x4_6",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/4x4_9.png",true)) return false;
	Textures.add("4x4_9",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/4x4_12.png",true)) return false;
	Textures.add("4x4_12",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/8x8_0.png",true)) return false;
	Textures.add("8x8_0",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/6x2_0.png",true)) return false;
	Textures.add("6x2_0",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/6x2_1.png",true)) return false;
	Textures.add("6x2_1",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/person_sheet.png")) return false;
	tex->setFilter(GL_NEAREST,GL_NEAREST);
	Textures.add("person",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/police_sheet.png")) return false;
	tex->setFilter(GL_NEAREST,GL_NEAREST);
	Textures.add("police",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/player_sheet.png")) return false;
	tex->setFilter(GL_NEAREST,GL_NEAREST);
	Textures.add("player",tex);


	//Create meshes
	Meshes.add("4x4_0",new Mesh("data/models/4x4_0.obj"));
	Meshes.add("4x4_1",new Mesh("data/models/4x4_1.obj"));
	Meshes.add("4x4_2",new Mesh("data/models/4x4_2.obj"));
	Meshes.add("4x4_3",new Mesh("data/models/4x4_3.obj"));
	Meshes.add("4x4_4",new Mesh("data/models/4x4_4.obj"));
	Meshes.add("4x4_5",new Mesh("data/models/4x4_5.obj"));
	Meshes.add("4x4_6",new Mesh("data/models/4x4_6.obj"));
	Meshes.add("4x4_7",new Mesh("data/models/4x4_7.obj"));
	Meshes.add("4x4_8",new Mesh("data/models/4x4_8.obj"));
	Meshes.add("4x4_9",new Mesh("data/models/4x4_9.obj"));
	Meshes.add("4x4_10",new Mesh("data/models/4x4_10.obj"));
	Meshes.add("4x4_11",new Mesh("data/models/4x4_11.obj"));
	Meshes.add("4x4_12",new Mesh("data/models/4x4_12.obj"));
	Meshes.add("8x8_0",new Mesh("data/models/8x8_0.obj"));
	Meshes.add("6x2_0",new Mesh("data/models/6x2_0.obj"));
	Meshes.add("6x2_1",new Mesh("data/models/6x2_1.obj"));
	Meshes.add("6x2_2",new Mesh("data/models/6x2_2.obj"));
	Meshes.add("6x2_3",new Mesh("data/models/6x2_3.obj"));

	//Character quad
	{
		std::vector<Vertex::Element> elements;
		elements.push_back(Vertex::Element(Vertex::Attribute::Position , Vertex::Element::Float, 3));
		elements.push_back(Vertex::Element(Vertex::Attribute::TexCoord , Vertex::Element::Float, 2));

		Vertex::Format format(elements);
		Mesh* charModel = new Mesh(format,0,false);

		struct Vertex {
				Vertex(vec3f pos, vec2f tex) : pos(pos) , tex(tex) {}
				vec3f pos;
				vec2f tex;
		};

		std::vector<Vertex> data;
		data.push_back(Vertex(vec3f(-0.5, 0.0, 0), vec2f(0.0, 1.0)));
		data.push_back(Vertex(vec3f( 0.5, 0.0, 0), vec2f(1.0, 1.0)));
		data.push_back(Vertex(vec3f(-0.5, 1.0, 0), vec2f(0.0, 0.0)));

		data.push_back(Vertex(vec3f( 0.5, 0.0, 0), vec2f(1.0, 1.0)));
		data.push_back(Vertex(vec3f( 0.5, 1.0, 0), vec2f(1.0, 0.0)));
		data.push_back(Vertex(vec3f(-0.5, 1.0, 0), vec2f(0.0, 0.0)));

		charModel->setVertexData(&data[0],data.size());
		Meshes.add("charModel",charModel);
	}

	Animations.add("takena", new Animation("data/anim/takena.anim"));
	Animations.add("poli", new Animation("data/anim/poli.anim"));

	Animations.add("calvo", new Animation("data/anim/calvo.anim"));
	Animations.add("tupe", new Animation("data/anim/tupe.anim"));
	Animations.add("gordo", new Animation("data/anim/gordo.anim"));
	Animations.add("rubiaca", new Animation("data/anim/rubiaca.anim"));
	Animations.add("morenaca", new Animation("data/anim/morenaca.anim"));
	Animations.add("moderno", new Animation("data/anim/moderno.anim"));

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


