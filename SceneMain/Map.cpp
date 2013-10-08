#include "Map.hpp"
#include "SceneMain.hpp"
#include "House.hpp"

using namespace std;

struct Street {
		int pos;
		int sidewalk;
		int roadway;

		int start() { return pos; }
		int end() { return pos+sidewalk*2+roadway; }
		int sstart() { return pos+sidewalk; }
		int send() { return pos+sidewalk+roadway; }
		bool peatonal() { return roadway == 0; }

		static const int types[][2];
};

const int Street::types[][2] = {
	{2, 0},
	{1, 2},
	{1, 3},
	{2, 4},
};

vector<Street> generateStreets(int size) {
	int margin = 10;
	//generate
	vector<Street> v;
	for(int i = margin; i < size-margin; i++) {
		int t = Utils::randomInt(0, 3);
		Street s;
		s.pos = i;
		s.sidewalk = Street::types[t][0];
		s.roadway = Street::types[t][1];
		i += s.sidewalk*2+s.roadway;
		if(i < size-1)
			v.push_back(s);
		i += Utils::randomInt(5, 10);
	}
	//fix offset
	if(v.empty()) return v;
	int start = v[0].start();
	int end = v[v.size()-1].end()+1;
	for(unsigned int i = 0; i < v.size(); ++i)
		v[i].pos += (size - end - start)/2;

	return v;
}

typedef vec2b Apple;

Map::Map() {
	setName("map");
	Utils::seedRandom(time(0));
	setDrawPriority(-1);

	int sizex = 100;
	int sizey = 100;
	tiles = vector<vector<Tile> > (sizex, vector<Tile>(sizey));

	//Set everything to garden
	for(int y = 0; y < sizey; y++)
		for(int x = 0; x < sizex; x++)
			tile(x, y).type = Map::Garden;

	vector<Street> horitzStreets = generateStreets(sizey);
	vector<Street> verticStreets = generateStreets(sizex);
	vector<vector<Apple> > apples (verticStreets.size(), vector<Apple>(horitzStreets.size()));

	//randomly connect apples
	for(unsigned int x = 0; x < verticStreets.size(); x++)
		for(unsigned int y = 0; y < horitzStreets.size(); y++) {
			Apple& a = apples[x][y];
			if(x == 0)
				a.x = false; //cannot connect to the left on the leftmost intersection
			else
				a.x = Utils::randomBool(80);
			if(y == 0)
				a.y = false; //cannot connect up on the upmost intersection
			else
				a.y = Utils::randomBool(80);
		}

	//draw sidewalk on all the street
	for(unsigned int x = 0; x < verticStreets.size(); x++)
		for(unsigned int y = 0; y < horitzStreets.size(); y++) {
			Apple& a = apples[x][y];
			if(a.x) {
				int x1 = verticStreets[x-1].start();
				int x2 = verticStreets[x].end();
				int y1 = horitzStreets[y].start();
				int y2 = horitzStreets[y].end();
				for(int dx = x1; dx < x2; dx++)
					for(int dy = y1; dy < y2; dy++)
						tile(dx, dy).type = Map::Sidewalk;
			}
			if(a.y) {
				int x1 = verticStreets[x].start();
				int x2 = verticStreets[x].end();
				int y1 = horitzStreets[y-1].start();
				int y2 = horitzStreets[y].end();
				for(int dx = x1; dx < x2; dx++)
					for(int dy = y1; dy < y2; dy++)
						tile(dx, dy).type = Map::Sidewalk;
			}
		}

	//draw roadway on top of the center sidewalk
	for(unsigned int x = 0; x < verticStreets.size(); x++)
		for(unsigned int y = 0; y < horitzStreets.size(); y++) {
			Apple& a = apples[x][y];
			if(a.x) {
				int x1 = verticStreets[x-1].sstart();
				int x2 = verticStreets[x].send();
				int y1 = horitzStreets[y].sstart();
				int y2 = horitzStreets[y].send();
				for(int dx = x1; dx < x2; dx++)
					for(int dy = y1; dy < y2; dy++)
						tile(dx, dy).type = Map::Roadway;
			}
			if(a.y) {
				int x1 = verticStreets[x].sstart();
				int x2 = verticStreets[x].send();
				int y1 = horitzStreets[y-1].sstart();
				int y2 = horitzStreets[y].send();
				for(int dx = x1; dx < x2; dx++)
					for(int dy = y1; dy < y2; dy++)
						tile(dx, dy).type = Map::Roadway;
			}
		}

	//Put a water border around the map.
	for(int x = 0; x < getWidth(); x++) {
		tile(x, 0).type = Water;
		tile(x, getHeight()-1).type = Water;
	}
	for(int y = 0; y < getHeight(); y++) {
		tile(0, y).type = Water;
		tile(getWidth()-1, y).type = Water;
	}

	//Place Houses (first at random and then in order)
	int fails = 0;
	while((fails < 1000))
		fails = (placeHouse(Utils::randomInt(0, House::houseTypeCount-1))? 0 : fails+1);
	for(int y = 0; y < getHeight(); y++)
		for(int x = 0; x < getWidth(); x++)
			for(int i = 0; i < House::houseTypeCount; i++)
				if(Utils::randomBool(30))
					if(houseFitsAt(x, y, i))
						placeHouse(x, y, i);

	//Discard smaller connected components (biggest BFS wins)
	vector<vector<int> > visited(getWidth(), vector<int>(getHeight(), -1));
	int bestid = 0;
	int bestcount = 0;
	int dx[] = {0, 0, 1, -1};
	int dy[] = {1, -1, 0, 0};

	for(int x = 0; x < getWidth(); x++)
		for(int y = 0; y < getHeight(); y++)
			if(visited[x][y] == -1 && !tile(x, y).isSolid()) {
				int id = x+y*getWidth();
				int count = 0;
				queue<vec2i> q;
				q.push(vec2i(x, y));

				while(!q.empty()) {
					vec2i current = q.front();
					q.pop();
					visited[current.x][current.y] = id;
					count++;
					for(int i = 0; i < 4; i++) {
						vec2i next(current.x+dx[i],current.y+dy[i]);
						if(!tile(next).isSolid() && visited[next.x][next.y] == -1) {
							visited[next.x][next.y] = id;
							q.push(next);
						}
					}
				}
				if(count > bestcount) {
					bestcount = count;
					bestid = id;
				}
			}

	//set tiles disconnected from main component to building
	for(int x = 0; x < getWidth(); x++)
		for(int y = 0; y < getHeight(); y++)
			if(visited[x][y] != bestid && !tile(x, y).isSolid())
				tile(x, y).type = Unaccesible;

	//Generate the mesh
	vector<Vertex::Element> elements;
	elements.push_back(Vertex::Element(Vertex::Attribute::Position , Vertex::Element::Float, 3));
	elements.push_back(Vertex::Element(Vertex::Attribute::Color    , Vertex::Element::Float, 3));

	Vertex::Format format(elements);
	Mesh* mesh = new Mesh(format,0,false);

	struct Vertex {
			Vertex(vec3f pos, vec3f color) : pos(pos) , color(color) {}
			vec3f pos,color;
	};
	vector<Vertex> data;
	for(int y = 0; y < sizey; y++)
		for(int x = 0; x < sizex; x++) {
			if(tiles[x][y].type == Map::Building)
				continue;
			vec3f color;
			switch(tiles[x][y].type) {
				case Map::Sidewalk:
					color = vec3f(0.4, 0.4, 0.5);
					break;
				case Map::Roadway:
					color = vec3f(0.2, 0.3, 0.3);
					break;
				case Map::Water:
					color = vec3f(0.1, 0.3, 0.5);
					break;
				case Map::Unaccesible:
					color = vec3f(0.1, 0.2, 0.05);
					break;
				default:
					color = vec3f(0.3, 0.5, 0.1);
					if((x+y)%2 == 0)
						color = vec3f(0.2, 0.4, 0.1);
					break;
			}

			data.push_back(Vertex(vec3f(x, 0,  y), color));
			data.push_back(Vertex(vec3f(x, 0,  y+1), color));
			data.push_back(Vertex(vec3f(x+1, 0,  y), color));
			data.push_back(Vertex(vec3f(x, 0,  y+1), color));
			data.push_back(Vertex(vec3f(x+1, 0,  y+1), color));
			data.push_back(Vertex(vec3f(x+1, 0,  y), color));
		}

	mesh->setVertexData(&data[0],data.size());
	model.mesh = mesh;
	Meshes.add("map",mesh);
	model.program = Programs.get("map");
}

