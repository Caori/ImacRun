#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Cube.hpp"

namespace glimac {

void Cube::build(GLfloat edgeLenght){
	ShapeVertex vertex;
    // face 1
    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(-edgeLenght,-edgeLenght,-edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(-edgeLenght,-edgeLenght,edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(-edgeLenght,edgeLenght,edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(edgeLenght,edgeLenght,-edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(-edgeLenght,-edgeLenght,-edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(-edgeLenght,edgeLenght,-edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    // face 2

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(edgeLenght,-edgeLenght,edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(-edgeLenght,-edgeLenght,-edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(edgeLenght,-edgeLenght,-edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

     vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(edgeLenght,edgeLenght,-edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(edgeLenght,-edgeLenght,-edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(-edgeLenght,-edgeLenght,-edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    // face 3
    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(-edgeLenght,-edgeLenght,-edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(-edgeLenght,edgeLenght,edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(-edgeLenght,edgeLenght,-edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

     vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(edgeLenght,-edgeLenght,edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(-edgeLenght,-edgeLenght,edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(-edgeLenght,-edgeLenght,-edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    // face 4

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(-edgeLenght,edgeLenght,edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(-edgeLenght,-edgeLenght,edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(edgeLenght,-edgeLenght,edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

     vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(edgeLenght,edgeLenght,edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(edgeLenght,-edgeLenght,-edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(edgeLenght,edgeLenght,-edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    // face 5

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(edgeLenght,-edgeLenght,-edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(edgeLenght,edgeLenght,edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(edgeLenght,-edgeLenght,edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

     vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(edgeLenght,edgeLenght,edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(edgeLenght,edgeLenght,-edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(-edgeLenght,edgeLenght,-edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);


    // face 6

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(edgeLenght,edgeLenght,edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(-edgeLenght,edgeLenght,-edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(-edgeLenght,edgeLenght,edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

     vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(edgeLenght,edgeLenght,edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(-edgeLenght,edgeLenght,edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);

    vertex.texCoords = glm::vec2(0,0);
    vertex.normal = glm::vec3(edgeLenght,-edgeLenght,edgeLenght);
    vertex.position = vertex.normal;
    m_Vertices.push_back(vertex);
}

void Cube::sendData(){
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXCOORDS = 2;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo); //bind buffer vbo1 sur cible

    //envoi des données
    glBufferData(GL_ARRAY_BUFFER, m_nVertexCount*sizeof(ShapeVertex), getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); //debind vbo1

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao); //bind vao1

    glBindBuffer(GL_ARRAY_BUFFER, vbo); //bind vbo1
    //active le type d'attribut dont on parle
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION); //active Position
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL); // active normal
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS); //active texture

    // glVertexAttribPointer(VERTEX_ATTR_NUMBER, VEC_NUMBER, GL_FLOAT, GL_FALSE...)
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, texCoords));
     
    glBindVertexArray(0); //debind vao1
}

}
