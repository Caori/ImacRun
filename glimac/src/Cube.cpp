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

}
