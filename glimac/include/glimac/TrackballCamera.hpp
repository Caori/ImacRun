#pragma once //fait que le compilateur le compile qu'une fois

#include "glm.hpp"

namespace glimac {

class TrackballCamera {
    private:
        float _fDistance; //distance frontale par rapport au centre de la scène
        float _fLeftDistance;//distance latérale par rapport au centre de la scène
        float _fUpDistance;
        float _fAngleX; //angle fait par la caméra autour de l'axe x (haut bas)
        float _fAngleY; //angle fait par caméra autour de l'axe y (gauche droite)

    public:
        TrackballCamera(float z=10, float x=0, float y=4, float angleX=0, float angleY=0);
        ~TrackballCamera() {}

        void move(const std::string &direction, const float speed);
        void moveFront(const float delta);
        void moveLeft(const float delta);
        void setDistance(const float z);
        void setLeft(const float x);
        void setUp(const float y);
        void rotateLeft(const float degrees);
        void rotateUp(const float degrees);

        glm::mat4 getViewMatrix() const;
};

}
