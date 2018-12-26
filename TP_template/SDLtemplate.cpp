#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <glimac/Exception.hpp>
#include <GL/glew.h>
#include "glimac/GameManager.hpp"
#include "glimac/Game.hpp"

/*! \namespace glimac
    \brief A namespace with all the classes used in the program.
*/
using namespace glimac;

const uint32_t width = 800;
const uint32_t height = 600;

int main(int argc, char** argv) {
    // Initialize glew for OpenGL3+ support
    SDLWindowManager windowManager(width, height, "IMACRUN");

    FilePath applicationPath(argv[0]);

    try{
		initialisation();    	
    }
    catch (const Exception &e) {
        std::cerr << e.what() <<std::endl;
    }

	startGame(windowManager, applicationPath);

	//dans la fonction startGame (cf. Gamemanager.cpp)  si bool pause ==1 --> afficher pause

    return EXIT_SUCCESS;
}
