#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <GL/glew.h>

#include "glimac/common.hpp"
//#include "glm.hpp"
#include "glimac/Light.hpp"
#include "glimac/DirectionalLight.hpp"

namespace glimac {

  DirectionalLight::DirectionalLight(const FilePath& applicationPath)
      : Light(applicationPath) {
    uLightDir_vs = glGetUniformLocation(_Program.getGLId(), "uLightDir_vs");
  }

  void DirectionalLight::drawLight(glm::mat4 &viewMatrix, glm::vec4 direction) const {
    glm::vec4 directLight = viewMatrix * direction;

    glUniform3f(uLightDir_vs, directLight.x,
      directLight.y, directLight.z);
    glUniform3f(uLightIntensity, 1.2f, 1.2f, 1.2f);
  }
}
