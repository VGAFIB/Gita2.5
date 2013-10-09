#include "CharacterMark.hpp"

CharacterMark::CharacterMark(vec4f color) : color(color), sign(INTERROGATION), visible(true){
	model.mesh = Meshes.get("charMesh");
	model.program = Programs.get("markProgram");
}

CharacterMark::~CharacterMark() {
}

void CharacterMark::update(float deltaTime) {
	transform = glm::translate(mat4f(1.0),vec3f(0,0.75,0));
	transform = glm::scale(transform,vec3f(0.5,0.5,0));
}

void CharacterMark::draw() const {
	if(!visible) return;
	model.program->uniform("modelViewProjectionMatrix")->set(fullTransform);
	model.program->uniform("color")->set(color);
	model.program->uniform("tex")->set(Textures.get("excTex"));
	switch(sign) {
		case INTERROGATION:
			model.program->uniform("texBounds")->set(vec4f(0,0,1,0.5));//upper half
			break;
		case EXCLAMATION:
			model.program->uniform("texBounds")->set(vec4f(0,0.5,1,0.5));//lower half
			break;
	}
	model.draw();
}
