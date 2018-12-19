#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <iostream>

#include "glimac/common.hpp"
#include "glimac/Obstacle.hpp"
#include "glimac/Cube.hpp"
#include "glimac/Sphere.hpp"
//#include "Texture.hpp"

namespace glimac {

Obstacle::Obstacle(const FilePath& applicationPath)
    :Object(applicationPath){
  }

void Obstacle::draw(int i, int j, glm::mat4 &viewMatrix, glm::mat4 &rotationMatrix, Cube& cube, Sphere& sphere) const {

}

}
