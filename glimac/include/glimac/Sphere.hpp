#pragma once

#include <vector>

#include "common.hpp"

namespace glimac {
	/*! \class Sphere
	\brief Represents a discrete sphere centered in (0, 0, 0) in its local reference point.
		Its vertical axis is (0, 1, 0) and its transversal axes are (1, 0, 0) and (0, 0, 1)
	*/
	class Sphere {
	private:
		std::vector<ShapeVertex> m_Vertices; /**< Vector of SHapeVertex vertices */
		GLsizei m_nVertexCount; /**< Number of vertices */

		/*!
		* \fn void build(GLfloat radius, GLsizei discLat, GLsizei discLong);
		* \brief Allocates and builds the sphere data.
		* \param radius Radius of the sphere
		* \param discLat Number of sides in latitude
		* \param discLong Number of sides in longitude
		*/
		void build(GLfloat radius, GLsizei discLat, GLsizei discLong);

		/*! 
		* \fn void sendData()
		* \brief Sends data to the vbo and the vao
		*/
		void sendData();

	public:
		GLuint vao; /**< Vertex array object */
		GLuint vbo; /**< Vertex buffer object */

		Sphere(GLfloat radius = 0.5, GLsizei discLat = 16, GLsizei discLong = 8)
			: m_nVertexCount(0) {
			build(radius, discLat, discLong); // Construction (voir le .cpp)
			sendData();
		}

		~Sphere(){
			glDeleteBuffers(1, &vbo);
			glDeleteVertexArrays(1, &vao);
		}

		/*! 
		* \fn inline const ShapeVertex* getDataPointer() const
		* \brief Gets data pointer
		* \return Const pointer of ShapeVertex
		*/
		inline const ShapeVertex* getDataPointer() const {
			return &m_Vertices[0];
		}

		/*! 
		* \fn inline GLsizei getVertexCount() const
		* \brief Gets the number of vertices of the sphere
		* \return Const pointer of ShapeVertex
		*/
		inline GLsizei getVertexCount() const {
			return m_nVertexCount;
		}

	};
    
}