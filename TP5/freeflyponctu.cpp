#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

#include "glimac/Image.hpp"
#include "glimac/common.hpp"
#include "glimac/Sphere.hpp"
#include "glimac/FreeflyCamera.hpp"

using namespace glimac;

const uint32_t width = 800;
const uint32_t height = 800;

struct EarthProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uKd;
    GLint uKs;
    GLfloat uShininess;
    GLint uLightPos_vs;
    GLint uLightIntensity;

    EarthProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/directionallight.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uKd = glGetUniformLocation(m_Program.getGLId(), "uKd");
        uKs = glGetUniformLocation(m_Program.getGLId(), "uKs");
        uShininess = glGetUniformLocation(m_Program.getGLId(), "uShininess");
        uLightPos_vs = glGetUniformLocation(m_Program.getGLId(), "uLightPos_vs");
        uLightIntensity = glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");

    }
};

struct MoonProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uKd;
    GLint uKs;
    GLfloat uShininess;
    GLint uLightPos_vs;
    GLint uLightIntensity;

    MoonProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/pointlight.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uKd = glGetUniformLocation(m_Program.getGLId(), "uKd");
        uKs = glGetUniformLocation(m_Program.getGLId(), "uKs");
        uShininess = glGetUniformLocation(m_Program.getGLId(), "uShininess");
        uLightPos_vs = glGetUniformLocation(m_Program.getGLId(), "uLightPos_vs");
        uLightIntensity = glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");
    }
};

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(width, height, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    //permet d'appeler les shaders depuis ligne de commande
    FilePath applicationPath(argv[0]);
    EarthProgram earthProgram(applicationPath);
    MoonProgram moonProgram(applicationPath);

    //active test de profondeur GPU (pour qu'on voit pas triangles non visibles)
    glEnable(GL_DEPTH_TEST);

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

     Sphere sphere(1, 30, 30);

     GLuint vbo;
     glGenBuffers(1, &vbo);
     glBindBuffer(GL_ARRAY_BUFFER, vbo); //bind buffer vbo sur cible

     //envoi des données
     glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount()*sizeof(ShapeVertex),
                  sphere.getDataPointer(), GL_STATIC_DRAW);
     glBindBuffer(GL_ARRAY_BUFFER, 0); //debind vbo

     //création VAO
     GLuint vao;
     glGenVertexArrays(1, &vao);

     glBindVertexArray(vao); //bind vao

     const GLuint VERTEX_ATTR_POSITION = 0;
     const GLuint VERTEX_ATTR_NORMAL = 1;

      glBindBuffer(GL_ARRAY_BUFFER, vbo); //bind vbo
      //active le type d'attribut dont on parle
     glEnableVertexAttribArray(VERTEX_ATTR_POSITION); //active Position
     glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);

     glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE,
         sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, position));
     glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE,
         sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, normal));

     glBindVertexArray(0); //debind vao

     glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), (float)width/height,
        0.1f, 100.f);
        // -5 car la caméra est en 0 0 0, si on dessine en z=0 on va rien voir
     glm::mat4 MVMatrix = glm::translate(glm::mat4(), glm::vec3(0.f, 0.f, -5.f));
     glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

     //tire 32 axes de rotation possibles et positions de départ pour les Moons
     std::vector<glm::vec3> positions(32);
     for(int i=0; i< 32; i++) {
       positions[i] = glm::vec3(glm::linearRand(-2.5f, 2.5f),
        glm::linearRand(-2.5f, 2.5f), glm::linearRand(-2.5f, 2.5f));
     }
     std::vector<glm::vec3> materiauxKd(32);
     for(int i=0; i< 32; i++) {
       materiauxKd[i] = glm::vec3(glm::linearRand(0.f, 0.5f),
        glm::linearRand(0.f, 0.5f), glm::linearRand(0.f, 0.5f));
     }
     std::vector<glm::vec3> materiauxKs(32);
     for(int i=0; i< 32; i++) {
       materiauxKs[i] = glm::vec3(glm::linearRand(0.f, 0.5f),
        glm::linearRand(0.f, 0.5f), glm::linearRand(0.f, 0.5f));
     }

     std::vector<glm::vec3> axes(32);
     for(int i=0; i< 32; i++) {
       axes[i] = glm::sphericalRand(1.f);
     }

     //création caméra Freefly
     FreeflyCamera FCamera;

     //on stock la positon de la souris avante la boucle
     glm::ivec2 vieillePosition = windowManager.getMousePosition();

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            if(windowManager.isKeyPressed(SDLK_DOWN)) {
              FCamera.moveFront(-1);
            }
            if(windowManager.isKeyPressed(SDLK_UP)) {
                FCamera.moveFront(1);
            }
            if(windowManager.isKeyPressed(SDLK_RIGHT)) {
              FCamera.moveLeft(-1);
            }
            if(windowManager.isKeyPressed(SDLK_LEFT)) {
                FCamera.moveLeft(1);
            }
            //demander pourquoi la rotation marche pas
            if(windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
              glm::ivec2 newPosition = windowManager.getMousePosition();
              float deplacementX = vieillePosition.x - newPosition.x;
              float deplacementY = vieillePosition.y - newPosition.y;
              //si souris bouge horizontalement
              if(deplacementX != 0) {
                 FCamera.rotateLeft(-deplacementX*5);
               }
              //si souris bouge verticalement
              if(deplacementY != 0) {
                FCamera.rotateUp(-deplacementY*5);
              }
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

         //récupère la viewmatrix
         glm::mat4 ViewMatrix = FCamera.getViewMatrix();

         //on stock la positon de la souris
         vieillePosition = windowManager.getMousePosition();

         //choisit quels shaders utiliser
         earthProgram.m_Program.use();

         //remet la bonne valeur de MVMatrix au début de chaque tour
         glm::mat4 globalMVMatrix = ViewMatrix;

         //envoie des matrices au shader pour TERRE
          glm::mat4 earthMVMatrix = glm::rotate(globalMVMatrix,
            windowManager.getTime(), glm::vec3(0, 1, 0));
          glUniformMatrix4fv(earthProgram.uMVMatrix, 1, GL_FALSE,
          	glm::value_ptr(earthMVMatrix));
          glUniformMatrix4fv(earthProgram.uNormalMatrix, 1, GL_FALSE,
          	glm::value_ptr(glm::transpose(glm::inverse(earthMVMatrix))));
          glUniformMatrix4fv(earthProgram.uMVPMatrix, 1, GL_FALSE,
          	glm::value_ptr(ProjMatrix * earthMVMatrix));

          //envoi des informations materiau et lumières au shader pour TERRE
          glUniform3f(earthProgram.uKd, 0.3f, 0.f, 0.7f); //couleur diffuse
          glUniform3f(earthProgram.uKs, 0.7f, 1.f, 0.3f); //couleur tache speculaire
          glUniform1f(earthProgram.uShininess, 32);

          //calcul position de la source de lumière
          glm::vec4 positionLightEarth = glm::vec4(3, 0, 0, 1);
          glm::mat4 rotaMatrixLightEarth = glm::rotate(glm::mat4(1.0f),
            glm::radians(windowManager.getTime())*25, glm::vec3(0, 1, 0));
          positionLightEarth = positionLightEarth * rotaMatrixLightEarth;
          positionLightEarth = ViewMatrix * positionLightEarth;

          glUniform3f(earthProgram.uLightPos_vs, positionLightEarth.x,
            positionLightEarth.y, positionLightEarth.z);
          glUniform3f(earthProgram.uLightIntensity, 10, 10, 10);

         glBindVertexArray(vao); //bind vao

         //dessine la sphère
         glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

         moonProgram.m_Program.use();

         //on modifie MVMatrix pour deplacer/shrinker la sphere
         glm::mat4 moonMVMatrix = globalMVMatrix;

         //calcul position de la source lumière
         /*glm::vec4 positionLightMoon = glm::vec4(-1, -1, -1, 1);
         glm::mat4 rotaMatrixLightMoon = glm::mat4(1.0f);
         rotaMatrixLightMoon = glm::rotate(rotaMatrixLightMoon, glm::radians(windowManager.getTime())*25, glm::vec3(0, 1, 0));
         positionLightMoon = positionLightMoon * rotaMatrixLightMoon;
         positionLightMoon = ViewMatrix*positionLightMoon;*/

         glUniform3f(moonProgram.uLightPos_vs, positionLightEarth.x,
           positionLightEarth.y, positionLightEarth.z);
         glUniform3f(moonProgram.uLightIntensity, 8, 8, 8);

         //ça dessine 32 Moons aux axes de rotation différents
         for(int i=0; i < 32; i++) {
           moonMVMatrix = globalMVMatrix;
           moonMVMatrix = glm::rotate(moonMVMatrix, windowManager.getTime(), axes[i]);
           moonMVMatrix = glm::translate(moonMVMatrix, positions[i]);
           moonMVMatrix = glm::scale(moonMVMatrix, glm::vec3(0.2f, 0.2f, 0.2f));

           //envoi des matrices pour LUNES
           glUniformMatrix4fv(moonProgram.uMVMatrix, 1, GL_FALSE,
             glm::value_ptr(moonMVMatrix));
           glUniformMatrix4fv(moonProgram.uMVPMatrix, 1, GL_FALSE,
             glm::value_ptr(ProjMatrix*moonMVMatrix));
           glUniformMatrix4fv(moonProgram.uNormalMatrix, 1, GL_FALSE,
             glm::value_ptr(glm::transpose(glm::inverse(moonMVMatrix))));

             //envoi des information materiau et lumière pour LUNES
             glUniform3f(moonProgram.uKd, materiauxKd[i].x, materiauxKd[i].y, materiauxKd[i].z);
             glUniform3f(moonProgram.uKs,  materiauxKs[i].x, materiauxKs[i].y, materiauxKs[i].z);
             glUniform1f(moonProgram.uShininess, 32);

             //dessine les Moons
           glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
         }

         glBindVertexArray(0); //debind vao

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1, &vbo); //libere espace vbo
    glDeleteVertexArrays(1, &vao); //libere espace vao

    return EXIT_SUCCESS;
}
