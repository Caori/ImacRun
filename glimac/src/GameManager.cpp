#include <glimac/SDLWindowManager.hpp>
#include "glimac/GameManager.hpp"
#include "glimac/Exception.hpp"
#include <GL/glew.h>
#include "glimac/Game.hpp"
#include "glimac/AssetLoader.hpp"

namespace glimac {

int initialisation(){
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        THROW_EXCEPTION("Failed to load GLEW library.");
        return EXIT_FAILURE;
    }

    if(TTF_Init() == 1){
        std::cerr << TTF_GetError() << std::endl;
        THROW_EXCEPTION("Failed to load SDL_ttf library");
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
}

void startGame(SDLWindowManager &windowManager, const FilePath& applicationPath){
    AssetLoader& assetLoader = AssetLoader::instance();
	Game game(windowManager);
    game.playGame(applicationPath);
}

}