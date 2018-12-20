#pragma once //fait que le compilateur le compile qu'une fois

#include "glm.hpp"

namespace glimac {

  class TrackballCamera {

  private:
    float m_fDistance; //distance par rapport au centre de la scène
    float m_fLeftDistance;
    float m_fAngleX; //angle fait par la caméra autour de l'axe x (haut bas)
    float m_fAngleY; //angle fait par caméra autour de l'axe y (gauche droite)

  public:
    TrackballCamera();
    ~TrackballCamera() {}

    void moveFront(float delta);
    void moveLeft(float delta);

    void rotateLeft(float degrees);

    void rotateUp(float degrees);

    glm::mat4 getViewMatrix() const;
  };

}
