#version 330

layout(location = 0) in vec3 pCords;

out vec3 colors;

void main() {
	gl_Position = vec4(pCords, 1.0);
}