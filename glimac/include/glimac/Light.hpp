#pragma once //fait que le compilateur le compile qu'une fois

#include "glm.hpp"
#include <iostream>
#include <stdlib.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include "glimac/common.hpp"

namespace glimac {
	/*! \class Light
	\brief An abstract class to epresents a source of light
	*/
	class Light {

	protected:
		Program _Program; /**< The combination of shaders used */
		GLint uLightIntensity; /**< The uniform location of the light intensity*/

	public:
		Light(const FilePath& applicationPath)
			: _Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
				applicationPath.dirPath() + "shaders/directionallight.fs.glsl")) {
			_Program.use();
			uLightIntensity = glGetUniformLocation(_Program.getGLId(), "uLightIntensity");
		}

		virtual ~Light() {}

		/*! 
		* \fn virtual void drawLight(glm::mat4& viewMatrix, glm::vec4 direction) const
		* \brief An abstract function for placing the light in the scene
		* \param viewMatrix The active view matrix
		* \param direction The direction of the rays of light/placement of the light source
		*/
		virtual void drawLight(glm::mat4& viewMatrix, glm::vec4 direction) const = 0;
	};
}