#ifndef CHARACTERMARK_HPP
#define CHARACTERMARK_HPP
#include "Commons.hpp"

class CharacterMark : public GameObject {
	public:
		enum Sign {
			INTERROGATION = 0,
			EXCLAMATION
		};

		CharacterMark(vec4f color = vec4f(1,0,1,1));
		~CharacterMark();

		void update(float deltaTime);
		void draw() const;

		vec4f color;
		Sign sign;
		bool visible;
	private:
		Model model;
};

#endif // CHARACTERMARK_HPP
