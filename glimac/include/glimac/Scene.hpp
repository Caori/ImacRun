#include <vector>
#include <GL/glew.h>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Object.hpp>
#include <glimac/Ground.hpp>
#include <glimac/TrackballCamera.hpp>

namespace glimac {

class Scene{
	public:
		/*
		Light _lights[];
		Camera _cams[];*/
		TrackballCamera _trackCam;

		//std::vector<Object*> _objects;
		Cube _cube;
		Sphere _sphere;

		std::vector< std::vector<int>> _grid;

	public:
		//Constructeur et destructeurs
		Scene();
		~Scene(){}
        
		std::vector< std::vector<int>> readPPM();

		int getLargeur(){
			return _grid[0].size();
		}

		void drawScene(glm::mat4 &viewMatrix /*,Camera &camera*/);
		/*
		void draw1(int i, int j, glm::mat4 &viewMatrix, glm::mat4 &projMatrix, Cube &cube, GLint &locationuMVMatrix, GLint &locationuMVPMatrix, GLint &locationuNormalMatrix);
		void draw2(int i, int j, glm::mat4 &viewMatrix, glm::mat4 &projMatrix, Cube &cube, Sphere &sphere, GLint &locationuMVMatrix, GLint &locationuMVPMatrix, GLint &locationuNormalMatrix);
		void draw5(int i, int j, glm::mat4 &viewMatrix, glm::mat4 &projMatrix, Cube &cube, GLint &locationuMVMatrix, GLint &locationuMVPMatrix, GLint &locationuNormalMatrix);
		*/
};


}
