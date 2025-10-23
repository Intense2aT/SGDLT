#version 330

layout(location = 0) in vec3 pCords;

uniform vec4 colors;

out vec4 color;

uniform mat4 projectionMat;

void main() {
	gl_Position = projectionMat * vec4(pCords, 1.0);
	color = colors;
}