#version 420

uniform sampler2D sampler;

in vec4 vPos;
in vec3 vPos2;
in vec3 vNormal;
in vec2 vTexCoord;

void main() {
	vec3 lightDir = normalize(vec3(-1, -2, -2));
	float light = abs(dot(lightDir, vNormal));
	gl_FragColor = vec4(texture2D(sampler,vTexCoord).xyz*light,1.0);
}
