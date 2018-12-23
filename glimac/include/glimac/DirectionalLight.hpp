#pragma once

#include <iostream>
#include <stdlib.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include "glimac/common.hpp"
#include "glimac/Light.hpp"

namespace glimac {
	/*! \class DirectionalLight
        \brief Represents a uniform light with a direction vector
    */
	class DirectionalLight : public Light {
	private:
		GLint uLightDir_vs; /**< Light direction */

	public:
		DirectionalLight(const FilePath& applicationPath);

		~DirectionalLight() {}

		/*! 
        * \fn void drawLight(glm::mat4& viewMatrix, glm::vec4 direction) const
        * \brief Places and orients the light in the scene
        * \param viewMatrix The active view matrix
        * \param direction The direction of the rays of light
        */
		void drawLight(glm::mat4& viewMatrix, glm::vec4 direction) const;
	};

}
