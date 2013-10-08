#version 420

uniform sampler2D tex;
uniform vec4 color;

in vec2 vTexCoord;

void main() {
	vec4 texcol = texture2D(tex, vTexCoord);
	float col = texcol.r;

	if(col < 0.5)
		gl_FragColor = color*col*2;
	else
		gl_FragColor = 1-(1-color)*(2-col*2);
	gl_FragColor.a = color.a*texcol.a;
}
