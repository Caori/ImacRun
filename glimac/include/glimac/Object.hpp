#pragma once

#include <iostream>
#include <stdlib.h>
#include <string>

#include "glm.hpp"
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include "glimac/Cube.hpp"
#include "glimac/Sphere.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Parameters.hpp>

namespace glimac {
	/*! 
	\class Object
	\brief An abstract class used to represent a game object.
	*/
	class Object {
	protected:
		Program _Program; /**< The combination of shaders used by the object. */
		GLint uMVPMatrix; /**< The uniform location for the MVP matrix*/
		GLint uMVMatrix; /**< The uniform location for the MV matrix*/
		GLint uNormalMatrix; /**< The uniform location for the normal matrix*/
		//GLint uTexture; /**< The uniform location for the texture*/
		GLint uKd; /**< The uniform location for the material's diffuse coefficient*/
		GLint uKs; /**< The uniform location for the material's diffuse coefficient*/
		GLfloat uShininess; /**< The uniform location for the material's shininess*/

	public:
		GLint uTexture;

		Object()
			: _Program(loadProgram(Parameters::instance().appPath().dirPath() + "shaders/3D.vs.glsl",
			Parameters::instance().appPath().dirPath() + "shaders/directionallight.fs.glsl")) {
			_Program.use();
			uMVPMatrix = glGetUniformLocation(_Program.getGLId(), "uMVPMatrix");
			uMVMatrix = glGetUniformLocation(_Program.getGLId(), "uMVMatrix");
			uNormalMatrix = glGetUniformLocation(_Program.getGLId(), "uNormalMatrix");
			uTexture = glGetUniformLocation(_Program.getGLId(), "uTexture");
			uKd = glGetUniformLocation(_Program.getGLId(), "uKd");
			uKs = glGetUniformLocation(_Program.getGLId(), "uKs");
			uShininess = glGetUniformLocation(_Program.getGLId(), "uShininess");
			uTexture = glGetUniformLocation(_Program.getGLId(), "uTexture");
		}

		~Object() {}

		/*!
		* \fn virtual void draw(int i, int j, glm::mat4 &viewMatrix, Cube& cube, Sphere& sphere, const FilePath& applicationPath) const
		* \brief A pure virtual function to draw a game object.
		* \param i Corresponding X coordinate in the scene grid
		* \param j Corresponding Y coordinate in the scene grid 
		* \param viewMatrix Reference to the active view matrix
		* \param cube Reference to the scene's cube primitive
		* \param sphere Reference to the scene's cube primitive
		* \param window Reference to the game's window
		*/
		virtual void draw(int i, int j, glm::mat4& viewMatrix, SDLWindowManager& window) const = 0;
	};

}
