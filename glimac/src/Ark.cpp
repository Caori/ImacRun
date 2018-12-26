#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <iostream>

#include "glimac/common.hpp"
#include "glimac/Ark.hpp"
#include "glimac/Cube.hpp"
#include "glimac/Sphere.hpp"

namespace glimac {

	Ark::Ark(const FilePath& applicationPath)
		:Object(applicationPath){
	}

	void Ark::draw(int i, int j, glm::mat4& viewMatrix, Cube& cube, Sphere& sphere, SDLWindowManager& window) const {
		glm::mat4 projMatrix = glm::perspective(glm::radians(70.f), 1200.f/900.f, 0.1f,100.f);

		glUniform3f(uKd, 0.3f, 0.8f, 0.3f); //couleur diffuse
		glUniform3f(uKs, 0.7f, 0.2f, 0.7f); //couleur tache speculaire
		glUniform1f(uShininess, 64);

		glBindVertexArray(cube.vao);
			float scale =  10.0;
			glm::mat4 MVMatrix = viewMatrix*glm::translate(glm::mat4(1.0),glm::vec3(j, 0., -i));
			glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
			glUniformMatrix4fv(uMVPMatrix, 1, false, glm::value_ptr(projMatrix * MVMatrix));
			glUniformMatrix4fv(uMVMatrix, 1, false, glm::value_ptr(MVMatrix));
			glUniformMatrix4fv(uNormalMatrix, 1, false, glm::value_ptr(NormalMatrix));
			glDrawArrays(GL_TRIANGLES,0,cube.getVertexCount());

			glUniform3f(uKd, 0.5f, 0.5f, 0.5f); //couleur diffuse
			glUniform3f(uKs, 0.5f, 0.5f, 0.5f); //couleur tache speculaire
			glUniform1f(uShininess, 20);

			// height of the arks : 2.0
			MVMatrix = glm::translate(glm::mat4(1.0),glm::vec3(j, 2.0, -i))*viewMatrix;
			NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
			glUniformMatrix4fv(uMVPMatrix, 1, false, glm::value_ptr(projMatrix * MVMatrix));
			glUniformMatrix4fv(uMVMatrix, 1, false, glm::value_ptr(MVMatrix));
			glUniformMatrix4fv(uNormalMatrix, 1, false, glm::value_ptr(NormalMatrix));
			glDrawArrays(GL_TRIANGLES,0,cube.getVertexCount());
		glBindVertexArray(0);
	}
}
