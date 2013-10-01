#include "SceneMain.hpp"
#include "PerspectiveCamera.hpp"
#include "Map.hpp"
#include "House.hpp"
#include "Person.hpp"

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
	for(int i = 0; i < 1000; ++i) {
		cam->addObject(new Person());
	}
}

SceneMain::~SceneMain() {
	TEXTURES.clear();
	MESHES.clear();
	PROGRAMS.clear();
	AudioManager::clear();
}

bool SceneMain::loadResources() {
	//shaders
	ShaderProgram* p = new ShaderProgram();
	if(!p->makeProgram("data/shaders/sample.vert","data/shaders/sample.frag")) return false;
	PROGRAMS.add("sample",p);
	p = new ShaderProgram();
	if(!p->makeProgram("data/shaders/sample2.vert","data/shaders/sample2.frag")) return false;
	PROGRAMS.add("sample2",p);
	p = new ShaderProgram();
	if(!p->makeProgram("data/shaders/tex.vert","data/shaders/tex.frag")) return false;
	PROGRAMS.add("tex",p);
	//textures
	Texture* tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/4x4_0.png",true)) return false;
	TEXTURES.add("4x4_0",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/4x4_3.png",true)) return false;
	TEXTURES.add("4x4_3",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/4x4_6.png",true)) return false;
	TEXTURES.add("4x4_6",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/4x4_9.png",true)) return false;
	TEXTURES.add("4x4_9",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/4x4_12.png",true)) return false;
	TEXTURES.add("4x4_12",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/8x8_0.png",true)) return false;
	TEXTURES.add("8x8_0",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/6x2_0.png",true)) return false;
	TEXTURES.add("6x2_0",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/6x2_1.png",true)) return false;
	TEXTURES.add("6x2_1",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/person.png")) return false;
	tex->setFilter(GL_NEAREST,GL_NEAREST);
	TEXTURES.add("person",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/person_sheet.png")) return false;
	tex->setFilter(GL_NEAREST,GL_NEAREST);
	TEXTURES.add("person_sheet",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/police_sheet.png")) return false;
	tex->setFilter(GL_NEAREST,GL_NEAREST);
	TEXTURES.add("police_sheet",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/player_sheet.png")) return false;
	tex->setFilter(GL_NEAREST,GL_NEAREST);
	TEXTURES.add("player_sheet",tex);


	//Create meshes
	MESHES.add("4x4_0",new Mesh("data/models/4x4_0.obj"));
	MESHES.add("4x4_1",new Mesh("data/models/4x4_1.obj"));
	MESHES.add("4x4_2",new Mesh("data/models/4x4_2.obj"));
	MESHES.add("4x4_3",new Mesh("data/models/4x4_3.obj"));
	MESHES.add("4x4_4",new Mesh("data/models/4x4_4.obj"));
	MESHES.add("4x4_5",new Mesh("data/models/4x4_5.obj"));
	MESHES.add("4x4_6",new Mesh("data/models/4x4_6.obj"));
	MESHES.add("4x4_7",new Mesh("data/models/4x4_7.obj"));
	MESHES.add("4x4_8",new Mesh("data/models/4x4_8.obj"));
	MESHES.add("4x4_9",new Mesh("data/models/4x4_9.obj"));
	MESHES.add("4x4_10",new Mesh("data/models/4x4_10.obj"));
	MESHES.add("4x4_11",new Mesh("data/models/4x4_11.obj"));
	MESHES.add("4x4_12",new Mesh("data/models/4x4_12.obj"));
	MESHES.add("8x8_0",new Mesh("data/models/8x8_0.obj"));
	MESHES.add("6x2_0",new Mesh("data/models/6x2_0.obj"));
	MESHES.add("6x2_1",new Mesh("data/models/6x2_1.obj"));
	MESHES.add("6x2_2",new Mesh("data/models/6x2_2.obj"));
	MESHES.add("6x2_3",new Mesh("data/models/6x2_3.obj"));

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
		MESHES.add("charModel",charModel);
	}
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


