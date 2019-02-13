//
// Created by harun on 22.12.2018.
//
#include "pch.h"
#include "Player.h"

Player::Player() {
    pos_y = 0.0f;
    pos_x = -1.0f;
    health = 100;
    bullet = 1000;
    cout << "Player created." << endl;
}

void Player::up() {
    pos_y = pos_y + .125f;
}
void Player::down() {
    pos_y = pos_y - .125f;
}

void Player::draw() {
    glColor3f(0.0f,0.0f,1.0f);
    glPushMatrix();
    glTranslatef(pos_x, pos_y, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f,-.125f);
    glVertex2f(.125f, 0.0f);
    glVertex2f(0.0f, .125f);
    glEnd();
    glPopMatrix();
}

Player::~Player() {
    cout << "Player destroyed." << endl;
}

void Player::fire() {
    Bullet *bullet = new Bullet(pos_x + 0.25f, pos_y);
    bullets.insert(bullet);
}

ArrayList<Bullet *> Player::getBullets() {
    return bullets;
}

