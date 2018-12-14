#pragma once //fait que le compilateur le compile qu'une fois

#include "glm.hpp"

namespace glimac {

  class FreeflyCamera {

  private:
    glm::vec3 m_Position; //position de la caméra
    float m_fPhi; //coord spherique x du vecteur F
    float m_fTheta; //coord spherique y du vecteur F
    glm::vec3 m_FrontVector; //vecteur F
    glm::vec3 m_LeftVector; //vecteur L
    glm::vec3 m_UpVector; //vecteur U

    void computeDirectionVectors();

  public:
    FreeflyCamera();
    ~FreeflyCamera() {}

    void moveLeft(float t);

    void moveFront(float t);

    void rotateLeft(float degrees);

    void rotateUp(float degrees);

    glm::mat4 getViewMatrix() const;
  };

}
