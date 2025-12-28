#version 330

layout(location = 0) in vec3 pCords;
layout(location = 1) in vec2 texCords;

out vec2 texcords;

uniform mat4 projectionMat;

void main() {
	if (gl_VertexID == 0 && gl_InstanceID == 0) {
        printf("Vertex 0 pos: %.1f, %.1f, %.1f\n", pCords.x, pCords.y, pCords.z);
        printf("Vertex 0 tex: %.1f, %.1f\n", texCords.x, texCords.y);
    }

	gl_Position = projectionMat * vec4(pCords, 1.0);
	texcords = texCords;
}