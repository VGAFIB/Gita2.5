#include "Police.hpp"
#include "SceneMain.hpp"
#include "Person.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Population.hpp"

Police::Police() : Npc() {
	mark->color = vec4f(1,0,0,1);
	mark->visible = false;
	vel = 2.0f;
	state = PATROL;
	anim.setAnimData(Animations.get("poli"));
	texName = "policeTex";
	position = vec2f(map->getRandomStreet())+0.5f;
}

vec2f Police::moveCharacter(float deltaTime) {
	(void) deltaTime;
	return vec2f(0, 0);
}
