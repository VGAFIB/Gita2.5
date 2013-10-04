#ifndef MAP_HPP
#define MAP_HPP

#include "Commons.hpp"

class Map : public GameObject {
	public:
		enum TileType {
			Roadway,
			Sidewalk,
			Crosswalk,
			Garden,
			Building,
			Fence,
			Grass,
			Water,
			Unaccesible
		};

		struct Tile {
				TileType type;
				bool isSolid() const {
					return (type == Building || type == Fence || type == Water || type == Unaccesible);
				}
				bool isGrass() const {
					return (type == Grass);
				}
		};

		Map();
		virtual ~Map();

		virtual void draw() const;

		int getWidth() const {return tiles.size();}
		int getHeight() const {return tiles[0].size();}

		const Tile& tile(int x, int y) const;
		Tile& tile(int x, int y);
		const Tile& tile(vec2f p) const { return tile(p.x, p.y); }
		Tile& tile(vec2f p) { return tile(p.x, p.y); }
		const Tile& tile(vec2i p) const { return tile(p.x, p.y); }
		Tile& tile(vec2i p) { return tile(p.x, p.y); }
		inline bool validTile(int x, int y) const {return x >= 0 && x < getWidth() && y >= 0 && y < getHeight();}
		inline bool validTile(vec2i p) const {return validTile(p.x, p.y);}

		bool solid(int x, int y) const {return tile(x, y).isSolid(); }
		bool lineOfSight(vec2f from, vec2f to) const;

		vec2i getRandomStreet() const;
	private:
		void placeHouses();
		bool placeHouse(int type);
		void placeHouse(int x, int y, int type);
		bool houseFitsAt(int x, int y, int type);
		std::vector<std::vector<Tile> > tiles;
		Model model;
};


#endif // MAP_HPP
