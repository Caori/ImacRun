#include <GL/glew.h>
#include "glimac/Game.hpp"
#include "glimac/SDLWindowManager.hpp"
#include "glimac/TrackballCamera.hpp"
#include <glimac/Parameters.hpp>
#include <glimac/Program.hpp>
#include <iostream>
#include <glimac/Image.hpp>
#include <cmath>

namespace glimac {

	Game::Game(const SDLWindowManager &window)
		:_windowManager(window),
		_scene("map1.ppm"), 
		_character(_scene.getWidth()/2),
		// les 3 nombres en + : décalage hauteur, profondeur et scale pour les ennemis
		_foe1(_scene.getWidth()/2+1, 0.3, -6., 0.6),
		_foe2(_scene.getWidth()/2,  0.3, -6.,  0.7),
		_foe3(_scene.getWidth()/2-1, 0.3, -6.,  0.65),
		_done(false), _pause(0), _speed(Parameters::instance().getSpeed()) {
		glEnable(GL_DEPTH_TEST);
	}	

	void Game::playGame() {
		while(!_done){
			gameEvent();
			_trackballCamera.move(_scene._direction, _speed);
			_character.move(_scene._grid, _speed, _scene._direction);
			_foe1._z+=_speed+0.003*cos(_windowManager.getTime());
			_foe2._z+=_speed+0.003*cos(2+0.8*_windowManager.getTime());;
			_foe3._z+=_speed+0.003*cos(1+0.6*_windowManager.getTime());;
            if(_foe2._z >= _character._z){
                std::cout<<"LOOOOOSE"<<std::endl;
            }
			gameRendering();
		}
	}

    void Game::gameEvent(){
		SDL_Event e;
		while(_windowManager.pollEvent(e)) {
			switch(e.type){
				case SDL_QUIT:
					_done = true; // Leave the loop after this iteration
					break;

				case SDL_KEYDOWN:
					if(_windowManager.isKeyPressed(SDLK_q) == true){
						_character.moveLeft(_scene._grid, _scene._posX, _scene._posZ, _scene._direction);
					}
    	           	if(_windowManager.isKeyPressed(SDLK_d) == true){
    	           		_character.moveRight(_scene._grid, _scene._posX, _scene._posZ, _scene._direction);
    	           	}
    	           	if(_windowManager.isKeyPressed(SDLK_s) == true){
                        if (_character._isCrouched == 0){
                            _timeTmp = _windowManager.getTime();
    	                    _character._scale = 0.5;
                            _character._y -=0.3;
                            _character._isCrouched = 1;
                        }
                    }
                    if(_windowManager.isKeyPressed(SDLK_z) == true){
    	                _character._jump = 1;
    	            }
                    if(_windowManager.isKeyPressed(SDLK_SPACE) == true){
                        if (_pause==0){_pause=1;}
                        else {_pause=0;}
                        _speed = 0.03*(1-_pause);
                    }
                    break;

                default:
                	break;	          
            } 	
        }

        if (_character._isCrouched){
            if (_windowManager.getTime() - _timeTmp > 0.65){
                _character._isCrouched = 0;
                _character._scale = 1.;
                _character._y +=0.3;
            }
        }
    }

    void Game::gameRendering(){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Program _Program(loadProgram(Parameters::instance().appPath().dirPath() + "shaders/3D.vs.glsl",
                Parameters::instance().appPath().dirPath() + "shaders/directionallight.fs.glsl"));
            _Program.use();

        glm::mat4 viewMatrix = _trackballCamera.getViewMatrix();
        viewMatrix = glm::translate(viewMatrix, glm::vec3(0, -4.f, -5.f));
        _character.draw(0, 0, viewMatrix, _scene._cube, _scene._sphere, _windowManager);
        _foe1.draw(0, 0, viewMatrix, _scene._cube, _scene._sphere, _windowManager);
        _foe2.draw(0, 0, viewMatrix, _scene._cube, _scene._sphere, _windowManager);
        _foe3.draw(0, 0, viewMatrix, _scene._cube, _scene._sphere, _windowManager);

        _scene.drawScene(viewMatrix, _windowManager);

        _windowManager.swapBuffers();
    }
}