#pragma once

#include <glimac/SDLWindowManager.hpp>
#include <glimac/Parameters.hpp>

#include <glimac/Character.hpp>
#include <glimac/Scene.hpp>
#include <glimac/Menu.hpp>
#include "glimac/Model.hpp"
#include "glimac/DirectionalLight.hpp"
#include "glimac/TrackballCamera.hpp"

namespace glimac {
	/*!
	\class Game
	\brief A singleton class used to represent a game session.
	*/
	class Game {
	public:
		SDLWindowManager _windowManager; /**< The current window manager */
		Scene _scene; /**< The current scene with all its objects */
		Character _character; /**< The object controlled by the player */
		Character _foe1,_foe2, _foe3; /**< The enemies */
		TrackballCamera _camera1, _camera2; /**< The trackball camera */
		int _cam;
		bool _done; /**< Used to check if the game is over */
		int _pause; /**< Used to check if the game is open */
		int _menu; /**< Used to check whiwh the menu is paused */
		float _timeTmp; /**< The time passed since the beginning of the game*/
		float _speed; /**< The speed of the player and enemies */

	public:
		Game(const SDLWindowManager& window);

		~Game() {}

		/*!
		* \fn void playGame(const FilePath& applicationPath)
		* \brief Renders the current state of the scene and makes the character, camera and foes move.
		* \param applicationPath Path to main file, cannot be null
		*/
		void playGame(const FilePath& applicationPath);

		/*!
		* \fn void gameEvent()
		* \brief Manages the user input.
		*/
		void gameEvent();

		/*!
		* \fn void gameRendering(const FilePath& applicationPath)
		* \brief Renders the current scene.
		* \param applicationPath Path to main file, cannot be null
		*/
		void gameRendering();
	};
}
