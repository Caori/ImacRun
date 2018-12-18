#pragma once

#include <iostream>
#include <stdlib.h>

namespace glimac {

  class Camera {
  public:
    virtual ~Camera() {}

    virtual void rotateLeft(float degrees) = 0;

    virtual void rotateUp(float degrees) = 0;

    virtual glm::mat4 getViewMatrix() const = 0;
  };
}
