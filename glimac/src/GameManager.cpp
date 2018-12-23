#include <glimac/SDLWindowManager.hpp>
#include "glimac/GameManager.hpp"
#include "glimac/Exception.hpp"
#include <GL/glew.h>
#include "glimac/Game.hpp"

namespace glimac {

int initialisation(){
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        THROW_EXCEPTION("Failed to load GLEW library.");
        return EXIT_FAILURE;
    }
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
}

void startGame(SDLWindowManager &windowManager, const FilePath& applicationPath){
	Game game(windowManager, applicationPath);
    game.playGame(applicationPath);
    //if _pause == 1 --> afficher pause

}

}