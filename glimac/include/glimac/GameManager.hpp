#pragma once

#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>

namespace glimac {
	/*!
	* \fn int initialisation()
	* \brief Initialize the GLEW library
	* \return Success status
	*/
	int initialisation();

	/*!
	* \fn startGame(SDLWindowManager &windowManager, const FilePath& applicationPath)
	* \brief Initialize the game and launches it
	* \param windowManager Reference to the windw manager
	* \param applicationPath Reference to the main file path
	*/
	void startGame(SDLWindowManager& windowManager, const FilePath& applicationPath);
}