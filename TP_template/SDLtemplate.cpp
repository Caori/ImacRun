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

	Personnage personnage("/home/jarcet/Bureau/Projet OpenGL/Projet_SI_local/ImacRun/TP_template/SDLtemplate.cpp", scene.getLargeur()/2);

    glEnable(GL_DEPTH_TEST);

    // création TrackballCamera
    TrackballCamera t;

    glm::mat4 viewMatrix = glm::mat4(1.f);


    // Application loop:
    bool done = false;
    float timeTmp;
    bool pause = 1;
    float speed = 0.03*pause;

    while(!done) {
    	
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
        	switch(e.type){
        		case SDL_QUIT:
        			done = true; // Leave the loop after this iteration
        			break;

        		case SDL_KEYDOWN:
        			if(windowManager.isKeyPressed(SDLK_q) == true){
		           		personnage.moveLeft(scene._grid, scene._posX, scene._posZ, scene._direction);
		           	}
		           	if(windowManager.isKeyPressed(SDLK_d) == true){
		           		personnage.moveRight(scene._grid, scene._posX, scene._posZ, scene._direction);
		           	}
		           	if(windowManager.isKeyPressed(SDLK_s) == true){
                        if (personnage._isCrouched == 0){
                            timeTmp = windowManager.getTime();
    	                    personnage._scale = 0.5;
                            personnage._y -=0.3;
                            personnage._isCrouched = 1;
                        }
	                }
	                if(windowManager.isKeyPressed(SDLK_z) == true){
		                personnage._jump = 1;
		            }
                    if(windowManager.isKeyPressed(SDLK_SPACE) == true){
                        if (pause==0){pause=1;}
                        else {pause=0;}
                        speed = 0.03*pause;
                    }
	                break;

	            default:
	            	break;	          
            }
           	
           	if(windowManager.isKeyPressed(SDLK_UP) == true){
           		scene._posZ+=10;
           	}
            if(windowManager.isKeyPressed(SDLK_DOWN) == true){
                scene._posZ-=10;
            }
           	if(windowManager.isKeyPressed(SDLK_LEFT) == true){
           		scene._posX-=10;
           	}
            if(windowManager.isKeyPressed(SDLK_RIGHT) == true){
                scene._posX+=10;
            }
           	
        }

        if (personnage._isCrouched){
            if (windowManager.getTime() - timeTmp > 0.65){
                personnage._isCrouched = 0;
                personnage._scale = 1.;
                personnage._y +=0.3;
            }
        }
        

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        if (scene._direction == "NORD"){
            t.moveFront(-speed);
        }
        if (scene._direction == "SUD"){
            t.moveFront(+speed);
        }
        if (scene._direction == "OUEST"){
            t.moveFront(+speed);
        }
        if (scene._direction == "EST"){
            t.moveFront(-speed);
        }

        //ici check collision
        personnage.move(scene._grid, speed, scene._direction);
        //personnage.moveFront(+0.01);


        viewMatrix = t.getViewMatrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       

        //transformer vue
       viewMatrix = glm::translate(viewMatrix, glm::vec3(0, -4.f, -5.f));
     
        //***PERSO***
        personnage.draw(0, 0, viewMatrix, scene._cube, scene._sphere);


        //***SCENE***
        scene.drawScene(viewMatrix);


        // Update the display
        windowManager.swapBuffers();
    }


    return EXIT_SUCCESS;
}
