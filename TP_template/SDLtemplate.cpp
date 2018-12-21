#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <glimac/Exception.hpp>
#include <GL/glew.h>
#include "glimac/GameManager.hpp"
#include "glimac/Game.hpp"


using namespace glimac;

const uint32_t width = 1200;
const uint32_t height = 900;

int main(int argc, char** argv) {
    // Initialize glew for OpenGL3+ support
    SDLWindowManager windowManager(width, height, "IMACRUN");

    FilePath applicationPath(argv[0]);

    //try{
		initialisation();    	
    //}
    //si l'initialisation fail ça return EXIT_FAILURE (false en gros)
    //-->renvoyer exception 

	//ICI MENU	
	//qui return start game si on clic sur start
	startGame(windowManager, applicationPath);

	//dans la fonction startGame (cf. Gamemanager.cpp)  si bool pause ==1 --> afficher pause

    return EXIT_SUCCESS;
}
