#version 130

in vec3 vPosition_vs;
in vec3 vNormal_vs;

//infos sur le materiau de l'objet
uniform vec3 uKd; //couleur de l'objet (diffus)
uniform vec3 uKs; //couleur du reflet (spéculaire)
uniform float uShininess;
//infos sur la lumière
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

out vec3 fFragColor;

float prodScal(vec3 vect1, vec3 vect2) {
  float prod = dot(normalize(vect1), normalize(vect2));
  if(prod <= 0) return 0.0;
  else return prod;
}

vec3 blinnPhong() {
  vec3 wi = normalize(uLightDir_vs);
  vec3 w0 = normalize(-vPosition_vs);
  vec3 h = normalize((w0 + wi)/2);

  vec3 KD = uKd * prodScal(wi, vNormal_vs);
  vec3 KS = uKs * pow(prodScal(h, vNormal_vs), uShininess);

  vec3 color = uLightIntensity * (KD + KS);
  return color;
}

void main() {
    //fFragColor = normalize(vNormal_vs);
    fFragColor = blinnPhong();
}
