#pragma once

#include <vector>

#include "common.hpp"

namespace glimac {

class Cube {
    public:
        GLuint vao, vbo;

        // Constructeur: alloue le tableau de données et construit les attributs des vertex
        Cube(GLfloat edgeLenght = 0.5):
            m_nVertexCount(36) {
            build(edgeLenght); // Construction (voir le .cpp)
            sendData();
        }

        ~Cube(){
            glDeleteBuffers(1,&vbo);
            glDeleteVertexArrays(1,&vao);
        }

        GLsizei getVertexCount(){
            return m_nVertexCount;
        }

        // Renvoit le pointeur vers les données
        const ShapeVertex* getDataPointer() const {
            return &m_Vertices[0];
        }

    private:
        std::vector<ShapeVertex> m_Vertices;
        GLsizei m_nVertexCount; // Nombre de sommets

            // Alloue et construit les données (le paramètre est la longueur de l'arête)
            void build(GLfloat edgeLenght);
            //envoie les données aux vao/vbo
            void sendData();
};
    
}
