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
	if (!loadResources())
		VBE_ASSERT(false, "Could not load resources for SceneMain" );

	//Center mouse
//	Input::setMousePos(SCRWIDTH/2,SCRHEIGHT/2,game->getWindow());

	//GL stuff..: root(NULL)
	glClearColor(0.1,0.2,0.05,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.01f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE); //enable backface culling
	glCullFace(GL_BACK);

	//Create camera
	PerspectiveCamera* cam = new PerspectiveCamera();
	cam->pos = vec3f(150,20,100);
	cam->rot.x = 45.0f;
	cam->addTo(this);

	//Create stuff
	Map* map = new Map();
	map->addTo(this);

	Population* pop = new Population();
	pop->addTo(this);

	Player* player = new Player();
	player->addTo(pop);

	for(int i = 0; i < 1000; ++i) {
		Person* person = new Person();
		person->addTo(pop);
	}
	for(int i = 0; i < 33; ++i) {
		Police* police = new Police();
		police->addTo(pop);
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
	if(!p->makeProgram("data/shaders/house.vert","data/shaders/house.frag")) return false;
	Programs.add("houseProgram",p);
	p = new ShaderProgram();
	if(!p->makeProgram("data/shaders/map.vert","data/shaders/map.frag")) return false;
	Programs.add("mapProgram",p);
	p = new ShaderProgram();
	if(!p->makeProgram("data/shaders/character.vert","data/shaders/character.frag")) return false;
	Programs.add("characterProgram",p);
	p = new ShaderProgram();
	if(!p->makeProgram("data/shaders/mark.vert","data/shaders/mark.frag")) return false;
	Programs.add("markProgram",p);
	//textures
	Texture* tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/2x6_0.png",true)) return false;
	Textures.add("2x6_0Tex",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/2x6_1.png",true)) return false;
	Textures.add("2x6_1Tex",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/4x4_0.png",true)) return false;
	Textures.add("4x4_0Tex",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/4x4_1.png",true)) return false;
	Textures.add("4x4_1Tex",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/4x4_2.png",true)) return false;
	Textures.add("4x4_2Tex",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/4x4_3.png",true)) return false;
	Textures.add("4x4_3Tex",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/4x4_4.png",true)) return false;
	Textures.add("4x4_4Tex",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/ajuntament8x8.png",true)) return false;
	Textures.add("ajuntament8x8Tex",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/construccio8x8.png",true)) return false;
	Textures.add("construccio8x8Tex",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/hospital8x8.png",true)) return false;
	Textures.add("hospital8x8Tex",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/person_sheet.png")) return false;
	tex->setFilter(GL_NEAREST,GL_NEAREST);
	Textures.add("personTex",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/police_sheet.png")) return false;
	tex->setFilter(GL_NEAREST,GL_NEAREST);
	Textures.add("policeTex",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/player_sheet.png")) return false;
	tex->setFilter(GL_NEAREST,GL_NEAREST);
	Textures.add("playerTex",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/blood1.png")) return false;
	tex->setFilter(GL_NEAREST,GL_NEAREST);
	Textures.add("blood1Tex",tex);
	tex = new Texture(1);
	if(!tex->loadFromFile("data/textures/exc.png")) return false;
	tex->setFilter(GL_NEAREST,GL_NEAREST);
	Textures.add("excTex",tex);

	//Create meshes
	Meshes.add("2x6_0Mesh",new Mesh("data/models/2x6_0.obj"));
	Meshes.add("2x6_1Mesh",new Mesh("data/models/2x6_1.obj"));
	Meshes.add("2x6_2Mesh",new Mesh("data/models/2x6_2.obj"));
	Meshes.add("2x6_3Mesh",new Mesh("data/models/2x6_3.obj"));
	Meshes.add("4x4_0AltMesh",new Mesh("data/models/4x4_0Alt.obj"));
	Meshes.add("4x4_0BaixMesh",new Mesh("data/models/4x4_0Baix.obj"));
	Meshes.add("4x4_0CentreMesh",new Mesh("data/models/4x4_0Centre.obj"));
	Meshes.add("4x4_1AltMesh",new Mesh("data/models/4x4_1Alt.obj"));
	Meshes.add("4x4_1BaixMesh",new Mesh("data/models/4x4_1Baix.obj"));
	Meshes.add("4x4_1CentreMesh",new Mesh("data/models/4x4_1Centre.obj"));
	Meshes.add("4x4_2AltMesh",new Mesh("data/models/4x4_2Alt.obj"));
	Meshes.add("4x4_2BaixMesh",new Mesh("data/models/4x4_2Baix.obj"));
	Meshes.add("4x4_2CentreMesh",new Mesh("data/models/4x4_2Centre.obj"));
	Meshes.add("4x4_3AltMesh",new Mesh("data/models/4x4_3Alt.obj"));
	Meshes.add("4x4_3BaixMesh",new Mesh("data/models/4x4_3Baix.obj"));
	Meshes.add("4x4_3CentreMesh",new Mesh("data/models/4x4_3Centre.obj"));
	Meshes.add("4x4_4Mesh",new Mesh("data/models/4x4_4.obj"));
	Meshes.add("ajuntament8x8Mesh",new Mesh("data/models/ajuntament8x8.obj"));
	Meshes.add("construccio8x8Mesh",new Mesh("data/models/construccio8x8.obj"));
	Meshes.add("hospital8x8Mesh",new Mesh("data/models/hospital8x8.obj"));

	//Character quad
	{
		std::vector<Vertex::Element> elements;
		elements.push_back(Vertex::Element(Vertex::Attribute::Position , Vertex::Element::Float, 3));
		elements.push_back(Vertex::Element(Vertex::Attribute::TexCoord , Vertex::Element::Float, 2));

		Vertex::Format format(elements);
		Mesh* charModel = new Mesh(format,0,Mesh::STATIC);

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
		Meshes.add("charMesh",charModel);
	}

	//Blood quad
	{
		std::vector<Vertex::Element> elements;
		elements.push_back(Vertex::Element(Vertex::Attribute::Position , Vertex::Element::Float, 3));
		elements.push_back(Vertex::Element(Vertex::Attribute::TexCoord , Vertex::Element::Float, 2));

		Vertex::Format format(elements);
		Mesh* bloodModel = new Mesh(format,0,Mesh::STATIC);

		struct Vertex {
				Vertex(vec3f pos, vec2f tex) : pos(pos) , tex(tex) {}
				vec3f pos;
				vec2f tex;
		};

		std::vector<Vertex> data;
		data.push_back(Vertex(vec3f(-1, 0, -1), vec2f(0.0, 1.0)));
		data.push_back(Vertex(vec3f(-1, 0,  1), vec2f(0.0, 0.0)));
		data.push_back(Vertex(vec3f( 1, 0, -1), vec2f(1.0, 1.0)));

		data.push_back(Vertex(vec3f( 1, 0,  1), vec2f(1.0, 0.0)));
		data.push_back(Vertex(vec3f( 1, 0, -1), vec2f(1.0, 1.0)));
		data.push_back(Vertex(vec3f(-1, 0,  1), vec2f(0.0, 0.0)));

		bloodModel->setVertexData(&data[0],data.size());
		Meshes.add("bloodMesh",bloodModel);
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
		VBE_LOG("FPS: " << fpsCount << ". Amount of GameObjects: " << getGame()->getObjectCount());
		debugCounter--;
		fpsCount = 0;
	}
}


