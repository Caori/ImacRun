#pragma once

#include <iostream>
#include <stdlib.h>

#include "glm.hpp"
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include "glimac/Cube.hpp"
#include "glimac/Sphere.hpp"

namespace glimac {

    class Object {
    protected:

        Program _Program;
        GLint uMVPMatrix;
        GLint uMVMatrix;
        GLint uNormalMatrix;
        GLint uTexture;
        GLint uKd;
        GLint uKs;
        GLfloat uShininess;

    public:
        Object(const FilePath& applicationPath)
            : _Program(loadProgram("/home/administrateur/Téléchargements/Moves/ImacRun/TP_template/shaders/3D_130.vs.glsl",
                                "/home/administrateur/Téléchargements/Moves/ImacRun/TP_template/shaders/normals.fs.glsl"))
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

        virtual void draw(int i, int j, glm::mat4 &viewMatrix, glm::mat4 &rotationMatrix/*Camera& camera*/, Cube& cube, Sphere& sphere) const = 0;

  };

}
