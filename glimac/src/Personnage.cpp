#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <string>
#include <glimac/SDLWindowManager.hpp>
#include "glimac/common.hpp"
#include "glimac/Personnage.hpp"
#include "glimac/Cube.hpp"
#include "glimac/Object.hpp"
#include "glimac/Sphere.hpp"
#include "glimac/Scene.hpp"
#include "glimac/MapTransformation.hpp"
//#include "Texture.hpp"

namespace glimac {

Personnage::Personnage(const FilePath& applicationPath, float demiLargeur)
    :_x(demiLargeur), _xGrid(demiLargeur), _y(1.), _z(0.), _zGrid(0.), _scale(1.f), _score(0), _jump(0), _isFalling(0), _isCrouched(0), Object(applicationPath){
}

void Personnage::draw(int i, int j, glm::mat4 &viewMatrix/*Camera& camera*/, Cube& cube, Sphere& sphere) const {
    //attention 800..0/600.0 correspond largeur/hauteur fenetre, à voir + tard
    glm::mat4 projMatrix = glm::perspective(glm::radians(70.f),800.f/600.f ,0.1f,100.f);
    glBindVertexArray(cube.vao);
        glm::mat4 MVMatrix = viewMatrix*glm::translate(glm::mat4(1.0),glm::vec3(_x-50,_y+0.4, -(_z+1)));
        MVMatrix = glm::scale(MVMatrix, glm::vec3(0.7, _scale*1.5, 0.6));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        glUniformMatrix4fv(uMVPMatrix, 1, false, glm::value_ptr(projMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix, 1, false, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, false, glm::value_ptr(NormalMatrix));
        glDrawArrays(GL_TRIANGLES,0,cube.getVertexCount());
    glBindVertexArray(0);
}

void Personnage::move(std::vector< std::vector< std::vector<int>>> &grid, float speed, std::string &position){
    fallTest(grid);
    if (_isFalling){
        _y -= 0.08;
    }
    moveFront(grid, speed, position);
    if (_jump !=0){
        jump(grid);
    }

}

void Personnage::moveFront(std::vector< std::vector< std::vector<int>>> &grid, float speed, std::string &position){
    int blocType = grid[grid.size()-_zGrid-1][grid[0].size()-_xGrid][_y];
    int upblocType = grid[grid.size()-_zGrid-1][grid[0].size()-_xGrid][_y+1];
    if ((blocType != 4 && blocType != 5 && blocType != 3)&&(upblocType != 3)||_jump==3){
        _z+=speed;//0.2 c'est la vitesse de défillement de la caméra
        if (position == "NORD"){
            _zGrid+=speed;
        }
        if (position == "OUEST"){
            _xGrid-=speed;
        }
        if (position == "SUD"){
            _zGrid+=speed;
        }
        if (position == "EST"){
            _xGrid+=speed;
        }

        if (blocType == 2){
            _score += 1;
            std::cout<<"score :"<<_score<<std::endl;
            grid[grid.size()-_zGrid-1][grid[0].size()-_xGrid][0]=1;
            grid[grid.size()-_zGrid-1][grid[0].size()-_xGrid][1]=1;
        }


    }
    else{
        if (upblocType==3 || blocType==3){
            if (_scale<1.f){
                _z+=speed;
                if (position == "NORD"){
                    _zGrid+=speed;
                }
                if (position == "OUEST"){
                    _xGrid-=speed;
                }
                if (position == "SUD"){
                    _zGrid+=speed;
                }
                if (position == "EST"){
                    _xGrid+=speed;
                }
            }
            else{
                std::cout<<"GAME OVER"<<std::endl;
            }
        }
    }
}

void Personnage::jump(const std::vector< std::vector< std::vector<int>>> &grid){
    int upblocType = grid[grid.size()-_zGrid][grid[0].size()-int(_xGrid)][int(_y)+1];
    int downblocType = grid[grid.size()-_zGrid][grid[0].size()-(_xGrid)][int(_y)];
    //std::cout<<downblocType<<std::endl;
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
            if(downblocType != 4){
                _y-=0.05;    
            }
        }
    }                                                         
}



