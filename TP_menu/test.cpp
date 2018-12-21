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


	mainMenu.initializeMenu(windowManager,"/home/administrateur/Documents/Projet/ImacRun/assets/menu/Menu-player.png");

	return EXIT_SUCCESS;
}