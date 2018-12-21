#pragma once //fait que le compilateur le compile qu'une fois

#include "glm.hpp"

namespace glimac {

class TrackballCamera {
    private:
        float _fDistance; //distance frontale par rapport au centre de la scène
        float _fLeftDistance;//distance latérale par rapport au centre de la scène
        float _fAngleX; //angle fait par la caméra autour de l'axe x (haut bas)
        float _fAngleY; //angle fait par caméra autour de l'axe y (gauche droite)

    public:
        TrackballCamera();
        ~TrackballCamera() {}

        void move(const std::string &direction, const float speed);
        void moveFront(const float delta);
        void moveLeft(const float delta);
        void rotateLeft(const float degrees);
        void rotateUp(const float degrees);

        glm::mat4 getViewMatrix() const;
};

}
