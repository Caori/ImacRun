#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <iostream>

#include "glimac/common.hpp"
#include "glimac/Wall.hpp"
#include "glimac/AssetLoader.hpp"
#include "glimac/MapTransformation.hpp"

namespace glimac {

	Wall::Wall(const Model& model)
		: Object(), model(model) {
	}

	void Wall::draw(int i, int j, glm::mat4 &viewMatrix, SDLWindowManager &window) const {
		glm::mat4 projMatrix = glm::perspective(glm::radians(70.f), 1200.f/900.f, 0.1f, 100.f);

		glUniform3f(uKd, 0.5f, 0.35f, 0.05f); //couleur diffuse
		glUniform3f(uKs, 0.5f, 0.35f, 0.05f); //couleur tache speculaire
		glUniform1f(uShininess, 20);

		glUniform1i(uTexture, 0);
		glBindTexture(GL_TEXTURE_2D, model.textureID());

		glBindVertexArray(model.VAO());
			glm::mat4 MVMatrix = viewMatrix*glm::translate(glm::mat4(1.0), glm::vec3(j, 1, -i));
			glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
			glUniformMatrix4fv(uMVPMatrix, 1, false, glm::value_ptr(projMatrix * MVMatrix));
			glUniformMatrix4fv(uMVMatrix, 1, false, glm::value_ptr(MVMatrix));
			glUniformMatrix4fv(uNormalMatrix, 1, false, glm::value_ptr(NormalMatrix));
			glDrawElements(GL_TRIANGLES, model.geometry().getIndexCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
