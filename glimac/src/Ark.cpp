#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <iostream>

#include "glimac/common.hpp"
#include "glimac/Ark.hpp"
#include "glimac/Cube.hpp"
#include "glimac/Sphere.hpp"
//#include "Texture.hpp"

namespace glimac {

Ark::Ark(const FilePath& applicationPath)
	:Object(applicationPath){
}

void Ark::draw(int i, int j, glm::mat4 &viewMatrix, glm::mat4 &rotationMatrix, Cube& cube, Sphere& sphere) const {
	glm::mat4 projMatrix = glm::perspective(glm::radians(70.f),800.f/600.f ,0.1f,100.f)*viewMatrix;

	glBindVertexArray(cube.vao);
		float scale =  10.0;

	 	glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0),glm::vec3(j, 0., -i))*viewMatrix;
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        glUniformMatrix4fv(uMVPMatrix, 1, false, glm::value_ptr(projMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix, 1, false, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, false, glm::value_ptr(NormalMatrix));
        glDrawArrays(GL_TRIANGLES,0,cube.getVertexCount());

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
