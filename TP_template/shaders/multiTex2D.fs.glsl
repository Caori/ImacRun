#version 330

in vec2 vCoordTexture;
out vec4 fFragColor;

uniform vec3 uColor;
uniform sampler2D uTexture1;
uniform sampler2D uTexture2;
uniform sampler2D uTexture3;

void main() {
	
	vec4 dataColor1 = texture(uTexture1, vCoordTexture);
	vec4 dataColor2 = texture(uTexture2, vCoordTexture);
	vec4 dataColor3 = texture(uTexture3, vCoordTexture);

	fFragColor = dataColor1 + dataColor2 + dataColor3;
};
