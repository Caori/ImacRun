#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <glimac/Parameters.hpp>

namespace glimac{

	class Vertex2DUV {
		public:
		    //methode
		    Vertex2DUV();
		    Vertex2DUV(glm::vec2 &position,glm::vec2 &coordtexture);
		public:
		    //attributs
		    glm::vec2 m_position;
		    glm::vec2 m_coordtexture;
	};

	class Menu{
		protected:
			// path of the files needed (texture & shaders)
			Program _Program; // load shaders
		
		public:
			
			Menu()
			:  _Program(loadProgram(Parameters::instance().appPath().dirPath() + "shaders/tex2D.vs.glsl",
	                                  Parameters::instance().appPath().dirPath() + "shaders/multiTex2D.fs.glsl"))

			{
				_Program.use();
			}
			~Menu();
			
			// display the menu in parameter
			GLuint initializeMenu();
			GLuint initializeMenu2();
			GLuint loadTexture(const FilePath& filepath, const FilePath& filepath2, const FilePath& filepath3);
			void displayMenu(SDLWindowManager &_windowManager, GLuint *texture, int indexTexture);
	};

}
