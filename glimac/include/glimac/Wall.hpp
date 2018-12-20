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
/// \class Ground
/// \brief description...
class Wall : public Object {
    public:
        /// \return Ground
        /// \param applicationPath: description...
        Wall(const FilePath& applicationPath);

        ~Wall() {}

        /// \return void
        /// \param i: description...
        /// \param j: description...
        /// \param camera: description...
        /// \brief Get the active camera's view matrix, build and send the matrixes
        /// to the shader, send the material data to the shader and draws a Ground.
        void draw(int i, int j, glm::mat4 &viewMatrix, /*,Camera& camera*/Cube& cube, Sphere& sphere) const;
};

}
