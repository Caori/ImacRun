#version 330 core

in vec3 vFragColor;
out vec3 fFragColor;

in vec2 vPosition;




void main() {
	float alpha = 0.5;
  	float beta = 40;
  	float distance = distance(vPosition,vPosition);
  	/*sqrt((vFragCoord.x)*(vFragCoord.x)+(vFragCoord.y)*(vFragCoord.y));*/
  	float a = alpha*exp(-beta*distance*distance);
  	
  	fFragColor = vFragColor*a;
  
};