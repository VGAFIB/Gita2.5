#version 420

uniform sampler2D tex;
in vec2 vTexCoord;
uniform float alpha;

void main() {
    gl_FragColor = texture2D(tex, vTexCoord) * vec4(1.0, 1.0, 1.0, alpha);
}
