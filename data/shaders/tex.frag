#version 420

uniform sampler2D tex;
in vec2 vTexCoord;

void main() {
	gl_FragColor = texture2D(tex, vTexCoord);
}
