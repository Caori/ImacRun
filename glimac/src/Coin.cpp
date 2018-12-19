#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <iostream>

#include "glimac/common.hpp"
#include "glimac/Coin.hpp"
#include "glimac/Cube.hpp"
#include "glimac/Sphere.hpp"
//#include "Texture.hpp"

namespace glimac {

Coin::Coin(const FilePath& applicationPath)
    :Object(applicationPath){
}

void Coin::draw(int i, int j, glm::mat4 &viewMatrix, glm::mat4 &rotationMatrix, Cube &cube, Sphere &sphere) const{
    glm::mat4 projMatrix = glm::perspective(glm::radians(70.f),800.f/600.f ,0.1f,100.f)*viewMatrix;

    glBindVertexArray(cube.vao);
      glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0),glm::vec3(j, 0., -i))*viewMatrix;
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        glUniformMatrix4fv(uMVPMatrix, 1, false, glm::value_ptr(projMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix, 1, false, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, false, glm::value_ptr(NormalMatrix));
        glDrawArrays(GL_TRIANGLES,0,cube.getVertexCount());
    glBindVertexArray(0);

    glBindVertexArray(sphere.vao);
        MVMatrix = glm::translate(glm::mat4(1.0),glm::vec3(j, 1., -i))*viewMatrix;
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        glUniformMatrix4fv(uMVPMatrix, 1, false, glm::value_ptr(projMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix, 1, false, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, false, glm::value_ptr(NormalMatrix));
        glDrawArrays(GL_TRIANGLES,0,sphere.getVertexCount());
    glBindVertexArray(0);
}


}
