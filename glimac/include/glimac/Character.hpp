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
	\brief A class used to represent moving (and also living) object (characters).
	*/
	class Character : public Object {
		protected:
			float _x, _y, _z; /**< Position in the world */
			float _scale;/**< To modify the size of the character */

		public:
			Character(float demiLargeur, float y=0, float z=+0.3, float _scale=1.);

			~Character(){}

			float getX() const{
				return _x;
			}

			float getY() const{
				return _y;
			}

			float getZ() const{
				return _z;
			}

			float setX(const float x){
				_x = x;
			}

			float setY(const float y){
				_y = y;
			}

			float setZ(const float z){
				_z = z;
			}

			float setScale(const float scale){
				_scale = scale;
			}
	};

	/*! \class Foe
	\brief A class used to represent foes who follow the player in order to kill him.
	*/
	class Foe : public Character {
		public:
			Foe(float demiLargeur, float y=0, float z=+0.3, float _scale=1.);

			~Foe(){}

			void draw(int i, int j, glm::mat4& viewMatrix, SDLWindowManager &window) const;
	};

	/*! \class Player
	\brief A class used to represent the object controlled by the player.
	*/
	class Player : public Character {
		public:
			float _xGrid, _zGrid;/**< Position of the player on the grid */
			int _score; /**< Sum of coins value */
			int _jump; //ceci est un état
			bool _isFalling;/**< State that indicates if the player is falling */
			bool _isAlive; /**< State that indicates if the player is alive */
			bool _isCrouched;/**< State that indicates if the player is crouched */

			Player(float demiLargeur, float y=0, float z=+0.3, float _scale=1.);

			~Player() {}

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
			void draw(int i, int j, glm::mat4& viewMatrix, SDLWindowManager &window) const;
			
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
