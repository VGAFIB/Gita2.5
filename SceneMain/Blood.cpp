#include "Blood.hpp"

Blood::Blood(vec2f pos): pos(pos), life(0.0f) {
	model.mesh = Meshes.get("bloodModel");
	model.program = Programs.get("tex");

}

Blood::~Blood() {

}

void Blood::update(float deltaTime)
{
	life += deltaTime;
	if(life > 10.0f)
		removeAndDelete();

	transform = glm::translate(mat4f(1.0f), vec3f(pos.x, 0.005, pos.y));
}

void Blood::draw() const {
	glDepthMask(GL_FALSE);
	model.program->uniform("alpha")->set(1.0f - life*0.1f);
	model.program->uniform("texBounds")->set(vec4f(0, 0, 1, 1));
	mat4f t = fullTransform;
	t = glm::scale(t, vec3f(glm::min(life, 1.0f)));
	model.program->uniform("modelViewProjectionMatrix")->set(t);
	model.program->uniform("tex")->set(Textures.get("blood1"));
	model.draw();
	glDepthMask(GL_TRUE);
}
