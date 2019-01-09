#version 330
#define M_PI 3.1415926535897932384626433832795


layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aTexCoord;

out vec2 vCoordTexture;
out vec2 vPosition;

uniform mat3 uModelMatrix;

mat3 rotate(float a){
  return mat3(vec3(cos((a*M_PI)/180),sin((a*M_PI)/180),0),vec3(-sin((a*M_PI)/180),cos((a*M_PI)/180),0),vec3(0,0,1));
}

void main() {

  vPosition = aVertexPosition;
  gl_Position = vec4((uModelMatrix*vec3(aVertexPosition, 1)).xy, 0, 1);
  vCoordTexture = aTexCoord;

};
