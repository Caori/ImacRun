#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <glimac/shader130Manager.hpp>
#include <glimac/Menu.hpp>

using namespace glimac;

int main(int argc, char** argv) {
	// Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");
	 // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

	Menu mainMenu("/home/administrateur/Documents/Projet/ImacRun/TP_menu/test.cpp");

	// initialize textures
	GLuint texture = mainMenu.loadTexture("/home/administrateur/Documents/Projet/ImacRun/assets/menu/Menu-player.png");

	bool done = false;
	while(!done){
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
                    if(mousePosY >= 120 && mousePosY <= 220){
                        std::cout << "Let's go !" << std::endl;
                    }
                }
            }
        }
        mainMenu.displayMenu(windowManager, &texture);
        windowManager.swapBuffers();
    }
    glDeleteTextures(1,(GLuint*)(&texture));
	return EXIT_SUCCESS;
}