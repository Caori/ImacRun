#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <iostream>

#include "glimac/common.hpp"
#include "glimac/Obstacle.hpp"

namespace glimac {

	Obstacle::Obstacle(const Model& model)
		: Object(), model(model) {
	}

	void Obstacle::draw(int i, int j, glm::mat4& viewMatrix, SDLWindowManager& window) const {
		glm::mat4 projMatrix = glm::perspective(glm::radians(70.f), 1200.f/900.f, 0.1f, 100.f);

		glUniform3f(uKd, 0.7f, 0.7f, 0.7f); //couleur diffuse
		glUniform3f(uKs, 0.0f, 0.2f, 0.2f); //couleur tache speculaire
		glUniform1f(uShininess, 32);

		glUniform1i(uTexture, 0);
		glBindTexture(GL_TEXTURE_2D, model.textureID());

		glBindVertexArray(model.VAO());
			glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0),glm::vec3(j, 0.5f, -i))*viewMatrix;
			MVMatrix = glm::scale(MVMatrix, glm::vec3(0.5, 0.5, 0.5));
			MVMatrix = glm::rotate(MVMatrix, 0.9f, glm::vec3(0.0, 1, 0.0));
			glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
			glUniformMatrix4fv(uMVPMatrix, 1, false, glm::value_ptr(projMatrix * MVMatrix));
			glUniformMatrix4fv(uMVMatrix, 1, false, glm::value_ptr(MVMatrix));
			glUniformMatrix4fv(uNormalMatrix, 1, false, glm::value_ptr(NormalMatrix));
			glDrawElements(GL_TRIANGLES, model.geometry().getIndexCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}
