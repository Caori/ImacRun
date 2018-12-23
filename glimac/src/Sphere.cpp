#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Sphere.hpp"

namespace glimac {

    void Sphere::build(GLfloat r, GLsizei discLat, GLsizei discLong) {
        // Equation paramétrique en (r, phi, theta) de la sphère 
        // avec r >= 0, -PI / 2 <= theta <= PI / 2, 0 <= phi <= 2PI
        //
        // x(r, phi, theta) = r sin(phi) cos(theta)
        // y(r, phi, theta) = r sin(theta)
        // z(r, phi, theta) = r cos(phi) cos(theta)
        //
        // Discrétisation:
        // dPhi = 2PI / discLat, dTheta = PI / discLong
        //
        // x(r, i, j) = r * sin(i * dPhi) * cos(-PI / 2 + j * dTheta)
        // y(r, i, j) = r * sin(-PI / 2 + j * dTheta)
        // z(r, i, j) = r * cos(i * dPhi) * cos(-PI / 2 + j * dTheta)

        GLfloat rcpLat = 1.f / discLat, rcpLong = 1.f / discLong;
        GLfloat dPhi = 2 * glm::pi<float>() * rcpLat, dTheta = glm::pi<float>() * rcpLong;
        
        std::vector<ShapeVertex> data;
        
        // Construit l'ensemble des vertex
        for(GLsizei j = 0; j <= discLong; ++j) {
            GLfloat cosTheta = cos(-glm::pi<float>() / 2 + j * dTheta);
            GLfloat sinTheta = sin(-glm::pi<float>() / 2 + j * dTheta);
            
            for(GLsizei i = 0; i <= discLat; ++i) {
                ShapeVertex vertex;
                
                vertex.texCoords.x = i * rcpLat;
                vertex.texCoords.y = 1.f - j * rcpLong;

                vertex.normal.x = sin(i * dPhi) * cosTheta;
                vertex.normal.y = sinTheta;
                vertex.normal.z = cos(i * dPhi) * cosTheta;
                
                vertex.position = r * vertex.normal;
                
                data.push_back(vertex);
            }
        }

        m_nVertexCount = discLat * discLong * 6;
        
        GLuint idx = 0;
        // Construit les vertex finaux en regroupant les données en triangles:
        // Pour une longitude donnée, les deux triangles formant une face sont de la forme:
        // (i, i + 1, i + discLat + 1), (i, i + discLat + 1, i + discLat)
        // avec i sur la bande correspondant à la longitude
        for(GLsizei j = 0; j < discLong; ++j) {
            GLsizei offset = j * (discLat + 1);
            for(GLsizei i = 0; i < discLat; ++i) {
                m_Vertices.push_back(data[offset + i]);
                m_Vertices.push_back(data[offset + (i + 1)]);
                m_Vertices.push_back(data[offset + discLat + 1 + (i + 1)]);
                m_Vertices.push_back(data[offset + i]);
                m_Vertices.push_back(data[offset + discLat + 1 + (i + 1)]);
                m_Vertices.push_back(data[offset + i + discLat + 1]);
            }
        }
        
        // Attention ! dans cette implantation on duplique beaucoup de sommets. Une meilleur stratégie est de passer
        // par un Index Buffer Object, que nous verrons dans les prochains TDs
    }

    void Sphere::sendData(){
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
