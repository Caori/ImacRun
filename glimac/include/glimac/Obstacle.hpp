#pragma once

#include <iostream>
#include <stdlib.h>

#include "glm.hpp"
#include "common.hpp"
#include "FilePath.hpp"
#include "Object.hpp"
#include "Camera.hpp"
#include "Cube.hpp"
#include "glimac/Sphere.hpp"
#include <glimac/Model.hpp>


namespace glimac {
	/*!
	\class Obstacle
	\brief A class derived of Object used to represent an obstacle
	*/
	class Obstacle : public Object {
	public:
		const Model& model;
		
		Obstacle(const Model& model);

		~Obstacle() {}

		/*!
		* \fn void draw(int i, int j, glm::mat4 &viewMatrix, Cube& cube, Sphere& sphere, const FilePath& applicationPath) const
		* \brief A function derived from Object::draw().
		    Sends data to the shaders and draws an obstacle.
		* \param i Corresponding X coordinate in the scene grid
		* \param j Corresponding Y coordinate in the scene grid 
		* \param viewMatrix Reference to the active view matrix
		* \param cube Reference to the scene's cube primitive
		* \param sphere Reference to the scene's cube primitive
		* \param applicationPath Path to main file, cannot be null
		*/
		void draw(int i, int j, glm::mat4& viewMatrix, Cube& cube, Sphere& sphere, SDLWindowManager& window) const;
	};
}
