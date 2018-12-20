#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/TrackballCamera.hpp"

namespace glimac {

  TrackballCamera::TrackballCamera()
    : m_fDistance(5), m_fLeftDistance(0), m_fAngleX(0), m_fAngleY(0) {}

  void TrackballCamera::moveFront(float delta) {
    m_fDistance += delta;
  }

  void TrackballCamera::moveLeft(float delta) {
    m_fLeftDistance += delta;
  }

  void TrackballCamera::rotateLeft(float degrees) {
    m_fAngleY += degrees;
  }

  void TrackballCamera::rotateUp(float degrees) {
    m_fAngleX += degrees;
  }

  glm::mat4 TrackballCamera::getViewMatrix() const {
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.f),
      glm::vec3(-m_fLeftDistance, 0, -m_fDistance));
    glm::mat4 rotationXMatrix = glm::rotate(glm::mat4(1.f),
      glm::radians(m_fAngleX), glm::vec3(1, 0, 0));
    glm::mat4 rotationYMatrix = glm::rotate(glm::mat4(1.f),
      glm::radians(m_fAngleY), glm::vec3(0, 1, 0));

    glm::mat4 ViewMatrix = translationMatrix*rotationXMatrix*rotationYMatrix;

    return ViewMatrix;
  }
}
