#pragma once

#include <iostream>
#include <math.h>
#include <GL/glu.h>
#include <GL/gl.h>

class Camera {
private:
    float x, y, z;
    float up_x, up_y, up_z;
    float focus_x, focus_y, focus_z;

public:
    Camera();
    ~Camera();

    void move(float vx, float vy);
    void rotate(float rx, float ry);
    void zoom(float scroll);
private:
    void update();
};
