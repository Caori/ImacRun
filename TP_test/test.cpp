#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glimac/common.hpp>
#include <glimac/Cube.hpp>
#include <glimac/TrackballCamera.hpp>

/********************************
IF YOU'RE USING GLSL VERSION 130
DELETE THIS PART IF YOU'RE VERSION 330
********************************/
std::string readFile(const char *filePath) {
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

GLuint LoadShader(const char *vertex_path, const char *fragment_path) {
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Read shaders
    std::string vertShaderStr = readFile(vertex_path);
    std::string fragShaderStr = readFile(fragment_path);
    const char *vertShaderSrc = vertShaderStr.c_str();
    const char *fragShaderSrc = fragShaderStr.c_str();

    GLint result = GL_FALSE;
    int logLength;


    // Compile vertex shader
    std::cout << "Compiling vertex shader." << std::endl;
    glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShader);

    // Check vertex shader
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> vertShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
    std::cout << &vertShaderError[0] << std::endl;

    // Compile fragment shader
    std::cout << "Compiling fragment shader." << std::endl;
    glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShader);

    // Check fragment shader
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> fragShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
    std::cout << &fragShaderError[0] << std::endl;

    std::cout << "Linking program" << std::endl;
    GLuint program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);

    glBindAttribLocation(program, 0, "position");
    glBindAttribLocation(program, 1, "normal");
    glBindAttribLocation(program, 2, "textCoords");

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> programError( (logLength > 1) ? logLength : 1 );
    glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
    std::cout << &programError[0] << std::endl;  

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return program;
}
/********************************
END - IF YOU'RE USING GLSL VERSION 130
********************************/

