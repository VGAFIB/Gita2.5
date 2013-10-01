#version 420

uniform mat4 modelViewProjectionMatrix;
uniform vec4 texBounds;

in vec3 a_position;
in vec2 a_texCoord;

out vec2 vTexCoord;

void main () {
    gl_Position = modelViewProjectionMatrix * vec4(a_position,1.0);
    vTexCoord = texBounds.xy + texBounds.zw*a_texCoord;
}
