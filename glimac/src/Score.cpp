#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <cstring>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Menu.hpp>
#include "glimac/Score.hpp"

namespace glimac{


	Score::~Score(){}

	GLuint Score::initializeVaoScore(){
		Vertex2DUV sommet1, sommet2, sommet3;

	     GLuint vbo;
	     glGenBuffers(1,&vbo);
	     glBindBuffer(GL_ARRAY_BUFFER,vbo);
	     
	     // triangle vertices and texture position
	     sommet1.m_position.x=-0.9;
	     sommet1.m_position.y= 0.8;
	     sommet1.m_coordtexture.x=0;
	     sommet1.m_coordtexture.y=1;

	     sommet2.m_position.x=-0.9;
	     sommet2.m_position.y=1;
	     sommet2.m_coordtexture.x=0;
	     sommet2.m_coordtexture.y=0;

	     sommet3.m_position.x=-0.7;
	     sommet3.m_position.y=1;
	     sommet3.m_coordtexture.x=1;
	     sommet3.m_coordtexture.y=0;

	     Vertex2DUV vertices[] = {sommet1,sommet2,sommet3};

	     glBufferData(GL_ARRAY_BUFFER,3*sizeof(Vertex2DUV),vertices, GL_STATIC_DRAW);
	     glBindBuffer(GL_ARRAY_BUFFER,0);

	     GLuint vao;
	     glGenVertexArrays(1,&vao);
	     glBindVertexArray(vao);
	     glEnableVertexAttribArray(0);
	     glEnableVertexAttribArray(1);

	     // attributes vertex specifications
	     
	     glBindBuffer(GL_ARRAY_BUFFER,vbo);
	     glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(Vertex2DUV),(void *) offsetof(Vertex2DUV,m_position));
	     glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(Vertex2DUV),(void *) offsetof(Vertex2DUV,m_coordtexture));
	     glBindBuffer(GL_ARRAY_BUFFER,0);
	     glBindVertexArray(0);

	     return vao;
	}

	GLuint Score::initializeVaoScore2(){
		Vertex2DUV sommet4, sommet5, sommet6;

	    GLuint vbo2;
	    glGenBuffers(1,&vbo2);
	    glBindBuffer(GL_ARRAY_BUFFER,vbo2);

	    // second triangle
	    sommet4.m_position.x=-0.9;
    	sommet4.m_position.y=0.8;
	    sommet4.m_coordtexture.x=0;
	    sommet4.m_coordtexture.y=1;

	    sommet5.m_position.x=-0.7;
	    sommet5.m_position.y=1;
	    sommet5.m_coordtexture.x=1;
	    sommet5.m_coordtexture.y=0;

	    sommet6.m_position.x=-0.7;
	    sommet6.m_position.y=0.8;
	    sommet6.m_coordtexture.x=1;
	    sommet6.m_coordtexture.y=1;

	    Vertex2DUV vertices2[] = {sommet4,sommet5,sommet6};

	    glBufferData(GL_ARRAY_BUFFER,3*sizeof(Vertex2DUV),vertices2, GL_STATIC_DRAW);
	    glBindBuffer(GL_ARRAY_BUFFER,0);

	    GLuint vao2;
	    glGenVertexArrays(1,&vao2);
	    glBindVertexArray(vao2);
	    glEnableVertexAttribArray(0);
	    glEnableVertexAttribArray(1);
	     
	    glBindBuffer(GL_ARRAY_BUFFER,vbo2);
	    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(Vertex2DUV),(void *) offsetof(Vertex2DUV,m_position));
	    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(Vertex2DUV),(void *) offsetof(Vertex2DUV,m_coordtexture));
	    glBindBuffer(GL_ARRAY_BUFFER,0);
	    glBindVertexArray(0);

		return vao2;
	}

	GLuint Score::initializeScore(TTF_Font *font, SDL_Color color, const unsigned int size, const char* message){
		GLenum texture_format;
	    GLuint texture;
	    glGenTextures(1, &texture);
	    glBindTexture(GL_TEXTURE_2D, texture);

	    SDL_Surface *texte = TTF_RenderText_Blended(font, message, color);

	    GLint colors = texte->format->BytesPerPixel;

	    if(colors == 4){
	        if(texte->format->Rmask == 0x000000ff){
	            texture_format = GL_RGBA;
	        }
	        else{
	            texture_format = GL_BGRA;
	        }
	    }
	    else{
	        if(texte->format->Rmask == 0x000000ff){
	            texture_format = GL_RGB;
	        }
	        else{
	            texture_format = GL_BGR;
	        }
	    }

	    // Convert SDL_Surface into a texture by passing a pointer to the date (surface->pixels) to OpenGL
	    glTexImage2D(GL_TEXTURE_2D, 0, colors, texte->w, texte->h, 0, texture_format, GL_UNSIGNED_BYTE, texte->pixels);
	    SDL_FreeSurface(texte);

	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	    glBindTexture(GL_TEXTURE_2D,0);

	    return texture;
	}

	void Score::displayScore(GLuint *texture){
		GLint uModelMatrixLocation = glGetUniformLocation(_Program.getGLId(), "uModelMatrix");
	    GLint uModelColor = glGetUniformLocation(_Program.getGLId(),"uColor");
	    GLint uModelTexture1 = glGetUniformLocation(_Program.getGLId(),"uTexture1");
	    
	    GLuint vao = initializeVaoScore();
	    GLuint vao2 = initializeVaoScore2();

		//glEnable(GL_BLEND);
        // LIGNE CI-DESSOUS IMPORTANTE !
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glUniform1i(uModelTexture1, 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        
        glm::mat3 matTriangle1 = glm::mat3(1.f);
        glm::vec3 colorTriangle = glm::vec3(0,1,0);
        glUniformMatrix3fv(uModelMatrixLocation,1,GL_FALSE,glm::value_ptr(matTriangle1));
        glUniform3fv(uModelColor,1, glm::value_ptr(colorTriangle));
        //draw triangle
        glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES,0,3);
        glBindVertexArray(0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0); // débind sur l'unité GL_TEXTURE0

        /////////////////

       glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[0]);

        glBindVertexArray(vao2);
            glDrawArrays(GL_TRIANGLES,0,3);
        glBindVertexArray(0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
	}
}