#version 130

// Entrée
in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fFragColor;

void main(){
	// normalisation de vNormale
	vec3 vNormalize = normalize(vNormal_vs);

	// calcul de la couleur
	fFragColor.r = vNormalize.x;
	fFragColor.g = vNormalize.y;
	fFragColor.b = vNormalize.z;
}