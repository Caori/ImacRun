#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <glimac/Scene.hpp>
#include <glimac/Exception.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Personnage.hpp>
#include <glimac/TrackballCamera.hpp>
#include <GL/glew.h>
#include <iostream>


using namespace glimac;

const uint32_t width = 800;
const uint32_t height = 600;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(width, height, "ImacRun");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;



    
    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    Scene scene;

	int largeur = scene.getLargeur()/2;


    glEnable(GL_DEPTH_TEST);


    // création TrackballCamera
    TrackballCamera tBCamera;


    glm::ivec2 vieillePosition = windowManager.getMousePosition();
    // Application loop:
    bool done = false;
    float rotation;

    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }

            if(windowManager.isKeyPressed(SDLK_q) == true){
           		rotation +=90.f;
           		scene._rotationMatrix = glm::rotate(glm::mat4(1.f), glm::radians(rotation), glm::vec3(0,1,0));
           		std::cout<<"rotation globale : "<<rotation<<std::endl;
           	}
           	if(windowManager.isKeyPressed(SDLK_d) == true){
           		rotation -=90.f;
           		scene._rotationMatrix = glm::rotate(glm::mat4(1.f), glm::radians(rotation), glm::vec3(0,1,0));
           	}

           	if(windowManager.isKeyPressed(SDLK_DOWN)) {
              tBCamera.moveFront(1);
            }
            if(windowManager.isKeyPressed(SDLK_UP)) {
                tBCamera.moveFront(- 1);
            }
            if(windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
              glm::ivec2 newPosition = windowManager.getMousePosition();
              float deplacementX = vieillePosition.x - newPosition.x;
              float deplacementY = vieillePosition.y - newPosition.y;
              //si souris bouge horizontalement
              if(deplacementX != 0) {
                 tBCamera.rotateLeft(glm::radians(-0.01*deplacementX));
               }
              //si souris bouge verticalement
              if(deplacementY != 0) {
                tBCamera.rotateUp(glm::radians(-0.01*deplacementY));
              }
            }

        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
		glm::mat4 viewMatrix = tBCamera.getViewMatrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.f), glm::radians(rotation), glm::vec3(0,1,0));
	    

        //transformer vue puis afficher scene***SCENE***
        //viewMatrix = glm::rotate(viewMatrix, glm::radians(rotation), glm::vec3(0,1,0));
        //viewMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0, -0.f, -1.f));
 
        //viewMatrix = glm::translate(glm::mat4(1.f), glm::vec3(-largeur/2, -1.3, -7+windowsManager.getTime()));

        scene.drawScene(viewMatrix);


		//***PERSO***
        Personnage personnage("/home/jarcet/Bureau/Projet OpenGL/Projet_SI_local/ImacRun/TP_template/SDLtemplate.cpp");
        //viewMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0, -0.3, -2))*rotationMatrix;
        personnage.draw(0, 0, viewMatrix, rotationMatrix, scene._cube, scene._sphere);


        // Update the display
        windowManager.swapBuffers();
    }


    return EXIT_SUCCESS;
}
