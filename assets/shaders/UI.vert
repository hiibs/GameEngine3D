#version 330 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_texCoord;

uniform mat4 MP;

out vec2 texCoord;

void main() {
	texCoord = in_texCoord;
	gl_Position = MP * vec4(in_position.x, in_position.y, in_position.z, 1.0);
}