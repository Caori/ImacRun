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
#include <glimac/Model.hpp>
#include <glimac/Light.hpp>
#include <glimac/DirectionalLight.hpp>
#include <string>
#include <map>

namespace glimac {
	/*!
	\class Scene
	\brief A class used to represent the game environment.
		Stores the primitive elements used in the environment;
	*/
	class Scene {
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
		std::map<std::string, Object*> _objects;
		DirectionalLight _light;

		Scene(const std::string &map);

		~Scene();

		/*!
		* \fn std::vector< std::vector< std::vector<int>>> readPPM(const std::string& map, const FilePath& applicationPath)
		* \brief Reads the PPM file and fills un _grid with corresponding integers
		* \param map Reference to the map name.
		* \param applicationPath Path to main file, cannot be null
		* \return 3D vector of integers
		*/
		std::vector< std::vector< std::vector<int>>> readPPM(const std::string& map);

		/*!
		* \fn inline int getWidth()
		* \brief Gets the width of the grid
		* \return integer width of _grid
		*/
		int getWidth(){
			return _grid[0].size();
		}

		/*!
		* \fn void drawScene(glm::mat4& viewMatrix, FilePath& applicationPath);
		* \brief Places the lights, cameras and game objects and calls their draw functions
		* \param viewMatrix Reference to the active view matrix
		* \param applicationPath Path to main file, cannot be null
		* \param windowManager Reference to the current window manager
		*/
		void drawScene(glm::mat4& viewMatrix, SDLWindowManager& windowManager);
	};
}
