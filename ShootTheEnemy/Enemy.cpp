//
// Created by harun on 22.12.2018.
//

#include "pch.h"
#include "Enemy.h"
#include <iostream>

using namespace std;

void Enemy::init() {

}

void Enemy::draw() {
    glColor3f(1.0f,0.0f,0.0f);
    glPushMatrix();
    glTranslatef(pos_x, pos_y, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.05f,0.05f);
    glVertex2f(-0.025f, 0.05f);
    glVertex2f(-0.025f, -0.05f);
    glVertex2f(0.05f, -0.05f);
    glEnd();
    glPopMatrix();

    pos_x = pos_x - speed;
}

Enemy::~Enemy() {
    cout << "Enemy destroyed" << endl;
}

Enemy::Enemy() {
    cout << "Enemy created" << endl;
}
