#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <glimac/Scene.hpp>
#include <glimac/Exception.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/TrackballCamera.hpp>
#include <GL/glew.h>
#include <iostream>

using namespace glimac;

const uint32_t width = 800;
const uint32_t height = 600;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(width, height, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

	FilePath applicationPath(argv[0]);
    /*Program program = loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                                  applicationPath.dirPath() + "shaders/normals.fs.glsl");
    program.use();

    // Récupération de la location des uniformes
    GLint uMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
**/
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    //Ground ground("/home/6im2/ejarcet/Bureau/Projet OpenGL/Projet_SI_local/ImacRun/TP_template/SDLtemplate.cpp");
    Scene scene;

	int largeur = scene.getLargeur()/2;

    glEnable(GL_DEPTH_TEST);

    // création TrackballCamera
    TrackballCamera t;

    glm::mat4 projMatrix,MVMatrix,NormalMatrix;


    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXCOORDS = 2;
    GLuint vbo2, vao2;




    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }

            if(windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT) == true){
                glm:: ivec2 mousePos = windowManager.getMousePosition();
                t.rotateLeft(mousePos.x/400);
                t.rotateUp(mousePos.y/300);
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // trackball
        glm::mat4 viewMatrix = glm::translate(glm::rotate(glm::mat4(1.f), glm::radians(5.f), glm::vec3(1, 0, 0)), glm::vec3(-largeur/2, -3, -5));

        float a = 800.0/600.0;
        // glm::perspective(angle_vertical_de_vue, ratio_fenetre, near, far)
        //projMatrix = glm::perspective(glm::radians(70.f),a,0.1f,100.f)*viewMatrix;

        scene.drawScene(viewMatrix);


        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1,&vbo2);
    glDeleteVertexArrays(1,&vao2);

    return EXIT_SUCCESS;
}
