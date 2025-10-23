#version 330
out vec4 fragcolor;
in vec4 color;

void main() {
	fragcolor = vec4(color.x, color.y, color.z, color.w);
}