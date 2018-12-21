#include "glimac/Scene.hpp"
#include "glimac/Exception.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <glimac/Cube.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Object.hpp>
#include <glimac/Ground.hpp>
#include <glimac/Wall.hpp>
#include <glimac/Coin.hpp>
#include <glimac/Ark.hpp>
#include <glimac/Obstacle.hpp>
#include <GL/glew.h>
#include <string>
#include <glimac/Light.hpp>

namespace glimac {

Scene::Scene(const std::string &map, const FilePath& applicationPath)
	:_posX(0), _posZ(0), _direction("NORD"){
	//camera, lights à faire
	_grid = readPPM(map, applicationPath);

}

void Scene::drawScene(glm::mat4 &viewMatrix, const FilePath& applicationPath){
	Ground ground(applicationPath);
	Wall wall(applicationPath);
	Coin coin(applicationPath);
	Ark ark(applicationPath);
	Obstacle obstacle(applicationPath);

	//light.drawLight(viewMatrix, glm::vec4(0, 1, 0, 0));

	for (int i=0; i<_grid.size(); i++){
    	for (int j=0; j<_grid[0].size(); j++){
    		if (_grid[i][j][0] == 1){
    			ground.draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, _cube, _sphere);
    		}
			if (_grid[i][j][0] == 2){
    			coin.draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, _cube, _sphere);
			}
			if ( _grid[i][j][0] == 3){
				ark.draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, _cube, _sphere);
			}
			if (_grid[i][j][0] == 4){
				obstacle.draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, _cube, _sphere);
			}
			if (_grid[i][j][0] == 5){
    			wall.draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, _cube, _sphere);
			}
    	}
    }
}

std::vector< std::vector< std::vector<int>>> Scene::readPPM(const std::string &map, const FilePath& applicationPath){
	std::ifstream file(applicationPath.dirPath() + "../../ImacRun/assets/maps/"+map, std::ios::in);
	//try{
		if(!file){
			//THROW_EXCEPTION("Impossible de lire le fichier test.ppm");
			std::cout<<"Impossible de lire le fichier "<<map<<std::endl;
		}
	//}
	//catch (const std::exception &e){
	//	std::cerr << e.what() << std::endl;
	//}
	int length, height;
	std::string linePass;
	getline(file, linePass);
	getline(file, linePass);
	file >> length >> height;
	std::cout<<length<<"x"<<height<<std::endl;

	std::vector< std::vector< std::vector<int>>> grid(height, std::vector<std::vector<int>>(length, std::vector<int>(3)));

	getline(file, linePass);
	int R,G,B;
	for (int i=0; i<height; i++){
		for (int j=0; j<length; j++){
			getline(file, linePass);
			file >> R;
			getline(file, linePass);
			file >> G;
			getline(file, linePass);
			file >> B;
			if (R==255){
				if (G==255){
					if (B==255){
						grid[i][j][0]=1;
					}
					else{
						grid[i][j][0]=2;
						grid[i][j][1]=2;
					}
				}
				else{
					grid[i][j][0]=4;
					grid[i][j][1]=4;
				}
			}
			else{
				if (G==255){
					grid[i][j][0]=5;
					grid[i][j][1]=5;
				}
				else{
					if (B==255){
						grid[i][j][0]=3;
						grid[i][j][2]=3;
					}
					else{
						grid[i][j][0]=0;
					}
				}
			}
			//std::cout<<grid[i][j][0]<<" ";
		}
		//std::cout<<std::endl;
	}

	file.close();

	return grid;
}


}