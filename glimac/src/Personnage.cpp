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
#include "glimac/Scene.hpp"
//#include "Texture.hpp"

namespace glimac {

Personnage::Personnage(const FilePath& applicationPath, float largeur)
    :_x(largeur), _y(0.), _z(0.), Object(applicationPath){
}

void Personnage::draw(int i, int j, glm::mat4 &viewMatrix, glm::mat4 &rotationMatrix/*Camera& camera*/, Cube& cube, Sphere& sphere) const {
    //attention 800..0/600.0 correspond largeur/hauteur fenetre, à voir + tard
    glm::mat4 projMatrix = glm::perspective(glm::radians(70.f),800.f/600.f ,0.1f,100.f);
    glBindVertexArray(cube.vao);
        glm::mat4 MVMatrix = viewMatrix*glm::translate(glm::mat4(1.0),glm::vec3(0,1.5,-_z));
        MVMatrix = glm::scale(MVMatrix, glm::vec3(1., 2., 0.6));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        glUniformMatrix4fv(uMVPMatrix, 1, false, glm::value_ptr(projMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix, 1, false, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, false, glm::value_ptr(NormalMatrix));
        glDrawArrays(GL_TRIANGLES,0,cube.getVertexCount());
    glBindVertexArray(0);
}


}
