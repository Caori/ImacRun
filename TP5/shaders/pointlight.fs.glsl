#version 330

in vec3 vPosition_vs;
in vec3 vNormal_vs;

//infos sur le materiau de l'objet
uniform vec3 uKd; //couleur de l'objet (diffus)
uniform vec3 uKs; //couleur du reflet (spéculaire)
uniform float uShininess;
//infos sur la lumière
uniform vec3 uLightPos_vs;
uniform vec3 uLightIntensity;

out vec3 fFragColor;

float prodScal(vec3 vect1, vec3 vect2) {
  float prod = dot(normalize(vect1), normalize(vect2));
  if(prod <= 0) return 0;
  else return prod;
}

vec3 blinnPhong() {
  float distanceLight = distance(vPosition_vs, uLightPos_vs);
  vec3 wi = normalize(uLightPos_vs - vPosition_vs);
  vec3 w0 = normalize(-vPosition_vs);
  vec3 half = normalize((w0 + wi)/2);

  vec3 KD = uKd * prodScal(wi, vNormal_vs);
  vec3 KS = uKs * pow(prodScal(half, vNormal_vs), uShininess);

  vec3 color = (uLightIntensity/(distanceLight*distanceLight)) * (KD + KS);
  return color;
}

void main() {
    //fFragColor = normalize(vNormal_vs);
    fFragColor = blinnPhong();
}
