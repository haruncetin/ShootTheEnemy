//
// Created by harun on 22.12.2018.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "pch.h"
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <iostream>
#include "Bullet.h"
#include "ArrayList.h"

using namespace std;



class Player{
private:
    int health, bullet;
    float pos_y, pos_x;
    float _top, _bottom, _left, _right;
    ArrayList<Bullet *> bullets;
public:
    Player();
    ~Player();
    void up();
    void down();
    void draw();
    void fire();
    float getX(){return pos_x;}
    float getY(){return pos_y;}
    float getLeft(){return pos_x - 0.125f;}
    float getRight(){return pos_x + 0.125f;}
    float getTop(){return pos_y + 0.125f;}
    float getBottom(){return pos_y - 0.125f;}
    ArrayList<Bullet *> getBullets();
};

#endif //PLAYER_H
