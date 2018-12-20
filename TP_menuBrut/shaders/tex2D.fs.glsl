#version 130

in vec2 vCoordTexture;
out vec4 fFragColor;

uniform vec3 uColor;
uniform sampler2D uTexture;

void main() {
	
	vec4 dataColor = texture(uTexture, vCoordTexture);

	//fFragColor.r = dataColor.x;
	//fFragColor.g = dataColor.y;
	//fFragColor.b = dataColor.z;

	fFragColor = dataColor;
};
