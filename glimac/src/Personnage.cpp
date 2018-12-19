#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <glimac/SDLWindowManager.hpp>
#include "glimac/common.hpp"
#include "glimac/Personnage.hpp"
#include "glimac/Cube.hpp"
#include "glimac/Object.hpp"
#include "glimac/Sphere.hpp"
#include "glimac/Scene.hpp"
//#include "Texture.hpp"

namespace glimac {

Personnage::Personnage(const FilePath& applicationPath, float largeur)
    :_x(largeur), _y(1.), _z(0.), _scale(1.f), _score(0), _jump(0), Object(applicationPath){
}

void Personnage::draw(int i, int j, glm::mat4 &viewMatrix, glm::mat4 &rotationMatrix/*Camera& camera*/, Cube& cube, Sphere& sphere) const {
    //attention 800..0/600.0 correspond largeur/hauteur fenetre, à voir + tard
    glm::mat4 projMatrix = glm::perspective(glm::radians(70.f),800.f/600.f ,0.1f,100.f);
    glBindVertexArray(cube.vao);
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0),glm::vec3(0,0.5,-0.2));
        MVMatrix = viewMatrix*glm::translate(glm::mat4(1.0),glm::vec3(_x-50,_y, -(_z+1)));
        MVMatrix = glm::scale(MVMatrix, glm::vec3(0.7, _scale*1.5, 0.6));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        glUniformMatrix4fv(uMVPMatrix, 1, false, glm::value_ptr(projMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix, 1, false, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, false, glm::value_ptr(NormalMatrix));
        glDrawArrays(GL_TRIANGLES,0,cube.getVertexCount());
    glBindVertexArray(0);
}

void Personnage::move(std::vector< std::vector< std::vector<int>>> &grid){
    moveFront(grid);
    if (_jump !=0){
        jump(grid);
    }

}

void Personnage::moveFront(std::vector< std::vector< std::vector<int>>> &grid){
    int blocType = grid[grid.size()-_z-1][grid[0].size()-_x][_y];
    int upblocType = grid[grid.size()-_z-1][grid[0].size()-_x][_y+1];
    if ((blocType != 4 && blocType != 5 && blocType != 3)&&(upblocType != 3)){
        _z+=0.02;//0.2 c'est la vitesse de défillement de la caméra

        if (blocType == 2){
            _score += 1;
            std::cout<<"score :"<<_score<<std::endl;
            grid[grid.size()-_z-1][grid[0].size()-_x][0]=1;
            grid[grid.size()-_z-1][grid[0].size()-_x][1]=1;
        }
    }
    else{
        if (upblocType==3 || blocType==3){
            if (_scale<1.f){
                _z+=0.2;
            }
            else{
                std::cout<<"GAME OVER"<<std::endl;
            }
        }
    }
}

void Personnage::jump(const std::vector< std::vector< std::vector<int>>> &grid){
    int upblocType = grid[grid.size()-_z][grid[0].size()-int(_x)][int(_y)+1];
    int downblocType = grid[grid.size()-_z][grid[0].size()-(_x)][int(_y)-1];

    if (upblocType !=3 && _jump==1){//s'il n'est pas sous une arche et qu'il n'est pas deja en train de sauter
        _jump=2;
    }
    if (_jump ==2){
        if (_y >= 3.){
            _jump=3;
        }
        else{
            //if(upblocType !=3){
                _y+=0.05;
            //}
        } 
    }     
    if(_jump == 3){
        if (_y<1.){
            _jump=0;
        }
        else{
            if(downblocType != 3 && downblocType != 4){
                _y-=0.05;    
            }
        }
    }        

                                    
                   
}



void Personnage::moveLeft(const std::vector< std::vector< std::vector<int>>> &grid){
    _x--;
}

void Personnage::moveRight(const std::vector< std::vector< std::vector<int>>> &grid){
    _x++;
}



}
