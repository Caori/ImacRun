#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <iostream>

#include "glimac/common.hpp"
#include "glimac/Coin.hpp"
#include "glimac/SDLWindowManager.hpp"
#include "glimac/Model.hpp"

namespace glimac {

    Coin::Coin(int value, const Model& model)
        :_value(value), Object(), model(model) {
    }


    void Coin::draw(int i, int j, glm::mat4& viewMatrix, SDLWindowManager& window) const {
        glm::mat4 projMatrix = glm::perspective(glm::radians(70.f), 1200.f/900.f, 0.1f, 100.f);
        
		
		glUniform3f(uKd, 0.3f, 0.8f, 0.3f); //couleur diffuse
		glUniform3f(uKs, 0.7f, 0.2f, 0.7f); //couleur tache speculaire
		glUniform1f(uShininess, 64);

		if(_value == 1) glUniform3f(uKd, 0.8f, 0.4f, 0.4f);
		if(_value == 2) glUniform3f(uKd, 0.5f, 0.5f, 0.5f); //couleur diffuse
		if(_value == 3) glUniform3f(uKd, 0.8f, 0.8f, 0.0f);
		glUniform3f(uKs, 0.2f, 0.2f, 0.2f); //couleur tache speculaire
		glUniform1f(uShininess, 32);
		
		glUniform1i(uTexture, 0);
		glBindTexture(GL_TEXTURE_2D, model.textureID());

		glBindVertexArray(model.VAO());
    		glm::mat4 MVMatrix = viewMatrix*glm::translate(glm::mat4(1.0),glm::vec3(j, 1., -i));
			MVMatrix = glm::rotate(MVMatrix, window.getTime()*2, glm::vec3(0,1,0));
			MVMatrix = glm::scale(MVMatrix, glm::vec3(0.5, 0.5, 0.5));
			glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
			glUniformMatrix4fv(uMVPMatrix, 1, false, glm::value_ptr(projMatrix * MVMatrix));
			glUniformMatrix4fv(uMVMatrix, 1, false, glm::value_ptr(MVMatrix));
			glUniformMatrix4fv(uNormalMatrix, 1, false, glm::value_ptr(NormalMatrix));
    	glDrawElements(GL_TRIANGLES, model.geometry().getIndexCount(), GL_UNSIGNED_INT, 0); // Draw all meshes
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		
	}
}