Map::~Map() {
}

bool Map::placeHouse(int type) {
	int sizeX = House::houseTypes[type].width;
	int sizeY = House::houseTypes[type].depth;

	int x = Utils::randomInt(0, getWidth()-sizeX);
	int y = Utils::randomInt(0, getHeight()-sizeY);

	if(houseFitsAt(x, y, type)) {
		placeHouse(x, y, type);
		return true;
	}
	return false;
}

void Map::placeHouse(int x, int y, int type) {
	int sizeX = House::houseTypes[type].width;
	int sizeY = House::houseTypes[type].depth;
	for(int dx = 0; dx < sizeX; dx++)
		for(int dy = 0; dy < sizeY; dy++)
			tile(x+dx, y+dy).type = Building;
	House* h = new House(x, y, type);
	h->addTo(this);
}

bool Map::houseFitsAt(int x, int y, int type) {
	int sizeX = House::houseTypes[type].width;
	int sizeY = House::houseTypes[type].depth;

	if(x+sizeX > getWidth()) return false;
	if(y+sizeY > getHeight()) return false;

	for(int dx = 0; dx < sizeX; dx++)
		for(int dy = 0; dy < sizeY; dy++)
			if(tile(x+dx, y+dy).type != Garden)
				return false;
	return true;
}

void Map::draw() const {
	model.program->uniform("modelViewProjectionMatrix")->set(fullTransform);
	model.draw();
}

const Map::Tile& Map::tile(int x, int y) const {
	assert(validTile(x, y));
	return tiles[x][y];
}

Map::Tile& Map::tile(int x, int y) {
	assert(validTile(x, y));
	return tiles[x][y];
}

vec2i Map::getRandomStreet() const {
	bool repeat = true;
	vec2i pos(0);
	while(repeat) {
		pos.x = Utils::randomInt(0, getWidth()-1);
		pos.y = Utils::randomInt(0, getHeight()-1);
		repeat = tile(pos).isSolid();
	}
	return pos;
}

bool Map::lineOfSight(vec2f from, vec2f to) const {
	//Dice si una persona en FROM ve a una persona en TO
	bool fromGrass = tile(from).isGrass();
	bool toGrass = tile(to).isGrass();

	//Desde fuera no se puede ver dentro..
	if(!fromGrass && toGrass) return false;
	float d = glm::distance(from, to);
	if(fromGrass && toGrass && d > 0.8) return false;
	if(d > 12) return false;

	for(float i = 0; i <= 1; i+=0.05) {
		vec2f midway = from*i + to*(1.0f-i);
		//Si los dos dentro, ha de ser todo grass.
		if(fromGrass && !tile(midway).isGrass())
			return false;
		if(tile(midway).isSolid())
			return false;
	}
	return true;
}
