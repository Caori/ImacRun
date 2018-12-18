#version 130

//attributs de sommet
/*layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoords;*/

in vec3 aVertexPosition;
in vec3 aVertexNormal;
in vec2 aVertexTexCoords;

//matrices de transformation reçues en uniform
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

//sorties du vertex shader
out vec3 vPosition_vs;
out vec3 vNormal_vs;
out vec2 vTexCoords;

void main() {

    //passage en coordonnées homogènes
    vec4 vertexPosition = vec4(aVertexPosition, 1);
    vec4 vertexNormal = vec4(aVertexNormal, 0);

    //calcul des valeurs de sortie
      vPosition_vs = vec3(uMVMatrix * vertexPosition);
      vNormal_vs = vec3(uNormalMatrix * vertexNormal);
      vTexCoords = aVertexTexCoords;

    //calcul de la position projetée
    gl_Position = uMVPMatrix * vertexPosition;
}
