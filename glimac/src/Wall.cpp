#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <iostream>

#include "glimac/common.hpp"
#include "glimac/Wall.hpp"
#include "glimac/Cube.hpp"
#include "glimac/Sphere.hpp"
//#include "Texture.hpp"

namespace glimac {

	Wall::Wall(const FilePath& applicationPath)
		: Object(applicationPath) {
	}

	void Wall::draw(int i, int j, glm::mat4 &viewMatrix, Cube& cube, Sphere& sphere, SDLWindowManager &window) const {
		glm::mat4 projMatrix = glm::perspective(glm::radians(70.f), 1200.f/900.f, 0.1f, 100.f);

		glUniform3f(uKd, 0.2f, 0.3f, 0.8f); //couleur diffuse
		glUniform3f(uKs, 0.8f, 0.7f, 0.2f); //couleur tache speculaire
		glUniform1f(uShininess, 20);

		glBindVertexArray(cube.vao);
			glm::mat4 MVMatrix = viewMatrix*glm::translate(glm::mat4(1.0),glm::vec3(j, 0., -i));
			glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
			glUniformMatrix4fv(uMVPMatrix, 1, false, glm::value_ptr(projMatrix * MVMatrix));
			glUniformMatrix4fv(uMVMatrix, 1, false, glm::value_ptr(MVMatrix));
			glUniformMatrix4fv(uNormalMatrix, 1, false, glm::value_ptr(NormalMatrix));
			glDrawArrays(GL_TRIANGLES,0,cube.getVertexCount());

			MVMatrix = glm::translate(glm::mat4(1.0),glm::vec3(j, 1., -i))*viewMatrix;
			NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
			glUniformMatrix4fv(uMVPMatrix, 1, false, glm::value_ptr(projMatrix * MVMatrix));
			glUniformMatrix4fv(uMVMatrix, 1, false, glm::value_ptr(MVMatrix));
			glUniformMatrix4fv(uNormalMatrix, 1, false, glm::value_ptr(NormalMatrix));
			glDrawArrays(GL_TRIANGLES,0,cube.getVertexCount());
		glBindVertexArray(0);
	}
}
