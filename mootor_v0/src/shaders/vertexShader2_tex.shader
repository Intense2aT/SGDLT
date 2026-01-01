#version 330

layout(location = 0) in vec3 pCords;
layout(location = 1) in vec2 texCords;
layout(location = 2) in float texType;

out vec2 texcords;
out float textype;

uniform mat4 projectionMat;
uniform mat4 viewMat;

void main() {
	gl_Position = projectionMat * viewMat * vec4(pCords, 1.0);
	texcords = texCords;
	textype = texType;
}