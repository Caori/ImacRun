#version 330 core

in vec3 vFragPosition;
in vec3 vFragNormal;
in vec2 vFragTexture;

out vec3 fFragColor;

uniform vec3 uColor;
uniform sampler2D uTexture;

void main() {
  fFragColor = vec3(texture(uTexture, vFragTexture).xyz);
};
