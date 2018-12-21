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
#include <string>

namespace glimac {
/// \class Coin
/// \brief description...
class Character : public Object {
    public:
      float _x,_y,_z;
      float _xGrid, _zGrid;
      float _scale;
      /// \return Coin
      int _score;
      int _jump; //ceci est un booléen
      bool _isFalling;
      bool _isCrouched;


      /// \param applicationPath: description...
      Character(const FilePath& applicationPath, float demiLargeur, float y=0, float z=0., float _scale=1.);

      ~Character() {}

      /// \return void
      /// \param i: description...
      /// \param j: description...
      /// \param camera: description...
      /// \brief Get the active camera's view matrix, build and send the matrixes
      /// to the shader, send the material data to the shader and draws a Coin.
      void draw(int i, int j, glm::mat4 &viewMatrix, /*,Camera& camera*/Cube& cube, Sphere& sphere, SDLWindowManager &window) const;
      void move(std::vector< std::vector< std::vector<int>>> &grid, float speed, std::string &position);
      //int moveFront : renvoie 0 si on est au bout de la map
      int moveFront(std::vector< std::vector< std::vector<int>>> &grid, float speed, std::string &position);
      void jump(const std::vector< std::vector< std::vector<int>>> &grid);
      void moveLeft(std::vector< std::vector< std::vector<int>>> &grid, int &posX, int &posZ, std::string &position);
      void moveRight(std::vector< std::vector< std::vector<int>>> &grid, int &posX, int &posZ, std::string &position);
      void fallTest(const std::vector< std::vector< std::vector<int>>> &grid);
};

}