using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    // chargement et utilisation des shaders
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/3D_130.vs.glsl",
                                  applicationPath.dirPath() + "shaders/normals.fs.glsl");
    program.use();

    // Récupération de la location des uniformes
    GLint locationuMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint locationuMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint locationuNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    // activation du test de profondeur du GPU
    glEnable(GL_DEPTH_TEST);

    // création TrackballCamera
    TrackballCamera t;

    glm::mat4 projMatrix,MVMatrix,NormalMatrix;

    Cube cube(2);
    int nbVertex = 36;
     //std::cout << "Nombre de sommets : " << nbVertex << std::endl; 
     
     GLuint vbo, vao;

     glGenBuffers(1, &vbo);
     glBindBuffer(GL_ARRAY_BUFFER, vbo); //bind buffer vbo sur cible

     //envoi des données
     glBufferData(GL_ARRAY_BUFFER, nbVertex*sizeof(ShapeVertex), cube.getDataPointer(),
      GL_STATIC_DRAW);
     glBindBuffer(GL_ARRAY_BUFFER, 0); //debind vbo

     glGenVertexArrays(1, &vao);

     glBindVertexArray(vao); //bind vao

     const GLuint VERTEX_ATTR_POSITION = 0;
     const GLuint VERTEX_ATTR_NORMAL = 1;
     const GLuint VERTEX_ATTR_TEXCOORDS = 2;

      glBindBuffer(GL_ARRAY_BUFFER, vbo); //bind vbo
      //active le type d'attribut dont on parle
     glEnableVertexAttribArray(VERTEX_ATTR_POSITION); //active Position
     glEnableVertexAttribArray(VERTEX_ATTR_NORMAL); // active normal
     glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS); //active texture

     // glVertexAttribPointer(VERTEX_ATTR_NUMBER, VEC_NUMBER, GL_FLOAT, GL_FALSE...)
     glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, position));
     glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, normal));
     glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, texCoords));
     
     glBindVertexArray(0); //debind vao

    glm::mat4 viewMatrixTurnLeft, viewMatrixTurnRight, viewMatrixDown, viewMatrixJump, viewMatrixLeft, viewMatrixRight;

     // enable to keep a key pressed
     //SDL_EnableKeyRepeat(delay, interval) (in milliseconds)
     SDL_EnableKeyRepeat(100,150);

     float rotationLeft = 0;
     float rotationRight = 0;
     float move = 0;

     float gravity = 0.5;
     float maxFallSpeed = 1.0;
     float velocityY, velocityZ;
     float positionY, positionZ;
     float axeYJump = 0;
     float axeZJump = 0;
     bool onGround = false;
     int jump = 0;
     float timeTmp;

     //float time = windowManager.getTime();
     float scale = 1.0;

     float acceralationY=0;
     

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

            if(windowManager.isKeyPressed(SDLK_q) == true){
                // rotation par rapport à l'axe Y
                rotationLeft -=45.f;
                viewMatrixTurnLeft = glm::rotate(glm::mat4(1.f), glm::radians(rotationLeft), glm::vec3(0,1,0));
                //viewMatrixTurnLeft = turnLeftCharacter();
            }

            if(windowManager.isKeyPressed(SDLK_d) == true){
                rotationRight += 45.f;
                viewMatrixTurnRight = glm::rotate(glm::mat4(1.f), glm::radians(rotationRight), glm::vec3(0,1,0));
                //viewMatrixTurnRight = turnRightCharacter();
            }

            // jump
            if(windowManager.isKeyPressed(SDLK_z) == true){
                jump = 1;
                timeTmp = windowManager.getTime();
            }
            /*while(jump = 1 && (0.1*windowManager.getTime() - timeTmp < 3.0)){
                axeYJump = 0.1*windowManager.getTime()-timeTmp;
                std::cout << axeYJump << std::endl;
            }*/
            //viewMatrixJump = glm::translate(glm::mat4(1.f), glm::vec3(0.0,axeYJump,0.0));

            // se baisser
            if(windowManager.isKeyPressed(SDLK_s) == true){
                // pour se baisser
                if(scale == 1.0){
                    scale = 0.2;
                    viewMatrixDown = glm::scale(glm::mat4(1.f), glm::vec3(1.0,scale,1.0));
                }
                // pour se relever
                else{
                    scale = 1.0;
                    viewMatrixDown = glm::scale(glm::mat4(1.f), glm::vec3(1.0,scale,1.0));
                }
                //viewMatrixDown = downCharacter();
            }

            // move on the left
            if(windowManager.isKeyPressed(SDLK_LEFT) == true){
                move -= 2.0;
                viewMatrixLeft = glm::translate(glm::mat4(1.f), glm::vec3(move, 0.0, 0.0));
            }

            // move on the right
            if(windowManager.isKeyPressed(SDLK_RIGHT) == true){
                move += 2.0;
                viewMatrixLeft = glm::translate(glm::mat4(1.f), glm::vec3(move, 0.0, 0.0));
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // trackball
         glm::mat4 viewMatrix = t.getViewMatrix(); 

         float a = 800.0/600.0;
         // glm::perspective(angle_vertical_de_vue, ratio_fenetre, near, far)
         projMatrix = glm::perspective(glm::radians(90.f),a,0.1f,100.f)*viewMatrix;
         // glm::translate(glm::mat4(1.0), glm:vec3(x,y,z))
         //MVMatrix = glm::translate(glm::mat4(1.0),glm::vec3(0.0,-3.0,-5.0))*viewMatrix;
         NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

         // faire tourner le cube
         //MVMatrix = glm::rotate(MVMatrix, windowManager.getTime(), glm::vec3(0,1.0,0));
         
         // saut du personnage (pas encore très au point mais ça marche)
         float timeDifference;
         float maxJump = 6.0;

         timeDifference = windowManager.getTime()*2.0-timeTmp;
         std::cout << jump << std::endl;
         if(jump == 1){
            MVMatrix = glm::translate(glm::mat4(1.0),glm::vec3(0.0,timeDifference, -10.0));
            if(timeDifference > maxJump){
                jump = 2;
                timeTmp = windowManager.getTime();
                
                //std::cout << timeDifference << std::endl;
            }
            
        }
        else{
            if(maxJump-timeDifference > 0.0 && jump == 2){
                MVMatrix = glm::translate(glm::mat4(1.0),glm::vec3(0.0,maxJump-timeDifference, -10.0));
            }
            else{
                MVMatrix = glm::translate(glm::mat4(1.0),glm::vec3(0.0,0.0, -10.0));
                jump = 0;
            }
        }

         // void glUniform4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
         glm::mat4 mat1 = projMatrix * MVMatrix * viewMatrixTurnLeft *viewMatrixTurnRight * viewMatrixDown *viewMatrixJump * viewMatrixLeft * viewMatrixRight;
         glm::mat4 mat2 = MVMatrix * viewMatrixTurnLeft * viewMatrixTurnRight * viewMatrixDown *viewMatrixJump;

         glUniformMatrix4fv(locationuMVPMatrix, 1, false, glm::value_ptr(mat1));
         glUniformMatrix4fv(locationuMVMatrix, 1, false, glm::value_ptr(mat2));
         glUniformMatrix4fv(locationuNormalMatrix, 1, false, glm::value_ptr(NormalMatrix));

         glBindVertexArray(vao);
         glDrawArrays(GL_TRIANGLES,0,nbVertex);
         glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1,&vbo);
    glDeleteVertexArrays(1,&vao);

    return EXIT_SUCCESS;
}
