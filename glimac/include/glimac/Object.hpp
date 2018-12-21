#pragma once

#include <iostream>
#include <stdlib.h>
#include <string>

#include "glm.hpp"
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include "glimac/Cube.hpp"
#include "glimac/Sphere.hpp"
#include <glimac/SDLWindowManager.hpp>

namespace glimac {

    class Object {
    protected:
        Program _Program;
        GLint uMVPMatrix;
        GLint uMVMatrix;
        GLint uNormalMatrix;
        GLint uKd;
        GLint uKs;
        GLfloat uShininess;

    public:
        GLint uTexture;

        Object(const FilePath& applicationPath, const std::string fShader = "normals.fs.glsl")
            : _Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                                   applicationPath.dirPath() + "shaders/" + fShader))
                                /*applicationPath.dirPath() + "shaders/directionallight.fs.glsl")) */
            {
            _Program.use();
            uMVPMatrix = glGetUniformLocation(_Program.getGLId(), "uMVPMatrix");
            uMVMatrix = glGetUniformLocation(_Program.getGLId(), "uMVMatrix");
            uNormalMatrix = glGetUniformLocation(_Program.getGLId(), "uNormalMatrix");
            uTexture = glGetUniformLocation(_Program.getGLId(), "uTexture");
            uKd = glGetUniformLocation(_Program.getGLId(), "uKd");
            uKs = glGetUniformLocation(_Program.getGLId(), "uKs");
            uShininess = glGetUniformLocation(_Program.getGLId(), "uShininess");
        }
        ~Object() {}

        virtual void draw(int i, int j, glm::mat4 &viewMatrix/*Camera& camera*/, Cube& cube, Sphere& sphere, SDLWindowManager &window) const = 0;

  };

}
