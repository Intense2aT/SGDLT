#version 330

out vec4 color;

in vec2 texcords;
in float textype;

uniform ivec2 texmapdims; // 2, 1
uniform sampler2D xtexture;

void main() {
	vec2 truecords = vec2(0.0, texcords.y);
	int texindex = int(textype); //1

	float x = 1.0 / float(texmapdims[0]); // 0.5
	float y = 1.0 / float(texmapdims.y); // 1

	int x2 = ((texindex - 1) % texmapdims.x) + 1; // 0 + 1 = 1
	int y2 = int(texindex / texmapdims.x); // int(1 / 2) = 0

	truecords.x = (x2 + texcords.x - 1) * x;
	truecords.y = (y2 + texcords.y) * y; 

	color = texture(xtexture, truecords);
}