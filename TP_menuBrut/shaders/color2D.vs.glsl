#version 330 core
#define M_PI 3.1415926535897932384626433832795

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vFragColor;
out vec2 vPosition;




mat3 translate(float x,float y){
  return mat3(vec3(1,0,0),vec3(0,1,0),vec3(x,y,1));
}

mat3 scale(float x,float y){
  return mat3(vec3(x,0,0),vec3(0,y,0),vec3(0,0,1));
}

mat3 rotate(float a){
  return mat3(vec3(cos((a*M_PI)/180),sin((a*M_PI)/180),0),vec3(-sin((a*M_PI)/180),cos((a*M_PI)/180),0),vec3(0,0,1));
}

void main() {

  vPosition = aVertexPosition;
  vFragColor = aVertexColor;
  gl_Position = vec4((vec3(aVertexPosition, 1)).xy, 0, 1);


};