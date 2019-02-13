//
// Created by harun on 22.12.2018.
//

#include "pch.h"
#include "Bullet.h"
#include <math.h>

Bullet::Bullet(float x, float y) {
    pos_y = y;
    pos_x = x;
    cout << "Bullet created." << endl;
}

Bullet::~Bullet() {
    cout << "Bullet destroyed." << endl;
}

void Bullet::init() {

}
void Bullet::DrawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex

    }
    glEnd();
}

void Bullet::draw() {
    glColor3f(1.0f, 0.0f, 1.0f);
    glPushMatrix();
    glTranslatef(pos_x, pos_y, 0.0f);
    DrawCircle(0.0f, 0.0f , 0.0125, 90);
    glPopMatrix();
    pos_x = pos_x + 0.05f;
}

float Bullet::getX() {
    return pos_x;
}

float Bullet::getY() {
    return pos_y;
}
