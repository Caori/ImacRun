#pragma once

#include <glimac/Character.hpp>
#include <glimac/Scene.hpp>
#include <glimac/SDLWindowManager.hpp>
#include "glimac/Model.hpp"
#include <vector>

namespace glimac {
	/*!
	\class Game
	\brief A singleton class used to represent a game session.
	*/
	class Game {
	public:
		SDLWindowManager _windowManager; /**< The current window manager */
		Scene _scene; /**< The current scene with all its objects */
		Player _player; /**< The object controlled by the player */
		std::vector<Foe*> _foes; /**< The enemies */
		TrackballCamera _camera1, _camera2; /**< The trackball camera */
		int _cam;
		bool _done; /**< Used to check if the game is over */
		bool _pause; /**< Used to check if the game is paused */
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
		void playGame();

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