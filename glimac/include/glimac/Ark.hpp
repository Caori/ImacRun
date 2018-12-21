#pragma once

#include <iostream>
#include <stdlib.h>

#include "glm.hpp"
#include "common.hpp"
#include "FilePath.hpp"
#include "Object.hpp"
#include "Camera.hpp"
#include "Cube.hpp"
#include "glimac/Sphere.hpp"

namespace glimac {
/// \class Ark
/// \brief description...
  class Ark : public Object {
  public:
    /// \return Ark
    /// \param applicationPath: description...
    Ark(const FilePath& applicationPath);

    ~Ark() {}

    /// \return void
    /// \param x: description...
    /// \param y: description...
    /// \param camera: description...
    /// \brief Get the active camera's view matrix, build and send the matrixes
    /// to the shader, send the material data to the shader and draws a Ark.
    void draw(int i, int j, glm::mat4 &viewMatrix/*,Camera& camera*/, Cube& cube, Sphere& sphere, SDLWindowManager &window) const;
  };

}
