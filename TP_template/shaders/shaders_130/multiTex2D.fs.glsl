#version 130

in vec2 vCoordTexture;
out vec4 fFragColor;

uniform vec3 uColor;
uniform sampler2D uTexture1;
uniform sampler2D uTexture2;

void main() {
	
	vec4 dataColor1 = texture(uTexture1, vCoordTexture);
	vec4 dataColor2 = texture(uTexture2, vCoordTexture);

	//fFragColor.r = dataColor.x;
	//fFragColor.g = dataColor.y;
	//fFragColor.b = dataColor.z;

	fFragColor = dataColor1 + dataColor2;
};
