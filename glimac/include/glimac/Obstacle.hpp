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
/// \class Obstacle
/// \brief description...
class Obstacle : public Object {
    public:
        /// \return Obstacle
        /// \param applicationPath: description...
        Obstacle(const FilePath& applicationPath);

        ~Obstacle() {}

        /// \return void
        /// \param x: description...
        /// \param y: description...
        /// \param camera: description...
        /// \brief Get the active camera's view matrix, build and send the matrixes
        /// to the shader, send the material data to the shader and draws a Obstacle.
         void draw(int i, int j, glm::mat4 &viewMatrix, Cube& cube, Sphere& sphere) const;
};

}
