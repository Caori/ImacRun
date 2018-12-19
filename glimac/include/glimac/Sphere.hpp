#pragma once

#include <vector>

#include "common.hpp"

namespace glimac {

// Représente une sphère discrétisée centrée en (0, 0, 0) (dans son repère local)
// Son axe vertical est (0, 1, 0) et ses axes transversaux sont (1, 0, 0) et (0, 0, 1)
class Sphere {
    // Alloue et construit les données (implantation dans le .cpp)
    void build(GLfloat radius, GLsizei discLat, GLsizei discLong);
    //envoie les données aux vao/vbo
    void sendData();

public:
    GLuint vao, vbo;

    // Constructeur: alloue le tableau de données et construit les attributs des vertex
    Sphere(GLfloat radius = 0.5, GLsizei discLat=16, GLsizei discLong=8):
        m_nVertexCount(0) {
        build(radius, discLat, discLong); // Construction (voir le .cpp)
        sendData();
    }

    ~Sphere(){
        glDeleteBuffers(1,&vbo);
        glDeleteVertexArrays(1,&vao);
    }

    // Renvoit le pointeur vers les données
    const ShapeVertex* getDataPointer() const {
        return &m_Vertices[0];
    }
    
    // Renvoit le nombre de vertex
    GLsizei getVertexCount() const {
        return m_nVertexCount;
    }

private:
    std::vector<ShapeVertex> m_Vertices;
    GLsizei m_nVertexCount; // Nombre de sommets
};
    
}