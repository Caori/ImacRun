#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/TrackballCamera.hpp"

namespace glimac {

TrackballCamera::TrackballCamera()
    : _fDistance(5), _fLeftDistance(0), _fAngleX(0), _fAngleY(0) 
{}

void TrackballCamera::move(const std::string &direction, const float speed){
    if (direction == "NORD"){
       moveFront(-speed);
    }
    if (direction == "SUD"){
        moveFront(speed);
    }
    if (direction == "OUEST"){
       moveLeft(speed);
    }
    if (direction == "EST"){
        moveLeft(-speed);
    }
}

void TrackballCamera::moveFront(const float delta){
    _fDistance+=delta;
}

void TrackballCamera::moveLeft(const float delta){
    _fLeftDistance+=delta;
}

void TrackballCamera::rotateLeft(const float degrees) {
    _fAngleY += degrees;
}

void TrackballCamera::rotateUp(const float degrees) {
    _fAngleX += degrees;
}

glm::mat4 TrackballCamera::getViewMatrix() const {
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.f), glm::vec3(-_fLeftDistance, 0, -_fDistance));
    glm::mat4 rotationXMatrix = glm::rotate(glm::mat4(1.f), glm::radians(_fAngleX), glm::vec3(1, 0, 0));
    glm::mat4 rotationYMatrix = glm::rotate(glm::mat4(1.f), glm::radians(_fAngleY), glm::vec3(0, 1, 0));

    glm::mat4 ViewMatrix = translationMatrix*rotationXMatrix*rotationYMatrix;

    return ViewMatrix;
}

}
