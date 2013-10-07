#ifndef BLOOD_HPP
#define BLOOD_HPP

#include "Commons.hpp"

class Blood : public GameObject
{
	public:
		Blood(vec2f pos);
		virtual ~Blood();
		void update(float deltaTime);
		void draw() const;

	private:
		vec2f pos;
		Model model;
		float life;
};

#endif // BLOOD_HPP
