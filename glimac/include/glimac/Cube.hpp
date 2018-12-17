#pragma once

#include <vector>

#include "common.hpp"

namespace glimac {

class Cube {
    // Alloue et construit les données (le paramètre est la longueur de l'arête)
    void build(GLfloat edgeLenght);

public:
    // Constructeur: alloue le tableau de données et construit les attributs des vertex
    Cube(GLfloat edgeLenght):
        m_nVertexCount(36) {
        build(edgeLenght); // Construction (voir le .cpp)
    }

    // Renvoit le pointeur vers les données
    const ShapeVertex* getDataPointer() const {
        return &m_Vertices[0];
    }

private:
    std::vector<ShapeVertex> m_Vertices;
    GLsizei m_nVertexCount; // Nombre de sommets
};
    
}