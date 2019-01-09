#include <GL/glew.h>
#include "glimac/Game.hpp"
#include "glimac/SDLWindowManager.hpp"
#include "glimac/TrackballCamera.hpp"
#include <glimac/Parameters.hpp>
#include <glimac/Program.hpp>
#include <iostream>
#include <glimac/Image.hpp>
#include <glimac/DirectionalLight.hpp>
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
        _camera1(TrackballCamera()),
        _camera2(TrackballCamera(0, 0, 1.5)),
        _cam(2),
		_done(false), _pause(2), _menu(0), _speed(Parameters::instance().getSpeed()) {
		glEnable(GL_DEPTH_TEST);
	}	

	void Game::playGame(const FilePath& applicationPath) {
         Menu menus(applicationPath);
        GLuint menuBackgrounds = menus.loadTexture(applicationPath.dirPath() + "../../ImacRun/assets/menu/Menu-player.png",
            applicationPath.dirPath() + "../../ImacRun/assets/menu/Menu-pause.png", 
            applicationPath.dirPath() + "../../ImacRun/assets/menu/Menu-gameover.png");

		while(!_done){
			gameEvent();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

           if(_pause == 2){
                menus.displayMenu(_windowManager, &menuBackgrounds, 0);
                //_menu = 0;
            }

           if(_character._isAlive == 1){
                menus.displayMenu(_windowManager, &menuBackgrounds, 2);
                _pause = 3;
                _menu = 2;
            }

           if(_pause == 1){
                menus.displayMenu(_windowManager, &menuBackgrounds, 1);
                _menu = 1;
            }

            if(_pause == 0){
    			_camera1.move(_scene._direction, _speed);
                _camera2.setDistance(-_character._z-1);
                _camera2.setLeft(_character._x-50);
                _camera2.setUp(_character._y+0.5);
    			_character.move(_scene._grid, _speed, _scene._direction);
    			_foe1._z+=_speed+0.003*cos(_windowManager.getTime());
    			_foe2._z+=_speed+0.003*cos(2+0.8*_windowManager.getTime());;
    			_foe3._z+=_speed+0.003*cos(1+0.6*_windowManager.getTime());;
                if(_foe2._z >= _character._z){
                    std::cout<<"LOOOOOSE"<<std::endl;
                }
    			gameRendering();
            }
            _windowManager.swapBuffers();
		}
        glDeleteTextures(3,(GLuint*)(&menuBackgrounds));
        /*glDeleteTextures(1, (GLuint*)(&scoreTexture));
        TTF_CloseFont(font);
        TTF_Quit();*/
	}

    void Game::gameEvent(){
		SDL_Event e;
        glm::ivec2 mousePosition = _windowManager.getMousePosition();
        float mousePosX = mousePosition.x;
        float mousePosY = mousePosition.y;

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
                        _speed = Parameters::instance().getSpeed()*(1-_pause);
                    }
                    if(_windowManager.isKeyPressed(SDLK_c) == true){
                        if (_cam==1){_cam=2;}
                        else{
                            _cam=1;
                        }
                    }
                    break;

                // Menus : 0 = main menu, 1 = pause, 2 = game over
                case SDL_MOUSEBUTTONDOWN:
                    if(_menu == 0){
                        if(_windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT) == true){
                            
                            // bouton width : 400 px
                            if(mousePosX >= 300 && mousePosX <= 900){
                                // leave
                                if(mousePosY >= 380 && mousePosY <= 530){
                                    _done = true;
                                }
                                // play
                                if(mousePosY >= 180 && mousePosY <= 330){
                                    _pause = 0;
                                }
                            }
                        }
                    }
                   if(_menu == 1){
                        if(_windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT) == true){
                            if(mousePosX >=300 && mousePosX <= 900
                                && mousePosY >= 380 && mousePosY <= 530){
                                _pause = 0;
                                _speed = 0.1*(1-_pause);
                            }
                        }
                    }
                    if(_menu == 2){
                        if(_windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT) == true){
                            if(mousePosX >=300 && mousePosX <= 900
                                && mousePosY >= 380 && mousePosY <= 530){
                                _done = true;
                            }
                        }
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
        
        Program _Program(loadProgram(Parameters::instance().appPath().dirPath() + "shaders/3D.vs.glsl",
                Parameters::instance().appPath().dirPath() + "shaders/directionallight.fs.glsl"));
        _Program.use();
        glm::mat4 viewMatrix;
        if (_cam==1){
            viewMatrix = _camera1.getViewMatrix();
            _character.draw(0, 0, viewMatrix, _windowManager);
        }
        else{
            viewMatrix = _camera2.getViewMatrix();
        }
        DirectionalLight light;
        light.drawLight(viewMatrix, glm::vec4(0.5f, 1, 1, 0));

        _foe1.draw(0, 0, viewMatrix, _windowManager);
        _foe2.draw(0, 0, viewMatrix, _windowManager);
        _foe3.draw(0, 0, viewMatrix, _windowManager);

        _scene.drawScene(viewMatrix, _windowManager);
    }
}