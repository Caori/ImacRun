#include <GL/glew.h>
#include "glimac/Game.hpp"
#include "glimac/SDLWindowManager.hpp"
#include "glimac/TrackballCamera.hpp"
#include "glimac/FreeflyCamera.hpp"
#include <iostream>
#include <glimac/Image.hpp>
#include <cmath>

namespace glimac {

	Game::Game(const SDLWindowManager &window, const FilePath& applicationPath)
		:_windowManager(window),
		_scene("map1.ppm", applicationPath), 
		_character(applicationPath, _scene.getWidth()/2),
		// les 3 nombres en + : décalage hauteur, profondeur et scale pour les ennemis
		_foe1(applicationPath, _scene.getWidth()/2+1, 0.3, -6., 0.6),
		_foe2(applicationPath, _scene.getWidth()/2,  0.3, -6.,  0.7),
		_foe3(applicationPath, _scene.getWidth()/2-1, 0.3, -6.,  0.65),
		_done(false), _pause(2), _menu(0), _camera(0), _speed(0.1) {
		glEnable(GL_DEPTH_TEST);
	}	

	void Game::playGame(const FilePath& applicationPath) {
        // main menu
        Menu menus(applicationPath);
        GLuint menuBackgrounds = menus.loadTexture(applicationPath.dirPath() + "../../ImacRun/assets/menu/Menu-player.png", applicationPath.dirPath() + "../../ImacRun/assets/menu/Menu-pause.png", applicationPath.dirPath() + "../../ImacRun/assets/menu/Menu-gameover.png");

        glm::mat4 viewMatrix = glm::mat4(1.f);

		while(!_done){
			gameEvent();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // collision character et ennemi (foe)
            if( _foe2._z == _character._z){
                _character._isAlive = 1;
                std::cout << "Vous avez été tué par l'ennemi" << std::endl;
            }

            // fonctionne
           if(_pause == 2){
                menus.displayMenu(_windowManager, &menuBackgrounds, 0);
                //_menu = 0;
            }

            // fonctionne quand gameRendering mis en commentaire
            if(_character._isAlive == 1 || _character._isFalling == 1){
                //std::cout << "Alive = " << _character._isAlive << std::endl;
                menus.displayMenu(_windowManager, &menuBackgrounds, 2);
                _pause = 3;
                _menu = 2;
            }

            // fonctionne quand gameRendering mis en commentaire
            if(_pause == 1){
                menus.displayMenu(_windowManager, &menuBackgrounds, 1);
                _menu = 1;
            }
            
            if(_pause == 0){
                //std::cout << "camera value = " << _camera << std::endl;
                std::cout << "foe2.z = " << _foe2._z << std::endl;
                std::cout << "character.z = " << _character._z << std::endl;

    		    _trackballCamera.move(_scene._direction, _speed);
                _freeflyCamera.move(_scene._direction, _speed);
    		    _character.move(_scene._grid, _speed, _scene._direction);
    		    _foe1._z+=_speed+0.003*cos(_windowManager.getTime());
    		    _foe2._z+=_speed;
    		    _foe3._z+=_speed+0.003*cos(1+0.6*_windowManager.getTime());;

                
                // changement de caméra : touche C détectée mais il ne se passe rien
                if(_camera == 0){
                    viewMatrix = _trackballCamera.getViewMatrix();
                }
                if(_camera == 1){
                    viewMatrix = _freeflyCamera.getViewMatrix();
                }

                gameRendering(applicationPath, viewMatrix);
            }
            _windowManager.swapBuffers();
		}
        glDeleteTextures(3,(GLuint*)(&menuBackgrounds));
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
                        _speed = 0.1*(1-_pause);
                    }
                    if(_windowManager.isKeyPressed(SDLK_c) == true){
                        if(_camera == 0){
                            _camera == 1;
                            std::cout << "TOUCHE C" << std::endl;
                        }
                        else{
                            _camera == 0;
                            std::cout << "Passage à 0" << std::endl;
                        }
                    }
                    break;

                // Menus : 0 = main menu, 1 = pause, 2 = game over
                case SDL_MOUSEBUTTONDOWN:
                    if(_menu == 0){
                        if(_windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT) == true){
                            
                            // bouton width : 400 px
                            if(mousePosX >= 200 && mousePosX <= 600){
                                // leave
                                if(mousePosY >= 250 && mousePosY <= 350){
                                    _done = true;
                                }
                                // play
                                if(mousePosY >= 120 && mousePosY <= 220){
                                    _pause = 0;
                                }
                            }
                        }
                    }
                   if(_menu == 1){
                        if(_windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT) == true){
                            if(mousePosX >=200 && mousePosX <= 600
                                && mousePosY >= 250 && mousePosY <= 350){
                                _pause = 0;
                                _speed = 0.1*(1-_pause);
                            }
                        }
                    }
                    if(_menu == 2){
                        if(_windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT) == true){
                            if(mousePosX >=200 && mousePosX <= 600
                                && mousePosY >= 250 && mousePosY <= 350){
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

    void Game::gameRendering(const FilePath& applicationPath, glm::mat4 viewMatrix){
        
       //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      //glm::mat4 viewMatrix = _trackballCamera.getViewMatrix();
        viewMatrix = glm::translate(viewMatrix, glm::vec3(0, -4.f, -5.f));
        _character.draw(0, 0, viewMatrix, _scene._cube, _scene._sphere, _windowManager);
        _foe1.draw(0, 0, viewMatrix, _scene._cube, _scene._sphere, _windowManager);
        _foe2.draw(0, 0, viewMatrix, _scene._cube, _scene._sphere, _windowManager);
        _foe3.draw(0, 0, viewMatrix, _scene._cube, _scene._sphere, _windowManager);

        _scene.drawScene(viewMatrix, applicationPath, _windowManager);

       // _windowManager.swapBuffers();
    }
}