#ifndef GAME_H
#define GAME_H

#include "pch.h"
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <random>
#include "Player.h"
#include "Enemy.h"

class Game {
private:
    static Game *gameInstance;
    Player *player;
    ArrayList<Enemy *> enemies;
    int gameWindow;
    int windowWidth  = 640;     // Windowed mode's width
    int windowHeight = 480;     // Windowed mode's height
    int windowPosX   = 50;      // Windowed mode's top-left corner x
    int windowPosY   = 50;      // Windowed mode's top-left corner y
    // Projection clipping area
    GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;
    bool fullScreenMode = false;
    bool gameOver = false;

    int score;

    void displayText( float x, float y, int r, int g, int b, const char *string );
    void timer(int);
    static void timerOfGlut(int);
    static void idle();
    void draw();
    static void drawOfGlut();
    void reshape(GLsizei width, GLsizei height);
    static void reshapeOfGlut(GLsizei width, GLsizei height);
    void keyEvent(int button, int x, int y);
    static void keyEventOfGlut(int button, int x, int y);
    void keyEvent(unsigned char button, int x, int y);
    static void keyEventOfGlut(unsigned char button, int x, int y);
    void initObjects();
public:
    Game();
    ~Game();
    static Game *getInstance();
    void initGame(int argc, char **argv);
    void run();
};

#endif //GAME_H
