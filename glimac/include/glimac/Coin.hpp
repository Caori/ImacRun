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

namespace glimac {
	/*!
	\class Coin
	\brief A class derived of Object used to represent a coin
	*/
	class Coin : public Object {
	public:
		int _value;

		Coin(const FilePath& applicationPath, int value);

		~Coin() {}

		/*!
		* \fn void draw(int i, int j, glm::mat4 &viewMatrix, Cube& cube, Sphere& sphere, const FilePath& applicationPath) const
		* \brief A function derived from Object::draw().
		Sends data to the shaders and draws a coin.
		* \param i Corresponding X coordinate in the scene grid
		* \param j Corresponding Y coordinate in the scene grid 
		* \param viewMatrix Reference to the active view matrix
		* \param cube Reference to the scene's cube primitive
		* \param sphere Reference to the scene's sphere primitive
		* \param window Reference to the game's window
		*/
		void draw(int i, int j, glm::mat4& viewMatrix, Cube& cube, Sphere& sphere, SDLWindowManager& window) const;
	};
}