void Personnage::moveLeft(std::vector< std::vector< std::vector<int>>> &grid, int &posX, int &posZ, std::string &position){
    int leftPath = grid[grid.size()-_zGrid-1][grid[0].size()-_xGrid+4][0];
    int blocType = grid[grid.size()-_zGrid-1][grid[0].size()-_xGrid+1][0];
    //pour tourner a gauche
    if (leftPath != 0 && blocType != 5){
        rotateGridLeft(grid);
        if (position == "NORD"){
            position = "OUEST";
        }
        if (position == "OUEST"){
            position = "SUD";
        }
        if (position == "SUD"){
            position = "EST";
        }
        if (position == "EST"){
            position = "NORD";
        }
        std::cout<<_x<<" "<<_z<<" grid:"<<_xGrid<<" "<<_zGrid<<std::endl;
        posX =int(_z)-int(_xGrid)+2;
        posZ =int(50)-int(_z)-1; 
        int tmp = _zGrid;
        _zGrid = 99-int(_xGrid)+1;
        _xGrid = tmp+2;
        //posX = (99-_z);
        //posZ = 99-_x;
    }
    //pour se décaler d'un cran a gauche
    else{
        if (blocType != 5 && blocType != 3 && blocType != 4){
            if (blocType == 2){
                _score += 1;
                std::cout<<"score :"<<_score<<std::endl;
                grid[grid.size()-_zGrid-1][grid[0].size()-_xGrid+1][0]=1;
                grid[grid.size()-_zGrid-1][grid[0].size()-_xGrid+1][1]=1;
            }
            _x--;
            if (position == "NORD"){
                _xGrid--;
            }
            if (position == "OUEST"){
                _zGrid++;
            }
            if (position == "SUD"){
                _xGrid++;
            }
            if (position == "EST"){
                _zGrid--;
            }
        }
    }
}

void Personnage::moveRight(std::vector< std::vector< std::vector<int>>> &grid, int &posX, int &posZ, std::string &position){
    int rightPath = grid[grid.size()-_zGrid-1][grid[0].size()-_xGrid-4][0];
    int blocType = grid[grid.size()-_zGrid-1][grid[0].size()-_xGrid-1][0]; 
    //pour tourner a droite
    if (rightPath != 0 && blocType!=5){
        rotateGridRight(grid);
        if (position == "NORD"){
            position = "EST";
        }
        if (position == "EST"){
            position = "SUD";
        }
        if (position == "SUD"){
            position = "OUEST";
        }
        if (position == "OUEST"){
            position = "NORD";
        }
        std::cout<<_x<<" "<<_z<<" grid:"<<_xGrid<<" "<<_zGrid<<std::endl;
        posX =-(int(_z)-int(_xGrid))-1;
        posZ =(int(50)-int(_z))-2; 
        float tmp = _xGrid;
        _xGrid = 99-_zGrid;
        _zGrid = tmp-2;
        //posX = (99-_z);
        //posZ = 99-_x;
    }
    //pour se décaler d'un cran a droite
    else{
        if (blocType != 5 && blocType != 3 && blocType != 4){
            if (blocType == 2){
                _score += 1;
                std::cout<<"score :"<<_score<<std::endl;
                grid[grid.size()-_zGrid-1][grid[0].size()-_xGrid-1][0]=1;
                grid[grid.size()-_zGrid-1][grid[0].size()-_xGrid-1][1]=1;
            }
            _x++;
            if (position == "NORD"){
                _xGrid++;
            }
            if (position == "OUEST"){
                _zGrid--;
            }
            if (position == "SUD"){
                _xGrid--;
            }
            if (position == "EST"){
                _zGrid++;
            }
        }
    }
}

void Personnage::fallTest(const std::vector< std::vector< std::vector<int>>> &grid){
    int blocType = grid[grid.size()-_zGrid-1][grid[0].size() - _xGrid][0];
    if (blocType == 0 && _jump==0){
        if (_isFalling == 0){
            std::cout<<"Faaaaallllllllllllllllllll !"<<std::endl<<"GAME OVER"<<std::endl;
            _isFalling = 1; 
        }
    }
}




}
