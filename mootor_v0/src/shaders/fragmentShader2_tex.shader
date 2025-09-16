#version 330

out vec4 color;

in vec2 texcords;

uniform sampler2D xtexture;

void main() {
	color = texture(xtexture, texcords);
}