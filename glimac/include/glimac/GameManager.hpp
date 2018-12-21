#pragma once

#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>

namespace glimac {

int initialisation();

void startGame(SDLWindowManager &windowManager, const FilePath& applicationPath);


}