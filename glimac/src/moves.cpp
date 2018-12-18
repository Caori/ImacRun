#include <iostream>
#include "glimac/moves.hpp"

// turn on the left
glm::mat4 turnLeftCharacter(){
	float rotationLeft = 0.0;
	rotationLeft -=45.f;
    glm::mat4 viewMatrixTurnLeft = glm::rotate(glm::mat4(1.f), glm::radians(rotationLeft), glm::vec3(0,1,0));

    return viewMatrixTurnLeft;
}

// turn on the right
glm::mat4 turnRightCharacter(){
	float rotationRight = 0.0;
	rotationRight += 45.f;
    glm::mat4 viewMatrixTurnRight = glm::rotate(glm::mat4(1.f), glm::radians(rotationRight), glm::vec3(0,1,0));

    return viewMatrixTurnRight;
}

glm::mat4 downCharacter(){
    float scale = 1.0;
	glm::mat4 viewMatrixDown;
	// to bend
    if(scale == 1.0){
        scale = 0.2;
        viewMatrixDown = glm::scale(glm::mat4(1.f), glm::vec3(1.0,scale,1.0));
    }

    // to get up
    else{
        scale = 1.0;
        viewMatrixDown = glm::scale(glm::mat4(1.f), glm::vec3(1.0,scale,1.0));
    }

    return viewMatrixDown;

}