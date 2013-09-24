#include "Map.hpp"
#include "SceneMain.hpp"
#include "Game.hpp"
#include <cmath>
#include "House.hpp"
#include <queue>

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
};

const int streetTypes[][2] = {
	{2, 0},
	{1, 2},
	{1, 3},
	{2, 4},
};

vector<Street> generateStreets(int size) {
	int margin = 20;
	//generate
	vector<Street> v;
	for(int i = margin; i < size-margin; i++) {
		int t = Utils::randomInt(0, 3);
		Street s;
		s.pos = i;
		s.sidewalk = streetTypes[t][0];
		s.roadway = streetTypes[t][1];
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

	int sizex = 300;
	int sizey = 200;
	tiles = vector<vector<Tile> > (sizex, vector<Tile>(sizey));

	vector<Street> sx = generateStreets(sizey);
	vector<Street> sy = generateStreets(sizex);

	//Generate the map
	for(int y = 0; y < sizey; y++)
		for(int x = 0; x < sizex; x++)
			tile(x, y).type = Map::Garden;

	vector<vector<Apple> > apples (sy.size(), vector<Apple>(sx.size()));
	for(unsigned int x = 0; x < sy.size(); x++)
		for(unsigned int y = 0; y < sx.size(); y++) {
			Apple& a = apples[x][y];
			if(x == 0)
				a.x = false;
			else
				a.x = Utils::randomBool(80);
			if(y == 0)
				a.y = false;
			else
				a.y = Utils::randomBool(80);
		}

	for(unsigned int x = 0; x < sy.size(); x++)
		for(unsigned int y = 0; y < sx.size(); y++) {
			Apple& a = apples[x][y];
			if(a.x) {
				int x1 = sy[x-1].start();
				int x2 = sy[x].end();
				int y1 = sx[y].start();
				int y2 = sx[y].end();
				for(int xx = x1; xx < x2; xx++)
					for(int yy = y1; yy < y2; yy++)
						tile(xx, yy).type = Map::Sidewalk;
			}
			if(a.y) {
				int y1 = sx[y-1].start();
				int y2 = sx[y].end();
				int x1 = sy[x].start();
				int x2 = sy[x].end();
				for(int xx = x1; xx < x2; xx++)
					for(int yy = y1; yy < y2; yy++)
						tile(xx, yy).type = Map::Sidewalk;
			}
		}

	for(unsigned int x = 0; x < sy.size(); x++)
		for(unsigned int y = 0; y < sx.size(); y++) {
			Apple& a = apples[x][y];
			if(a.x) {
				int x1 = sy[x-1].sstart();
				int x2 = sy[x].send();
				int y1 = sx[y].sstart();
				int y2 = sx[y].send();
				for(int xx = x1; xx < x2; xx++)
					for(int yy = y1; yy < y2; yy++)
						tile(xx, yy).type = Map::Roadway;
			}
			if(a.y) {
				int y1 = sx[y-1].sstart();
				int y2 = sx[y].send();
				int x1 = sy[x].sstart();
				int x2 = sy[x].send();
				for(int xx = x1; xx < x2; xx++)
					for(int yy = y1; yy < y2; yy++)
						tile(xx, yy).type = Map::Roadway;
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

	placeHouses();

	//Discard smaller connected components
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

	for(int x = 0; x < getWidth(); x++)
		for(int y = 0; y < getHeight(); y++)
			if(visited[x][y] != bestid && !tile(x, y).isSolid())
				tile(x, y).type = Building;

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
	MeshManager::add("map",mesh);
	model.program = ShaderManager::get("sample2");
}

Map::~Map() {
}

const static int houseSizes[][2] = {
	{8, 8},
	{4, 4},
	{5, 3},
	{2, 6},
	{6, 2}
};
const static int typeCount = 5;

void Map::placeHouses() {
	for(int i = 0; i < typeCount; i++)
	{
		int max = 10000/houseSizes[i][0];
		int fails = 0;
		int placed = 0;
		while((fails < 100) && placed < max) { //Parar cuando hayan 10 fallos seguidos.
			if(placeHouse(i)) {
				fails = 0;
				++placed;
			}
			else
				fails++;
		}
	}
	for(int y = 0; y < getHeight(); y++)
		for(int x = 0; x < getWidth(); x++)
			for(int i = 0; i < typeCount; i++)
				if(Utils::randomBool(30))
					if(houseFitsAt(x, y, i))
						placeHouse(x, y, i);
}

bool Map::placeHouse(int type) {
	int tx = houseSizes[type][0];
	int ty = houseSizes[type][1];

	int x = Utils::randomInt(0, getWidth()-tx);
	int y = Utils::randomInt(0, getHeight()-ty);

	bool fit = houseFitsAt(x, y, type);

	if(fit)
		placeHouse(x, y, type);

	return fit;
}

bool Map::houseFitsAt(int x, int y, int type) {
	int tx = houseSizes[type][0];
	int ty = houseSizes[type][1];

	if(x+tx > getWidth()) return false;
	if(y+ty > getHeight()) return false;

	for(int xx = 0; xx < tx; xx++)
		for(int yy = 0; yy < ty; yy++)
			if(tile(x+xx, y+yy).type != Garden)
				return false;

	return true;
}

void Map::placeHouse(int x, int y, int type) {
	int tx = houseSizes[type][0];
	int ty = houseSizes[type][1];

	for(int xx = 0; xx < tx; xx++)
		for(int yy = 0; yy < ty; yy++)
			tile(x+xx, y+yy).type = Building;

	addObject(new House(x, y, tx, ty));
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
	int x, y;
	while(repeat) {
		x = Utils::randomInt(0, getWidth()-1);
		y = Utils::randomInt(0, getHeight()-1);
		repeat = tile(x, y).isSolid();
	}
	return vec2i(x, y);
}

bool Map::lineOfSight(vec2f from, vec2f to) const {
	//Dice si una persona en FROM ve a una persona en TO
	bool fromGrass = tile(from).isGrass(); //getTileAt(from) == 11;
	bool toGrass = tile(to).isGrass(); //getTileAt(to) == 11;

	//Desde fuera no se puede ver dentro..
	if(!fromGrass && toGrass) return false;
	float d = glm::distance(from, to);
	if(fromGrass && toGrass && d > 0.8) return false;
	if(d > 12) return false;

	for(float i = 0; i <= 1; i+=0.05)
	{
		vec2f pt = from*i + to*(1.0f-i);
		//Si los dos dentro, ha de ser todo grass.
		if(fromGrass && !tile(pt).isGrass())
			return false;
		if(tile(pt).isSolid())
			return false;
	}
	return true;
}
