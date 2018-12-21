#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <glimac/shader130Manager.hpp>

#define psize (2*sizeof(GLfloat));

using namespace glimac;

class Vertex2DUV 
{
public:
    //methode
    Vertex2DUV();
    Vertex2DUV(glm::vec2 position,glm::vec2 m_coordtexture);
    //attributs
    glm::vec2 m_position;
    glm::vec2 m_coordtexture;

};

Vertex2DUV::Vertex2DUV()
    :m_position(0,0),m_coordtexture(0,0)
{}
Vertex2DUV::Vertex2DUV(glm::vec2 position,glm::vec2 coord)
	:m_position(position),m_coordtexture(coord)
{}



int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/tex2D.vs.glsl",
                                  applicationPath.dirPath() + "shaders/multiTex2D.fs.glsl");
    program.use();

    /********************************
    IF YOU'RE USING GLSL VERSION 130
    DELETE THIS PART IF YOU'RE VERSION 330
    ********************************/
    GLuint test = LoadShader("/home/administrateur/Documents/Marion/TD 2/GLImac-Template/TP_2/shaders/tex2D.vs.glsl", "/home/administrateur/Documents/Marion/TD 2/GLImac-Template/TP_2/shaders/multiTex2D.fs.glsl");
    glUseProgram(test);
    /********************************
    END - IF YOU'RE USING GLSL VERSION 130
    ********************************/

   	GLint uModelMatrixLocation = glGetUniformLocation(program.getGLId(), "uModelMatrix");
   	GLint uModelColor = glGetUniformLocation(program.getGLId(),"uColor");
   	GLint uModelTexture1 = glGetUniformLocation(program.getGLId(),"uTexture1");
    GLint uModelTexture2 = glGetUniformLocation(program.getGLId(),"uTexture2");


    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
	     *********************************/

    Vertex2DUV sommet1, sommet2, sommet3, sommet4, sommet5, sommet6;

     GLuint vbo, vbo2;
     glGenBuffers(1,&vbo);
     glBindBuffer(GL_ARRAY_BUFFER,vbo);
     
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

     // Spécification des attribut de vertex
     
     glBindBuffer(GL_ARRAY_BUFFER,vbo);
     glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(Vertex2DUV),(void *) offsetof(Vertex2DUV,m_position));
     glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(Vertex2DUV),(void *) offsetof(Vertex2DUV,m_coordtexture));
     glBindBuffer(GL_ARRAY_BUFFER,0);
     glBindVertexArray(0);


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

     // Spécification des attribut de vertex
     
     glBindBuffer(GL_ARRAY_BUFFER,vbo2);
     glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(Vertex2DUV),(void *) offsetof(Vertex2DUV,m_position));
     glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(Vertex2DUV),(void *) offsetof(Vertex2DUV,m_coordtexture));
     glBindBuffer(GL_ARRAY_BUFFER,0);
     glBindVertexArray(0);


     std::unique_ptr<Image> pImage1, pImage2;
     pImage1 = loadImage("/home/administrateur/Documents/Marion/TD 2/GLImac-Template/assets/texture/Menu-player.png");
     pImage2 = loadImage("/home/administrateur/Documents/Marion/TD 2/GLImac-Template/assets/texture/Menu-player.png");
     
     if(pImage1==NULL){
     	std::cout<<"oups !"<<std::endl;
     }
     if(pImage2==NULL){
        std::cout<<"oups !"<<std::endl;
     }

	GLuint texture[2];
    glGenTextures(2, texture);

    // bind first texture
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,pImage1->getWidth(),
    		pImage1->getHeight(),0,GL_RGBA,GL_FLOAT,pImage1->getPixels());
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D,0);

    // bind second texture
    glBindTexture(GL_TEXTURE_2D, texture[1]);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,pImage2->getWidth(),
            pImage2->getHeight(),0,GL_RGBA,GL_FLOAT,pImage2->getPixels());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,0);

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }

            // interaction avec les boutons
            if(windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT) == true){
                glm::ivec2 mousePosition = windowManager.getMousePosition();
                float mousePosX = mousePosition.x;
                float mousePosY = mousePosition.y;
                // bouton width : 400 px
                if(mousePosX >= 200 && mousePosX <= 600){
                    // leave
                    if(mousePosY >= 250 && mousePosY <= 350){
                        done = true;
                    }
                    // play
                    if( mousePosY >= 120 && mousePosY <= 220){
                        std::cout << "Let's go !" << std::endl;
                    }
                }
            }
        }

        /****************************************
         * HERE SHOULD COME THE RENDERING CODE *
         ***************************************/

         //Netoyer la fenetre
         glClear(GL_COLOR_BUFFER_BIT);


        glUniform1i(uModelTexture1, 0);
        glUniform1i(uModelTexture2, 1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,texture[0]);
            //Triangle 1
            glm::mat3 matTriangle1 = glm::mat3(1.f);
            glm::vec3 colorTriangle = glm::vec3(0,1,0);
            glUniformMatrix3fv(uModelMatrixLocation,1,GL_FALSE,glm::value_ptr(matTriangle1));
            glUniform3fv(uModelColor,1, glm::value_ptr(colorTriangle));
            //Dessiner le triangle
            glBindVertexArray(vao);
                glDrawArrays(GL_TRIANGLES,0,3);
            glBindVertexArray(0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0); // débind sur l'unité GL_TEXTURE0


        // texture triangle 2
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,texture[0]);
             // Triangle 2
            glm::mat3 matTriangle2 = glm::mat3(1.f);
            colorTriangle = glm::vec3(1,0,0);
            
            glUniformMatrix3fv(uModelMatrixLocation,1,GL_FALSE,glm::value_ptr(matTriangle2));
            glUniform3fv(uModelColor,1,glm::value_ptr(colorTriangle));
            //Dessiner le triangle
            glBindVertexArray(vao2);
            glDrawArrays(GL_TRIANGLES,0,3);
            glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0); // débind sur l'unité GL_TEXTURE1


        // Update the display
        windowManager.swapBuffers();
    }
    glDeleteTextures(2,(GLuint*)(&texture));
    return EXIT_SUCCESS;
}
