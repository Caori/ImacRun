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
#include <glimac/Light.hpp>
#include <glimac/DirectionalLight.hpp>
#include <GL/glew.h>
#include <string>
#include <glimac/Image.hpp>
#include "glimac/AssetLoader.hpp"
#include <glimac/Model.hpp>
#include <glimac/Parameters.hpp>

namespace glimac {

	Scene::Scene(const std::string& map)
		:_posX(0), _posZ(0), _direction("NORD") {
		//camera, lights à faire
		try {
			_grid = readPPM(map);
		}
		catch (const Exception &e) {
			std::cerr << e.what() << std::endl;
		}
	}

	void Scene::drawScene(glm::mat4& viewMatrix, SDLWindowManager& windowManager){

		Ground ground(AssetLoader::instance().models()["cube"]);
		Wall wall(AssetLoader::instance().models()["barrel"]);
		Coin coin1(1, AssetLoader::instance().models()["coin"]);
		Coin coin2(2, AssetLoader::instance().models()["coin"]);
		Coin coin3(3, AssetLoader::instance().models()["coin"]);
		Ark ark(AssetLoader::instance().models()["bird"]);
		Obstacle obstacle(AssetLoader::instance().models()["cat"]);

		DirectionalLight light;
		light.drawLight(viewMatrix, glm::vec4(0, 1, 0, 0));

		for (int i=0; i<_grid.size(); i++){
	    	for (int j=0; j<_grid[0].size(); j++){
	    		if (_grid[i][j][0] == 1){
	    			ground.draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, _cube, _sphere, windowManager);
	    		}
				if (_grid[i][j][0] == 2){
					switch(_grid[i][j][2]){
						case 0:
							coin1.draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, _cube, _sphere, windowManager);
						case 1:
							coin2.draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, _cube, _sphere, windowManager);
						case 2:
							coin3.draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, _cube, _sphere, windowManager);			
					}
	    		}
				if ( _grid[i][j][0] == 3){
					ark.draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, _cube, _sphere, windowManager);
				}
				if (_grid[i][j][0] == 4){
					obstacle.draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, _cube, _sphere, windowManager);
				}
				if (_grid[i][j][0] == 5){
	    			wall.draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, _cube, _sphere, windowManager);
				}
	    	}
	    }
	}

	std::vector< std::vector< std::vector<int>>> Scene::readPPM(const std::string &map){
		std::ifstream file(Parameters::instance().appPath().dirPath() + "../../ImacRun/assets/maps/" + map, std::ios::in);
			if(!file){
				THROW_EXCEPTION("Impossible de lire le fichier PPM");
			}

		int length, height;
		std::string linePass;
		getline(file, linePass);
		getline(file, linePass);
		file >> length >> height;
		std::cout<<length<<"x"<<height<<std::endl;

		int coinType=0;

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
							switch(coinType){
								case 0: 
									grid[i][j][2]=0;
									coinType++;
									break;
								case 1: 
									grid[i][j][2]=1;
									coinType++;
									break;
								case 2: 
									grid[i][j][2]=2;
									coinType=0;
									break;
								default:
									break;
							}
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
			}
		}

		file.close();

		return grid;
	}


}