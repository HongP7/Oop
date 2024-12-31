// Transform.h
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vector>
#include <string>

struct Transform {
    float translateX;
    float translateY;
    float scaleX;
    float scaleY;
    float rotate;

    Transform() : translateX(0), translateY(0), scaleX(1), scaleY(1), rotate(0) {}
    Transform(float tx, float ty, float sx, float sy, float r) :
        translateX(tx), translateY(ty), scaleX(sx), scaleY(sy), rotate(r) {
    }
};

#endif // TRANSFORM_H
