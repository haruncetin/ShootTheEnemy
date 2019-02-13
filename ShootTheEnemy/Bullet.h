//
// Created by harun on 22.12.2018.
//

#ifndef BULLET_H
#define BULLET_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <iostream>
#include "ArrayList.h"

using namespace std;

class Bullet {
private:
    float pos_x, pos_y;
    void DrawCircle(float cx, float cy, float r, int num_segments);

public:
    Bullet(float x, float y);
    ~Bullet();
    void init();
    void draw();
    float getX();
    float getY();
    float getLeft(){return pos_x - 0.125f;}
    float getRight(){return pos_x + 0.125f;}
    float getTop(){return pos_y + 0.125f;}
    float getBottom(){return pos_y - 0.125f;}

};


#endif //BULLET_H
