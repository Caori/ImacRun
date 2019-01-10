#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include "glimac/Menu.hpp"

namespace glimac{

Vertex2DUV::Vertex2DUV()
    :m_position(0,0),m_coordtexture(0,0)
{}
Vertex2DUV::Vertex2DUV(glm::vec2 &position,glm::vec2 &coordtexture)
	:m_position(position),m_coordtexture(coordtexture)
{}

Menu::Menu(){}

Menu::~Menu(){}

GLuint Menu::initializeMenu(){
    // vertices
    Vertex2DUV sommet1, sommet2, sommet3;

     GLuint vbo;
     glGenBuffers(1,&vbo);
     glBindBuffer(GL_ARRAY_BUFFER,vbo);
     
     // triangle vertices and texture position
     sommet1.m_position.x=-1;
     sommet1.m_position.y=-1;
     sommet1.m_coordtexture.x=0;
     sommet1.m_coordtexture.y=1;

     sommet2.m_position.x=-1;
     sommet2.m_position.y=1;
     sommet2.m_coordtexture.x=0;
     sommet2.m_coordtexture.y=0;

     sommet3.m_position.x=1;
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

GLuint Menu::initializeMenu2(){
    Vertex2DUV sommet4, sommet5, sommet6;

    GLuint vbo2;
    glGenBuffers(1,&vbo2);
    glBindBuffer(GL_ARRAY_BUFFER,vbo2);

     // second triangle
     sommet4.m_position.x=-1;
     sommet4.m_position.y=-1;
     sommet4.m_coordtexture.x=0;
     sommet4.m_coordtexture.y=1;

     sommet5.m_position.x=1;
     sommet5.m_position.y=1;
     sommet5.m_coordtexture.x=1;
     sommet5.m_coordtexture.y=0;

     sommet6.m_position.x=1;
     sommet6.m_position.y=-1;
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

GLuint Menu::loadTexture(const FilePath& filepath, const FilePath& filepath2, const FilePath& filepath3){
    // load menu backgrounds
    std::unique_ptr<Image> menuBackground, menuBackground2, menuBackground3;
    menuBackground = loadImage(filepath);
    menuBackground2 = loadImage(filepath2);
    menuBackground3 = loadImage(filepath3);

    // stock textures in array
    GLuint texture[3];
    glGenTextures(3, texture);

    // bind first texture
    glBindTexture(GL_TEXTURE_2D, texture[0]);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,menuBackground->getWidth(), menuBackground->getHeight(),0,GL_RGBA,GL_FLOAT,menuBackground->getPixels());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,0);

    // bind second texture
    glBindTexture(GL_TEXTURE_2D, texture[1]);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,menuBackground2->getWidth(), menuBackground2->getHeight(),0,GL_RGBA,GL_FLOAT,menuBackground2->getPixels());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,0);

    // bind third texture
    glBindTexture(GL_TEXTURE_2D, texture[2]);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,menuBackground3->getWidth(), menuBackground3->getHeight(),0,GL_RGBA,GL_FLOAT,menuBackground3->getPixels());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,0);

    return *texture;
}

void Menu::displayMenu(SDLWindowManager &_windowManager, GLuint *texture, int indexTexture){
    GLint uModelMatrixLocation = glGetUniformLocation(_Program.getGLId(), "uModelMatrix");
    GLint uModelColor = glGetUniformLocation(_Program.getGLId(),"uColor");
    GLint uModelTexture1 = glGetUniformLocation(_Program.getGLId(),"uTexture1");
    GLint uModelTexture2 = glGetUniformLocation(_Program.getGLId(),"uTexture2");
    GLuint uModelTexture3 = glGetUniformLocation(_Program.getGLId(), "uTexture3");
    
    GLuint vao = initializeMenu();
    GLuint vao2 = initializeMenu2();

    // each texture variable is associated with a texture unit
    glUniform1i(uModelTexture1, 0);
    glUniform1i(uModelTexture2, 1);
    glUniform1i(uModelTexture3, 2);

    glActiveTexture(GL_TEXTURE0 + indexTexture);
    glBindTexture(GL_TEXTURE_2D, uModelTexture1 + indexTexture);
        //Triangle 1
        glm::mat3 matTriangle1 = glm::mat3(1.f);
        glm::vec3 colorTriangle = glm::vec3(0,1,0);
        glUniformMatrix3fv(uModelMatrixLocation,1,GL_FALSE,glm::value_ptr(matTriangle1));
        glUniform3fv(uModelColor,1, glm::value_ptr(colorTriangle));
        //draw triangle
        glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES,0,3);
        glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0 + indexTexture);
    glBindTexture(GL_TEXTURE_2D, 0); // débind sur l'unité GL_TEXTURE0


    // texture triangle 2
    glActiveTexture(GL_TEXTURE0 + indexTexture);
    glBindTexture(GL_TEXTURE_2D, uModelTexture1 + indexTexture);
        // Triangle 2
        glm::mat3 matTriangle2 = glm::mat3(1.f);
        colorTriangle = glm::vec3(1,0,0);
                
        glUniformMatrix3fv(uModelMatrixLocation,1,GL_FALSE,glm::value_ptr(matTriangle2));
        glUniform3fv(uModelColor,1,glm::value_ptr(colorTriangle));

        glBindVertexArray(vao2);
            glDrawArrays(GL_TRIANGLES,0,3);
        glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0 + indexTexture);
    glBindTexture(GL_TEXTURE_2D, 0); // débind sur l'unité GL_TEXTURE1
}

}