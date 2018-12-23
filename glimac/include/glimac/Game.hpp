#pragma once

#include <glimac/Character.hpp>
#include <glimac/Scene.hpp>
#include <glimac/SDLWindowManager.hpp>

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
		TrackballCamera _trackballCamera; /**< The trackball camera */
		bool _done; /**< Used to check if the game is over */
		bool _pause; /**< Used to check if the game is paused */
		float _timeTmp; /**< The time passed since the beginning of the game*/
		float _speed; /**< The speed of the player and enemies */

	public:
		Game(const SDLWindowManager& window, const FilePath& applicationPath);

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
		void gameRendering(const FilePath& applicationPath);
	};
}