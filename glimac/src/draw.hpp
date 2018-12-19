void draw1(int i, int j, glm::mat4 viewMatrix, glm::mat4 projMatrix, int nbVertex){
	glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0),glm::vec3(j, 0., -i))*viewMatrix;
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    glUniformMatrix4fv(locationuMVPMatrix, 1, false, glm::value_ptr(projMatrix * MVMatrix));
    glUniformMatrix4fv(locationuMVMatrix, 1, false, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(locationuNormalMatrix, 1, false, glm::value_ptr(NormalMatrix));
    glDrawArrays(GL_TRIANGLES,0,nbVertex);
}