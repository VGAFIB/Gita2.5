#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Animation.hpp"

enum FaceDir {
	FACE_UP = 0, FACE_DOWN, FACE_LEFT, FACE_RIGHT, FACE_SIZE
};

class Map;
class Population;

class Character : public GameObject {
	public:
		Character();
		virtual ~Character();

		void move(vec2f posf);
		bool canSee(const vec2f& destPos);
		void update(float deltaTime);
		void draw() const;
		virtual vec2f moveCharacter(float deltaTime) = 0;
		vec2f getPosition() const { return position; }

		float getSeeRadius();

	protected:

		std::string currAnim;
		void setAnimation(std::string name);

		AnimationPlayer anim;
		std::string texName;
		std::string action;

		FaceDir faceDir;
		vec2f position;
		Map* map;
		Population* population;
		Model model;

		float vel;
		float deadrot;
		bool drawDead;
		void moveInDir(vec2f dir, float deltaTime);
};

#endif // CHARACTER_HPP
