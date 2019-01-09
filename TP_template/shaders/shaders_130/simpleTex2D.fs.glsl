#version 130

in vec2 vCoordTexture;
out vec4 fFragColor;

uniform vec3 uColor;
uniform sampler2D uTexture1;

void main() {
	
	vec4 dataColor1 = texture(uTexture1, vCoordTexture);

	fFragColor = dataColor1;
};
