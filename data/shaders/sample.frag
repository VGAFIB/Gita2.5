#version 420

uniform sampler2D sampler;

in vec4 vPos;
in vec3 vPos2;
in vec3 vNormal;
in vec2 vTexCoord;

void main() {
	vec3 lightDir = normalize(vec3(-1, -2, -2));
	float light = abs(dot(lightDir, vNormal));
	float yy = vPos2.y;
	light *= 1-exp(-yy*0.3)+0.4;

	float alpha = max(0.5, 1-exp(-length(vPos.xy)*0.6));
	if(vNormal.y < 0.5) alpha = 1;
	vec4 lightFactor = vec4(light, light, light, alpha);
	gl_FragColor = vec4(texture2D(sampler,vTexCoord).xyz,1.0)*lightFactor;
}
