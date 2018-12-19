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

	Personnage personnage("/chemin/ImacRun/TP_template/SDLtemplate.cpp", scene.getLargeur()/2);

    glEnable(GL_DEPTH_TEST);

    // création TrackballCamera
    TrackballCamera t;

    glm::mat4 viewMatrix = glm::mat4(1.f);

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
           		personnage.moveLeft(scene._grid);
           	}
           	if(windowManager.isKeyPressed(SDLK_d) == true){
           		personnage.moveRight(scene._grid);
           	}
           	/*
           	if(windowManager.isKeyPressed(SDLK_LEFT) == true){
           		rotation +=10.f;
           		scene._rotationMatrix = glm::rotate(glm::mat4(1.f), glm::radians(rotation), glm::vec3(0,1,0));
           		std::cout<<"rotation globale : "<<rotation<<std::endl;
           	}
           	if(windowManager.isKeyPressed(SDLK_RIGHT) == true){
           		rotation -=10.f;
           		scene._rotationMatrix = glm::rotate(glm::mat4(1.f), glm::radians(rotation), glm::vec3(0,1,0));
           	}
           	*/
        }
        

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        t.moveFront(-0.1);

        //ici check collision
        personnage.moveFront(scene._grid);

        // hole
        int isFall = personnage.fall(scene._grid);
        if(isFall == 1){
            personnage._y -= 0.5;
        }
        
        //personnage.moveFront(+0.01);


        viewMatrix = t.getViewMatrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.f), glm::radians(rotation), glm::vec3(0,1,0));
	    

        //transformer vue puis afficher scene***SCENE***
        //viewMatrix = glm::rotate(viewMatrix, glm::radians(rotation), glm::vec3(0,1,0));
        viewMatrix = glm::translate(viewMatrix, glm::vec3(0, -4.f, -5.f));
        scene.drawScene(viewMatrix);


		//***PERSO***
        //viewMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0, -0.3, -2))*rotationMatrix;
        personnage.draw(0, 0, viewMatrix, rotationMatrix, scene._cube, scene._sphere);


        // Update the display
        windowManager.swapBuffers();
    }


    return EXIT_SUCCESS;
}
