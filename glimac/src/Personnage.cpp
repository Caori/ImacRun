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
    :_x(largeur), _y(1.), _z(0.), Object(applicationPath){
}

void Personnage::draw(int i, int j, glm::mat4 &viewMatrix, glm::mat4 &rotationMatrix/*Camera& camera*/, Cube& cube, Sphere& sphere) const {
    //attention 800..0/600.0 correspond largeur/hauteur fenetre, à voir + tard
    glm::mat4 projMatrix = glm::perspective(glm::radians(70.f),800.f/600.f ,0.1f,100.f);
    glBindVertexArray(cube.vao);
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0),glm::vec3(0,0.5,0));
        MVMatrix = viewMatrix*glm::translate(glm::mat4(1.0),glm::vec3(_x-50,_y, -(_z+1)));
        MVMatrix = glm::scale(MVMatrix, glm::vec3(0.7, 2., 0.6));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        glUniformMatrix4fv(uMVPMatrix, 1, false, glm::value_ptr(projMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix, 1, false, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, false, glm::value_ptr(NormalMatrix));
        glDrawArrays(GL_TRIANGLES,0,cube.getVertexCount());
    glBindVertexArray(0);
}

void Personnage::moveFront(const std::vector< std::vector< std::vector<int>>> &grid){
    // if obstacle or ark
    if (grid[grid.size()-_z-1][grid[0].size()-_x][_y] == 4 || grid[grid.size()-_z-1][grid[0].size()-_x][2] == 3){
        _z += 0.0;
    }
    else{
        _z += 0.1;
    }
}

void Personnage::moveLeft(const std::vector< std::vector< std::vector<int>>> &grid){
    // _x, _y, _z = character's position
    // grid[longueur][largeur][hauteur]
    // grille en miroir (la gauche est à droite)
    if (grid[grid.size()-_z-1][grid[0].size()-_x+1][1] != 5){
        _x--;
    }
    else{
        _x = _x;
    }
}

void Personnage::moveRight(const std::vector< std::vector< std::vector<int>>> &grid){
    if (grid[grid.size()-_z-1][grid[0].size()-_x-1][1] != 5){
        _x++;
    }
    else{
        _x = _x;
    }
}

// la version violente de la chute (je suis là je suis plus là)
/*void Personnage::fall(const std::vector< std::vector< std::vector<int>>> &grid){
    if (grid[grid.size()-_z-1][_x][0] != 0){
        _y=_y;
    }
    else{
        _y-=10.0;
    }
}*/

bool Personnage::fall(const std::vector< std::vector< std::vector<int>>> &grid){
    if (grid[grid.size()-_z-1][_x][0] != 0){
        return 0;
    }
    else{
        return 1;
    }
}


}
