#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <iostream>

#include "glimac/common.hpp"
#include "glimac/Personnage.hpp"
#include "glimac/Cube.hpp"
#include "glimac/Object.hpp"
#include "glimac/Sphere.hpp"
//#include "Texture.hpp"

namespace glimac {

Personnage::Personnage(const FilePath& applicationPath, glm::vec3 &position)
    : _position(position), Object(applicationPath){
}

void Personnage::draw(int i, int j, glm::mat4 &viewMatrix, glm::mat4 &rotationMatrix/*Camera& camera*/, Cube& cube, Sphere& sphere) const {
    //attention 800..0/600.0 correspond largeur/hauteur fenetre, à voir + tard
    glm::mat4 projMatrix = glm::perspective(glm::radians(70.f),800.f/600.f ,0.1f,100.f);

    glBindVertexArray(cube.vao);
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0),glm::vec3(j, 0., -i))*viewMatrix;
        MVMatrix = glm::scale(MVMatrix, glm::vec3(1., 1.5, 0.6));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        glUniformMatrix4fv(uMVPMatrix, 1, false, glm::value_ptr(projMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix, 1, false, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, false, glm::value_ptr(NormalMatrix));
        glDrawArrays(GL_TRIANGLES,0,cube.getVertexCount());
    glBindVertexArray(0);
}


}
