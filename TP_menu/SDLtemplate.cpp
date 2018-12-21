#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <glimac/Program.hpp>
#include <glimac/Scene.hpp>
#include <glimac/Exception.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Personnage.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <vector>

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

class Vertex2DUV 
{
public:
    //methode
    Vertex2DUV();
    Vertex2DUV(glm::vec2 position,glm::vec2 m_coordtexture);
    //attributs
    glm::vec2 m_position;
    glm::vec2 m_coordtexture;

};

Vertex2DUV::Vertex2DUV()
    :m_position(0,0),m_coordtexture(0,0)
{}
Vertex2DUV::Vertex2DUV(glm::vec2 position,glm::vec2 coord)
    :m_position(position),m_coordtexture(coord)
{}

const uint32_t width = 800;
const uint32_t height = 600;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(width, height, "ImacRun");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/tex2D.vs.glsl",
                                  applicationPath.dirPath() + "shaders/tex2D.fs.glsl");
    program.use();

    /********************************
    IF YOU'RE USING GLSL VERSION 130
    DELETE THIS PART IF YOU'RE VERSION 330
    ********************************/
    GLuint test = LoadShader("/home/administrateur/Téléchargements/Moves/ImacRun/TP_menu/shaders/tex2D.vs.glsl", "/home/administrateur/Téléchargements/Moves/ImacRun/TP_menu/shaders/tex2D.fs.glsl");
    glUseProgram(test);
    /********************************
    END - IF YOU'RE USING GLSL VERSION 130
    ********************************/

    GLint uModelMatrixLocation = glGetUniformLocation(program.getGLId(), "uModelMatrix");
    GLint uModelColor = glGetUniformLocation(program.getGLId(),"uColor");
    GLint uModelTexture = glGetUniformLocation(program.getGLId(),"uTexture");

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;



    
    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    glEnable(GL_DEPTH_TEST);

    //glGenBuffers(GLsizei n,GLuint* buffers)
     /*GLuint vbo;
     glGenBuffers(1,&vbo);*/
     /*
     Pour binder un buffer on utilise la fonction 
     glBindBuffer(GLenum target, GLuint buffer)
     */
    /* glBindBuffer(GL_ARRAY_BUFFER,vbo);
     Vertex2DColor vertices[] = { 
        //Triangle1
        Vertex2DColor(glm::vec2(-0.5, 0.5), glm::vec3(1, 0, 0)),
        Vertex2DColor(glm::vec2(-0.5, -0.5), glm::vec3(0, 1, 0)),
        Vertex2DColor(glm::vec2(0.5,-0.5), glm::vec3(0, 0, 1)),
        //Triangle2
        Vertex2DColor(glm::vec2(-0.5, 0.5), glm::vec3(1, 0, 0)),
        Vertex2DColor(glm::vec2(0.5, 0.5), glm::vec3(0, 1, 0)),
        Vertex2DColor(glm::vec2(0.5,-0.5), glm::vec3(0, 0, 1)),
    };
     glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vertex2DColor), vertices, GL_STATIC_DRAW);
     glBindBuffer(GL_ARRAY_BUFFER,0);*/
     /*
     Création du VAO
     glGenVertexArrays(GLsizei n, GLuint *arrays
     */
     /*GLuint vao;
     glGenVertexArrays(1,&vao);
     //Bind VAO
     glBindVertexArray(vao);
     const GLuint VERTEX_ATTR_POSITION = 0;
     glEnableVertexAttribArray(3);
     glEnableVertexAttribArray(8);

     // Spécification des attribut de vertex
     static const void* offset = (void*) psize;
     glBindBuffer(GL_ARRAY_BUFFER,vbo);
     glVertexAttribPointer(3,2,GL_FLOAT,GL_FALSE,sizeof(Vertex2DColor),offsetof(Vertex2DColor, position));
     glVertexAttribPointer(8,3,GL_FLOAT,GL_FALSE,sizeof(Vertex2DColor),(const void*) offsetof(Vertex2DColor, color));
     glBindBuffer(GL_ARRAY_BUFFER,0);*/

     GLuint vbo;
     glGenBuffers(1,&vbo);
     glBindBuffer(GL_ARRAY_BUFFER,vbo);
     
     Vertex2DUV sommet1;
     Vertex2DUV sommet2;
     Vertex2DUV sommet3;

     sommet1.m_position.x=-1;
     sommet1.m_position.y=-1;

     sommet1.m_coordtexture.x=0;
     sommet1.m_coordtexture.y=1;


     sommet2.m_position.x=1;
     sommet2.m_position.y=-1;

     sommet2.m_coordtexture.x=1;
     sommet2.m_coordtexture.y=1;


     sommet3.m_position.x=0;
     sommet3.m_position.y=1;

     sommet3.m_coordtexture.x=0.5;
     sommet3.m_coordtexture.y=0;

    Vertex2DUV vertices[] = {sommet1,sommet2,sommet3};

     glBufferData(GL_ARRAY_BUFFER,15*sizeof(Vertex2DUV),vertices, GL_STATIC_DRAW);
     glBindBuffer(GL_ARRAY_BUFFER,0);

     GLuint vao;
     glGenVertexArrays(1,&vao);
     glBindVertexArray(vao);
     glEnableVertexAttribArray(0);
     glEnableVertexAttribArray(1);

     // Spécification des attribut de vertex
     
     glBindBuffer(GL_ARRAY_BUFFER,vbo);
     glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(Vertex2DUV),(void *) offsetof(Vertex2DUV,m_position));
     glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex2DUV),(void *) offsetof(Vertex2DUV,m_coordtexture));
     glBindBuffer(GL_ARRAY_BUFFER,0);
     glBindVertexArray(0);


    std::unique_ptr<Image> menuBackground;
    // load texture
    menuBackground = loadImage("/home/administrateur/Téléchargements/Moves/ImacRun/assets/menu/triforce.png");
    if(menuBackground==NULL){
        std::cout<< "Impossible de charger l'image !" <<std::endl;
     }

    GLuint texture[1];
    // create new texture object
    glGenTextures(1, texture);
    // bind texture
    glBindTexture(GL_TEXTURE_2D, texture[0]);
        // send image to the graphic card
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,menuBackground->getWidth(), menuBackground->getHeight(),0,GL_RGBA,GL_FLOAT,menuBackground->getPixels());
        // put a filter
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // debind
    glBindTexture(GL_TEXTURE_2D, 0);


    // Application loop:
    bool done = false;
    float rotation;
    while(!done) {
        
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }



        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUniform1i(uModelTexture,0);
        glBindTexture(GL_TEXTURE_2D,texture[0]);

        glBindVertexArray(vao);
         glDrawArrays(GL_TRIANGLES,0,3);
        glBindVertexArray(0);

        //glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.f), glm::radians(rotation), glm::vec3(0,1,0));
        

        //transformer vue puis afficher scene***SCENE***
        //viewMatrix = glm::rotate(viewMatrix, glm::radians(rotation), glm::vec3(0,1,0));
        //viewMatrix = glm::translate(viewMatrix, glm::vec3(0, -4.f, -5.f));
        //scene.drawScene(viewMatrix);


        //***PERSO***
        //viewMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0, -0.3, -2))*rotationMatrix;
        //personnage.draw(0, 0, viewMatrix, rotationMatrix, scene._cube, scene._sphere);

        glBindTexture(GL_TEXTURE_2D,0);

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteTextures(1, texture);
    return EXIT_SUCCESS;

}