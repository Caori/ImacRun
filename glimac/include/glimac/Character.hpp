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
#include <string>

namespace glimac {
	/*! \class Character
	\brief A class used to represent the object controlled by the player.
	*/
	class Character : public Object {
	public:
		float _x,_y,_z;
		float _xGrid, _zGrid;
		float _scale;
		/// \return Coin
		int _score;
		int _jump; //ceci est un booléen
		bool _isFalling;
		bool _isCrouched;

		Character(float demiLargeur, float y=0, float z=0., float _scale=1.);

		~Character() {}

		/*!
		* \fn void draw(int i, int j, glm::mat4 &viewMatrix, Cube& cube, Sphere& sphere) const
		* \brief A function derived from Object::draw().
			Sends data to the shaders and draws the character.
		* \param i Corresponding X coordinate in the scene grid
		* \param j Corresponding Y coordinate in the scene grid 
		* \param viewMatrix Reference to the active view matrix
		* \param cube Reference to the scene's cube primitive
		* \param sphere Reference to the scene's cube primitive
		*/
		void draw(int i, int j, glm::mat4& viewMatrix, Cube& cube, Sphere& sphere, SDLWindowManager &window) const;
		
		/*!
		* \fn void move(std::vector< std::vector< std::vector<int>>> &grid, float speed, std::string &position)
		* \brief Manages the character's movement with conditions.
		* \param grid Reference to the scene grid
		* \param speed the distance the character covers each loop
		* \param position Reference to the character's position
		*/		
		void move(std::vector< std::vector< std::vector<int>>>& grid, float speed, std::string& position);

		/*!
		* \fn int moveFront(std::vector< std::vector< std::vector<int>>> &grid, float speed, std::string &position)
		* \brief Makes the character move forward.
		* \param grid Reference to the scene grid
		* \param speed the distance the character covers each loop
		* \param position Reference to the character's position
		* \return 0 if the player is at the edge of the map
		*/
		int moveFront(std::vector< std::vector< std::vector<int>>>& grid, float speed, std::string& position);
		
		/*!
		* \fn void jump(const std::vector< std::vector< std::vector<int>>>& grid)
		* \brief Makes the character jump.
		* \param grid Reference to the scene grid
		*/
		void jump(const std::vector< std::vector< std::vector<int>>>& grid);

		/*!
		* \fn void moveLeft(std::vector< std::vector< std::vector<int>>>& grid, int& posX, int& posZ, std::string& position)
		* \brief Makes the character move a step to the left.
		* \param grid Reference to the scene grid
		* \param posX Reference to the character's X coordinate
		* \param posZ Reference to the character's Z coordinate
		* \param position Reference to the character's position
		*/
		void moveLeft(std::vector< std::vector< std::vector<int>>>& grid, int& posX, int& posZ, std::string& position);
		
		/*!
		* \fn void moveRight(std::vector< std::vector< std::vector<int>>>& grid, int& posX, int& posZ, std::string& position)
		* \brief Makes the character move a step to the right.
		* \param grid Reference to the scene grid
		* \param posX Reference to the character's X coordinate
		* \param posZ Reference to the character's Z coordinate
		* \param position Reference to the character's position
		*/
		void moveRight(std::vector< std::vector< std::vector<int>>>& grid, int& posX, int& posZ, std::string& position);
		
		/*!
		* \fn fallTest(const std::vector< std::vector< std::vector<int>>>& grid)
		* \brief Test if the character is falling.
		* \param grid Reference to the scene grid
		*/
		void fallTest(const std::vector< std::vector< std::vector<int>>>& grid);
	};
}
