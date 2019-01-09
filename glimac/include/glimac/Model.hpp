#pragma once

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <glimac/Geometry.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/common.hpp>
#include <glimac/Program.hpp>
#include <glimac/Parameters.hpp>
#include <glimac/Texture.hpp>

namespace glimac {

/// \brief Represents the 3D model of an object
	class Model {
	// METHODS
	public:
		// CONSTRUCTORS - DESTRUCTORS
		/// \brief default model Constructor
		Model();

		/// \brief Model Constructor by model name
		/// \param modelName : std::string& name of the model
		Model(const std::string& modelName, const std::string& textureName);

		/// \brief Model Copy constructor
		/// \param model : Model Model to copy
		Model(const Model &model);

		/// \brief model Destructor
		~Model();

		// GETTERS
		/// \brief get VAO
		inline const GLuint VAO() const { 
			return _VAO; 
		}

		/// \brief get VBO
		inline const GLuint VBO() const { 
			return _VBO; 
		}

		/// \brief get IBO
		inline const GLuint IBO() const { 
			return _IBO; 
		}

		/// \brief get Geometry
		inline const glimac::Geometry geometry() const { 
			return _geometry; 
		}

		/// \brief get Texture ID
		const GLuint textureID() const {
			return _textureID;
		}

		// SETTERS // TODO : change for non-const getters ?
		// NON-CONST GETTERS (can be used as setters)
		/// \brief set VBO of the model
		/// \param geometry geometry of the model
		void setVBO(const glimac::Geometry &geometry);

		/// \brief set IBO of the model
		/// \param geometry geometry of the model
		void setIBO(const glimac::Geometry &geometry);

		/// \brief set VAO based on the VBO and VAO
		void setVAO();

		void setTexture(const std::string textureName);

	private:
		/// \brief Contains the vertices and materials of the model
		glimac::Geometry _geometry;
		/// \brief Represent the VBO of the model
		GLuint _VBO;
		/// \brief Represent the IBO of the model
		GLuint _IBO;
		/// \brief Represent the VAO of the model
		GLuint _VAO;

		/// \brief Texture ID of the model
		GLuint _textureID;

		Texture* _texture;

		std::string _textureName;
	};
}