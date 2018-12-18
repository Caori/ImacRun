#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <iostream>

#include "glimac/common.hpp"
#include "glimac/Ground.hpp"
#include "glimac/Cube.hpp"
#include "glimac/Object.hpp"
#include "glimac/Sphere.hpp"
//#include "Texture.hpp"

namespace glimac {

Ground::Ground(const FilePath& applicationPath)
    :Object(applicationPath){
}

void Ground::draw(int i, int j, glm::mat4 &viewMatrix/*Camera& camera*/, Cube& cube, Sphere& sphere) const {
    //attention 800..0/600.0 correspond largeur/hauteur fenetre, à voir + tard
    glm::mat4 projMatrix = glm::perspective(glm::radians(70.f),800.f/600.f ,0.1f,100.f)*viewMatrix;

    glBindVertexArray(cube.vao);
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0),glm::vec3(j, 0., -i))*viewMatrix;
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        glUniformMatrix4fv(uMVPMatrix, 1, false, glm::value_ptr(projMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix, 1, false, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, false, glm::value_ptr(NormalMatrix));
        glDrawArrays(GL_TRIANGLES,0,cube.getVertexCount());
    glBindVertexArray(0);
}


}
