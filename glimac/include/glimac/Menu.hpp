#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include "glimac/shader130Manager.hpp"

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
			//FilePath& m_filepathTexture;
			// uniform variables
			GLint uModelMatrixLocation;
		   	GLint uModelColor;
		   	GLint uModelTexture1, uModelTexture2;
		
		public:
			Menu(const FilePath& filepathShader)
			:  _Program(loadProgram("/home/administrateur/Documents/Projet/ImacRun/TP_menu/shaders/tex2D.vs.glsl",
	                                  "/home/administrateur/Documents/Projet/ImacRun/TP_menu/shaders/multiTex2D.fs.glsl"))

			{
				_Program.use();
				/********************************
			    IF YOU'RE USING GLSL VERSION 130
			    DELETE THIS PART IF YOU'RE VERSION 330
			    ********************************/
			   GLuint test = LoadShader("/home/administrateur/Documents/Projet/ImacRun/TP_menu/shaders/tex2D.vs.glsl", "/home/administrateur/Documents/Projet/ImacRun/TP_menu/shaders/multiTex2D.fs.glsl");
			    glUseProgram(test);
			    // END - IF YOU'RE USING GLSL VERSION 130
			}
			~Menu();
			
			// display the menu in parameter
			void initializeMenu(SDLWindowManager &_windowManager, const FilePath& filepath);
	};

}
