#pragma once

#include <iostream>
#include <GL/glew.h>
#include <glimac/Geometry.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>


namespace glimac {

	class Texture {
	private:
		/// \  tableau de textures
		GLuint _texID;
		std::string _texName;
		std::unique_ptr<glimac::Image> _textureToLoad;

	public:
		//Constructors
		// Default
		Texture();
		// Basic
		Texture(const std::string &textureName);
		// Copy
		Texture(const Texture& tex);

		//getter
		inline GLuint getTextureID() const {
			return _texID;
		}

		//setter
		inline void setTexture(const std::string &texture) { 
			_texName = texture;
		}

		//destructor
		~Texture() {}

		bool loadTexture();

	};

}
