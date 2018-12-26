#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>
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

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){
        std::cerr << "Mix_OpenAudio error " << std::endl;
    }
    Mix_VolumeMusic(MIX_MAX_VOLUME);
    Mix_Music *mainMusic;
    mainMusic = Mix_LoadMUS("/home/administrateur/Téléchargements/Game2/ImacRun/assets/music/Atmospheric_Pressure.mp3");
    Mix_PlayMusic(mainMusic, -1);

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
}

void startGame(SDLWindowManager &windowManager, const FilePath& applicationPath){
	Game game(windowManager, applicationPath);
    game.playGame(applicationPath);
}

}