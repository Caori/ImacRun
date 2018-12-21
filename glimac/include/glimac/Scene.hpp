#pragma once

#include <vector>
#include <GL/glew.h>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Object.hpp>
#include <glimac/Ground.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/Character.hpp>
#include <string>

namespace glimac {

class Scene{
	public:
		/*
		Light _lights[];
		Camera _cams[];*/
		//TrackballCamera _trackCam;
		Cube _cube;
		Sphere _sphere;
		int _posX, _posZ;
		std::string _direction;

		std::vector< std::vector< std::vector<int>>> _grid;

		//Constructeur et destructeurs
		Scene(const std::string &map, const FilePath& applicationPath);
		~Scene(){}
        
		std::vector< std::vector< std::vector<int>>> readPPM(const std::string &map, const FilePath& applicationPath);

		int getWidth(){
			return _grid[0].size();
		}

		void drawScene(glm::mat4 &viewMatrix, const FilePath& applicationPath, SDLWindowManager &windowManager );

};


}
