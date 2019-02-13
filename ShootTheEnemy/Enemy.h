//
// Created by harun on 22.12.2018.
//

#ifndef ENEMY_H
#define ENEMY_H

#include "pch.h"
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <iostream>
using namespace std;

class Enemy {
private:
    float pos_x, pos_y;
    float speed;

public:
    Enemy();
    Enemy(float s):speed(s){};
    ~Enemy();
    void init();
    void draw();
    void setX(float x){pos_x=x;}
    float getX(){return pos_x;}
    void setY(float y){pos_y=y;}
    float getY(){return pos_y;}
    void setSpeed(float s){speed=s;}
    float getSpeed(){return speed;}
    float getLeft(){return pos_x - 0.125f;}
    float getRight(){return pos_x + 0.125f;}
    float getTop(){return pos_y + 0.125f;}
    float getBottom(){return pos_y - 0.125f;}

    friend ostream &operator<<(ostream &os, Enemy &e){
        os << "Enemy Position X: " << e.getX() << endl;
        os << "Enemy Position Y: " << e.getY() << endl;
        os << "Enemy Speed: " << e.getSpeed() << endl;
        return os;
    }
};


#endif //ENEMY_H
