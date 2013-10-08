#ifndef NPC_HPP
#define NPC_HPP
#include "Character.hpp"
#include "CharacterMark.hpp"

class Npc : public Character {
	public:
		Npc();

	protected:
		CharacterMark* mark;

		void setGoal(vec2f goal);
		vec2f dirTowardsGoal();

		std::queue<vec2f> path;
		vec2f goal;
		bool hasGoal;

};

#endif // NPC_HPP
