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
#include <algorithm>

namespace glimac {

	Scene::Scene(const std::string& map)
		:_posX(0), _posZ(0), _direction("NORD") {
		_objects["Ground"] = new Ground(AssetLoader::instance().models()["cube"]);
		_objects["Wall"] = new Wall(AssetLoader::instance().models()["barrel"]);
		_objects["Coin1"] = new Coin(1, AssetLoader::instance().models()["coin"]);
		_objects["Coin2"] = new Coin(2, AssetLoader::instance().models()["coin"]);
		_objects["Coin3"] = new Coin(3, AssetLoader::instance().models()["coin"]);
		_objects["Ark"] = new Ark(AssetLoader::instance().models()["bird"]);
		_objects["Obstacle"] = new Obstacle(AssetLoader::instance().models()["rock"]);
		//camera, lights à faire
		try {
			_grid = readPPM(map);
		}
		catch (const Exception &e) {
			std::cerr << e.what() << std::endl;
		}
	}

	Scene::~Scene(){
		for(std::map<std::string, Object*>::iterator it=_objects.begin(); it!=_objects.end(); it++){
			delete(it->second);
			_objects.erase(it);
		}
	}

	void Scene::drawScene(glm::mat4& viewMatrix, SDLWindowManager& windowManager){
		_light.drawLight(viewMatrix, glm::vec4(0, 1, 0.5f, 0));
		for (int i=0; i<_grid.size(); i++){
	    	for (int j=0; j<_grid[0].size(); j++){
	    		if (_grid[i][j][0] == 1){
	    			_objects["Ground"]->draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, windowManager);
	    		}
				if (_grid[i][j][0] == 2){
					switch(_grid[i][j][2]){
						case 0:
							_objects["Ground"]->draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, windowManager);
							_objects["Coin1"]->draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, windowManager);
						case 1:
							_objects["Ground"]->draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, windowManager);
							_objects["Coin2"]->draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix,  windowManager);
						case 2:
							_objects["Ground"]->draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, windowManager);
							_objects["Coin3"]->draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, windowManager);			
					}
	    		}
				if ( _grid[i][j][0] == 3){
					_objects["Ground"]->draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, windowManager);
					_objects["Ark"]->draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, windowManager);
				}
				if (_grid[i][j][0] == 4){
					_objects["Ground"]->draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, windowManager);
					_objects["Obstacle"]->draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, windowManager);
				}
				if (_grid[i][j][0] == 5){
					_objects["Ground"]->draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, windowManager);
	    			_objects["Wall"]->draw(_grid.size()-(i+_posZ), _grid[0].size()/2-(j+_posX), viewMatrix, windowManager);
				}
	    	}
	    }
	}

	std::vector< std::vector< std::vector<int>>> Scene::readPPM(const std::string &map){
		std::ifstream file(Parameters::instance().appPath().dirPath() + "../../ImacRun/assets/maps/" + map, std::ios::in);
			if(!file){
				THROW_EXCEPTION("Impossible de lire le fichier PPM : "+map);
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