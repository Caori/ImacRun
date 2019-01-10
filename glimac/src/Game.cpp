#include <GL/glew.h>
#include "glimac/Game.hpp"
#include "glimac/SDLWindowManager.hpp"
#include "glimac/TrackballCamera.hpp"
#include "glimac/Character.hpp"
#include <glimac/Parameters.hpp>
#include <glimac/Program.hpp>
#include <iostream>
#include <glimac/Image.hpp>
#include <cmath>
#include <vector>
#include <algorithm>

namespace glimac {

	Game::Game(const SDLWindowManager &window)
		:_windowManager(window),
		_scene("map1.ppm"), 
		_player(_scene.getWidth()/2),
        _camera1(TrackballCamera()),
        _camera2(TrackballCamera(0, 0, 1.5)),
        _cam(2),
		_done(false), _pause(0), _speed(Parameters::instance().getSpeed()) 
        {
            _foes.push_back(new Foe(_scene.getWidth()/2+1, 0.3, -6., 0.6)); 
            _foes.push_back(new Foe(_scene.getWidth()/2, 0.3, -6., 0.7)); 
            _foes.push_back(new Foe(_scene.getWidth()/2-1, 0.3, -6., 0.65)); 
    		glEnable(GL_DEPTH_TEST);
	}	

    Game::~Game(){
        for_each(_foes.begin(), _foes.end(), [&](Foe* foe){delete(foe);});
    }

	void Game::playGame() {
		while(!_done){
			gameEvent();
			_camera1.move(_scene._direction, _speed);
            _camera2.setDistance(-_player.getZ()-1);
            _camera2.setLeft(_player.getX()-50);
            _camera2.setUp(_player.getY()+0.5);
			_player.move(_scene._grid, _speed, _scene._direction);
            for_each(_foes.begin(), _foes.end(), [&](Foe* foe){foe->setZ(foe->getZ()+_speed);});
			/*_foe1.setZ(foe1.getZ()+_speed+0.003*cos(_windowManager.getTime()));
			_foe2._z+=_speed+0.003*cos(2+0.8*_windowManager.getTime());;
			_foe3._z+=_speed+0.003*cos(1+0.6*_windowManager.getTime());;*/
            if(_foes[1]->getZ() >= _player.getZ()){
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
						_player.moveLeft(_scene._grid, _scene._posX, _scene._posZ, _scene._direction);
					}
    	           	if(_windowManager.isKeyPressed(SDLK_d) == true){
    	           		_player.moveRight(_scene._grid, _scene._posX, _scene._posZ, _scene._direction);
    	           	}
    	           	if(_windowManager.isKeyPressed(SDLK_s) == true){
                        if (_player._isCrouched == 0){
                            _timeTmp = _windowManager.getTime();
    	                    _player.setScale(0.5);
                            _player.setY(_player.getY() -0.3);
                            _player._isCrouched = 1;
                        }
                    }
                    if(_windowManager.isKeyPressed(SDLK_z) == true){
    	                _player._jump = 1;
    	            }
                    if(_windowManager.isKeyPressed(SDLK_SPACE) == true){
                        if (_pause==0){_pause=1;}
                        else {_pause=0;}
                        _speed = Parameters::instance().getSpeed()*(1-_pause);
                    }
                    if(_windowManager.isKeyPressed(SDLK_c) == true){
                        if (_cam==1){_cam=2;}
                        else{
                            _cam=1;
                        }
                    }
                    break;

                default:
                	break;	          
            } 	
        }

        if (_player._isCrouched){
            if (_windowManager.getTime() - _timeTmp > 0.65){
                _player._isCrouched = 0;
                _player.setScale(1.);
                _player.setY(_player.getY()+0.3);
            }
        }
    }

    void Game::gameRendering(){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Program _Program(loadProgram(Parameters::instance().appPath().dirPath() + "shaders/3D.vs.glsl",
                Parameters::instance().appPath().dirPath() + "shaders/directionallight.fs.glsl"));
        _Program.use();
        glm::mat4 viewMatrix;
        if (_cam==1){
            viewMatrix = _camera1.getViewMatrix();
            _player.draw(0, 0, viewMatrix, _scene._cube, _scene._sphere, _windowManager);
        }
        else{
            viewMatrix = _camera2.getViewMatrix();
        }
        for_each(_foes.begin(), _foes.end(), [&](Foe* foe){foe->draw(0, 0, viewMatrix, _scene._cube, _scene._sphere, _windowManager);});
        _scene.drawScene(viewMatrix, _windowManager);

        _windowManager.swapBuffers();
    }
}