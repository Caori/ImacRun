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
/// \class Coin
/// \brief description...
class Personnage : public Object {
    public:
      float _x,_y,_z;
      /// \return Coin
      /// \param applicationPath: description...
      Personnage(const FilePath& applicationPath, float largeur);

      ~Personnage() {}

      void moveFront(const float d){
            _z+=d;
            std::cout<<int(_x)<<" , "<<int(_z)<<std::endl;
      }
      /// \return void
      /// \param i: description...
      /// \param j: description...
      /// \param camera: description...
      /// \brief Get the active camera's view matrix, build and send the matrixes
      /// to the shader, send the material data to the shader and draws a Coin.
      void draw(int i, int j, glm::mat4 &viewMatrix, glm::mat4 &rotationMatrix, /*,Camera& camera*/Cube& cube, Sphere& sphere) const;
      void move();
};

}
