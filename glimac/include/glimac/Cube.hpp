#pragma once

#include <vector>

#include "common.hpp"

namespace glimac {

	class Cube {
	public:
		GLuint vao; /**< Vertex array object */
		GLuint vbo; /**< Vertex buffer object */

		Cube(GLfloat edgeLenght = 0.5)
			: m_nVertexCount(36) {
			build(edgeLenght); // Construction (voir le .cpp)
			sendData();
		}

		~Cube(){
			glDeleteBuffers(1, &vbo);
			glDeleteVertexArrays(1, &vao);
		}

		/*! 
		* \fn inline GLsizei getVertexCount() const
		* \brief Gets the number of vertices of the cube
		* \return Const pointer of ShapeVertex
		*/
		inline GLsizei getVertexCount(){
			return m_nVertexCount;
		}

		 /*! 
		* \fn inline const ShapeVertex* getDataPointer() const
		* \brief Gets data pointer
		* \return Const pointer of ShapeVertex
		*/
		inline const ShapeVertex* getDataPointer() const {
			return &m_Vertices[0];
		}

	private:
		std::vector<ShapeVertex> m_Vertices; /**< Vector of vertices */
		GLsizei m_nVertexCount; /**< Number of vertices */

		/*!
		* \fn void build(GLfloat edgeLenght);
		* \brief Allocates and builds the cube data.
		* \param edgeLength Lenght of a side
		*/
		void build(GLfloat edgeLenght);

		/*! 
		* \fn void sendData()
		* \brief Sends data to the vbo and the vao
		*/
		void sendData();
	};
    
}
