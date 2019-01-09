#include <cmath>
#include <vector>
#include <iostream>
#include <math.h>
#include "glimac/common.hpp"
#include "glimac/FreeflyCamera.hpp"

namespace glimac {

  FreeflyCamera::FreeflyCamera()
    : m_Position(glm::vec3(0, 0, 0)), m_fPhi(M_PI), m_fTheta(0) {
      computeDirectionVectors();
  }

  void FreeflyCamera::computeDirectionVectors() {
    m_FrontVector = glm::vec3(cos(glm::radians(m_fTheta))*sin(glm::radians(m_fPhi)),
      sin(glm::radians(m_fTheta)),
      cos(glm::radians(m_fTheta))*cos(glm::radians(m_fPhi)));
    m_LeftVector = glm::vec3(sin(glm::radians(m_fPhi) + M_PI/2), 0,
      cos(glm::radians(m_fPhi) + M_PI/2));
    m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
  }

  void FreeflyCamera::moveLeft(float t) {
    m_Position += t*m_LeftVector;
  }

  void FreeflyCamera::moveFront(float t) {
    m_Position += t*m_FrontVector;
  }

  void FreeflyCamera::rotateLeft(float degrees) {
    m_fPhi += glm::radians(degrees);
    computeDirectionVectors();
  }

  void FreeflyCamera::rotateUp(float degrees) {
    m_fTheta += glm::radians(degrees);
    computeDirectionVectors();
  }

  glm::mat4 FreeflyCamera::getViewMatrix() const {
    glm::mat4 ViewMatrix = glm::lookAt(m_Position, m_Position+m_FrontVector, m_UpVector);

    return ViewMatrix;
  }
}
