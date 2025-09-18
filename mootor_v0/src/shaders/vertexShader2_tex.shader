#version 330

layout(location = 0) in vec3 pCords;
layout(location = 1) in vec2 texCords;

out vec2 texcords;

uniform mat4 projectionMat;

void main() {
	gl_Position = projectionMat * vec4(pCords, 1.0);
	texcords = texCords;
}