#pragma once

#include <iostream>
#include <stdlib.h>

#include "glm.hpp"
#include "common.hpp"
#include "FilePath.hpp"
#include "Object.hpp"
//#include "Camera.hpp"
#include "Cube.hpp"
#include "glimac/Sphere.hpp"

namespace glimac {
/// \class Ground
/// \brief description...
class Ground : public Object {
    public:
        /// \return Ground
        /// \param applicationPath: description...
        Ground(const FilePath& applicationPath);

        ~Ground(){}

        /// \return void
        /// \param x: description...
        /// \param y: description...
        /// \param camera: description...
        /// \brief Get the active camera's view matrix, build and send the matrixes
        /// to the shader, send the material data to the shader and draws a Ground.
        void draw(int i, int j, glm::mat4 &viewMatrix, glm::mat4 &rotationMatrix, /*,Camera& camera*/ Cube& cube, Sphere& sphere) const;

};

}
