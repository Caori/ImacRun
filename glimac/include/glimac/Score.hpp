#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <cstring>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Parameters.hpp>

namespace glimac{

	class Score{
		protected:
			// path of the files needed (texture & shaders)
			Program _Program; // load shaders
			//FilePath& m_filepathTexture;
			// uniform variables
			GLint uModelMatrixLocation;
		   	GLint uModelColor;
		
		public:
			Score()
			:  _Program(loadProgram(Parameters::instance().appPath().dirPath() + "shaders/tex2D.vs.glsl",
	                                  Parameters::instance().appPath().dirPath() + "shaders/simpleTex2D.fs.glsl"))

			{
				_Program.use();
			}
			~Score();
			
			GLuint initializeVaoScore();
			GLuint initializeVaoScore2();
			GLuint initializeScore(TTF_Font *font, SDL_Color color, const unsigned int size, const char* message);
			void displayScore(GLuint *texture);
	};
}
