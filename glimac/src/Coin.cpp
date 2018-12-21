#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <iostream>

#include "glimac/common.hpp"
#include "glimac/Coin.hpp"
#include "glimac/Cube.hpp"
#include "glimac/Sphere.hpp"
#include "glimac/SDLWindowManager.hpp"
//#include "Texture.hpp"

namespace glimac {

Coin::Coin(const FilePath& applicationPath, int value)
    :_value(value), Object(applicationPath){
}


void Coin::draw(int i, int j, glm::mat4 &viewMatrix, Cube &cube, Sphere &sphere, SDLWindowManager &window) const{
    glm::mat4 projMatrix = glm::perspective(glm::radians(70.f),800.f/600.f ,0.1f,100.f);
    glBindVertexArray(cube.vao);
      glm::mat4 MVMatrix = viewMatrix*glm::translate(glm::mat4(1.0),glm::vec3(j, 0., -i));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        glUniformMatrix4fv(uMVPMatrix, 1, false, glm::value_ptr(projMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix, 1, false, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, false, glm::value_ptr(NormalMatrix));
        glDrawArrays(GL_TRIANGLES,0,cube.getVertexCount());
    glBindVertexArray(0);
 
    glBindVertexArray(sphere.vao);
        MVMatrix = viewMatrix*glm::translate(glm::mat4(1.0),glm::vec3(j, 1., -i));
        MVMatrix = glm::rotate(MVMatrix, window.getTime(), glm::vec3(0,1,0));
        MVMatrix = glm::scale(MVMatrix, glm::vec3(0.2*0.3*_value, 0.3*_value, 0.3*_value));
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        glUniformMatrix4fv(uMVPMatrix, 1, false, glm::value_ptr(projMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix, 1, false, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, false, glm::value_ptr(NormalMatrix));
        glDrawArrays(GL_TRIANGLES,0,sphere.getVertexCount());
    glBindVertexArray(0);
}


}
