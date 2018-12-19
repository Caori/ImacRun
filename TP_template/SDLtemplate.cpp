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
    TrackballCamera t;

    glm::mat4 viewMatrix = glm::mat4(1.f);


    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }

            if(windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT) == true){
                glm:: ivec2 mousePos = windowManager.getMousePosition();
                t.rotateLeft(mousePos.x/400);
                t.rotateUp(mousePos.y/300);
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
	    //***PERSO***
        Personnage personnage("/home/administrateur/Documents/Projet_local/ImacRun/TP_template/SDLtemplate.cpp");
        viewMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2));
        personnage.draw(0, 0, viewMatrix, scene._cube, scene._sphere);


        //transformer vue puis afficher scene***SCENE***
        viewMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -5+1*windowManager.getTime()));
        //viewMatrix = glm::rotate(viewMatrix, glm::radians(5.f), glm::vec3(1, 0, 0));
        viewMatrix = glm::translate(viewMatrix, glm::vec3(-largeur/2, -1, 0));

        float a = 800.0/600.0;
        // glm::perspective(angle_vertical_de_vue, ratio_fenetre, near, far)
        //projMatrix = glm::perspective(glm::radians(70.f),a,0.1f,100.f)*viewMatrix;

        scene.drawScene(viewMatrix);


        // Update the display
        windowManager.swapBuffers();
    }


    return EXIT_SUCCESS;
}
