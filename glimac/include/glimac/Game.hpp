#pragma once

#include <glimac/Character.hpp>
#include <glimac/Scene.hpp>
#include <glimac/SDLWindowManager.hpp>

namespace glimac {

class Game{
	public:
		SDLWindowManager _windowManager;
		Scene _scene;
		Character _character;
		TrackballCamera _trackballCamera;
		bool _done;
		bool _pause;
		float _timeTmp;
		float _speed;

	public:
		Game(const SDLWindowManager &window, const FilePath& applicationPath);
		~Game(){}

		void playGame(const FilePath& applicationPath);
		void gameEvent();
		void gameRendering(const FilePath& applicationPath);
};

}