//
// Created by harun on 22.12.2018.
//

#include "pch.h"
#include <random>
#include <string.h>
#include "Game.h"

using namespace std;

Game *Game::gameInstance = 0;

Game::Game() {
}

Game::~Game() {
    for (int i = 0; i < player->getBullets().getLength(); ++i) {
		Bullet *bullet = player->getBullets().get(i);
		delete bullet;
		bullet = NULL;
    }
    for (int i = 0; i < enemies.getLength(); ++i) {
		Enemy *enemy = enemies.get(i);
		delete enemy;
		enemy = NULL;
    }
    glutDestroyWindow(gameWindow);
    cout << "All game objects destroyed!" << endl;
}

void Game::run() {
    glutMainLoop();
}

void Game::timer(int)
{
    if (!gameOver) {
        /* create one enemy every 1 sec */
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> ypos(-1.0, 1.0);
        std::uniform_real_distribution<double> speed(0.005, 0.01);

        Enemy *enemy = new Enemy;
        enemy->setSpeed(speed(mt));
        enemy->setX(clipAreaXRight );
        enemy->setY(ypos(mt));
        cout << *enemy;
        enemies.insert(enemy);
        cout << "Enemy created"<< endl;
        glutTimerFunc(1000, timerOfGlut, 0);
    }
}

void Game::timerOfGlut(int time) {
    gameInstance->timer(time);
}

void Game::displayText( float x, float y, int r, int g, int b, const char *string ) {
    glColor3f(r, g, b);
    glPushMatrix();
    glTranslatef(x,y,0.0);
    glRasterPos2f(0.0, 0.0);
    int j = strlen( string );
    for( int i = 0; i < j; i++ ) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i] );
    }
    glPopMatrix();
}

void Game::draw(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-1.0f);
    char strScore[20];
    char strGameOver[10] = "Game Over";
    if (!gameOver) {
        sprintf_s(strScore, "Score: %d", score);
        displayText(-0.90, 0.90, 255, 0, 0, strScore);
        // drawing & update operations here
        player->draw();
        for (int i = 0; i < player->getBullets().getLength(); i++) {
            Bullet *bullet = player->getBullets().get(i);
            if(bullet != NULL){
                bullet->draw();
                if(bullet->getX() >= clipAreaXRight){
                    player->getBullets().remove(i);
                    //delete bullet;
                    //bullet = NULL;
                }
            }
        }
        for (int j = 0; j < enemies.getLength(); j++) {
            Enemy *enemy = enemies.get(j);
            if (enemy != NULL) {
                enemy->draw();
                if ((player->getX() >= enemy->getLeft()) && (player->getBottom() <= enemy->getTop()) && (player->getTop() >= enemy->getBottom())) {
                    gameOver = true;
                }else if (enemy->getX() < clipAreaXLeft) {
                    enemies.remove(j);
                    delete enemy;
                    //enemy = NULL;
                } else {
                    for (int i = 0; i < player->getBullets().getLength(); i++) {
                        Bullet *bullet = player->getBullets().get(i);
                        if (bullet != NULL) {
                            if ((bullet->getX() >= enemy->getX()) && (bullet->getBottom() <= enemy->getTop()) && (bullet->getTop() >= enemy->getBottom())) {
                                cout << "Bullet hit the enemy" << endl;
                                player->getBullets().remove(i);
                                //delete bullet;
                                //bullet = NULL;
                                enemies.remove(j);
                                //delete enemy;
                                //enemy = NULL;
                                score += 1;
                            }
                        }
                    }
                }
            }
        }
    }else{
		sprintf_s(strScore, "Your Score is %d", score);
        displayText(-0.25, 0.25, 255, 0, 0, strGameOver);
        displayText(-0.30, 0.0, 255, 0, 0, strScore);
    }
    glutSwapBuffers();
}

void Game::idle() {
    glutPostRedisplay();   // Post a re-paint request to activate draw()
}

void Game::initGame(int argc, char **argv) {
    score = 0;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowPosition(0,0);
    glutInitWindowSize(windowWidth, windowHeight);
    gameWindow = glutCreateWindow("Shoot The Enemy!");
    glClearColor(0,0,0,1);
    glShadeModel(GL_FLAT);
    glutDisplayFunc(drawOfGlut);
    glutIdleFunc(idle);
    glutTimerFunc(1000, timerOfGlut, 0);
    glutReshapeFunc(reshapeOfGlut);
    glutKeyboardFunc(keyEventOfGlut);
    glutSpecialFunc(keyEventOfGlut);
    initObjects();
}

/* Call back when the windows is re-sized */
void Game::reshape(GLsizei width, GLsizei height) {
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping area to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset the projection matrix
    if (width >= height) {
        clipAreaXLeft   = -1.0 * aspect;
        clipAreaXRight  = 1.0 * aspect;
        clipAreaYBottom = -1.0;
        clipAreaYTop    = 1.0;
    } else {
        clipAreaXLeft   = -1.0;
        clipAreaXRight  = 1.0;
        clipAreaYBottom = -1.0 / aspect;
        clipAreaYTop    = 1.0 / aspect;
    }
    gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
}

void Game::initObjects() {
    player = new Player;
}

Game *Game::getInstance() {
    if (gameInstance == 0){
        gameInstance = new Game;
    }
    return gameInstance;
}

void Game::drawOfGlut() {
    gameInstance->draw();
}

void Game::keyEvent(int button, int x, int y) {
    switch (button) {
        case GLUT_KEY_UP:
            player->up();
            break;
        case GLUT_KEY_DOWN:
            player->down();
            break;
        case GLUT_KEY_F11:    // F11: Toggle between full-screen and windowed mode
            fullScreenMode = !fullScreenMode;         // Toggle state
            if (fullScreenMode) {                     // Full-screen mode
                windowPosX   = glutGet(GLUT_WINDOW_X); // Save parameters for restoring later
                windowPosY   = glutGet(GLUT_WINDOW_Y);
                windowWidth  = glutGet(GLUT_WINDOW_WIDTH);
                windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
                glutFullScreen();                      // Switch into full screen
            } else {                                         // Windowed mode
                glutReshapeWindow(windowWidth, windowHeight); // Switch into windowed mode
                glutPositionWindow(windowPosX, windowPosX);   // Position top-left corner
            }
            break;
    }
    glutPostRedisplay();
}

void Game::keyEvent(unsigned char button, int x, int y) {
    switch (button) {
        case 32:
            player->fire();
            break;
    }
    glutPostRedisplay();
}

void Game::keyEventOfGlut(unsigned char button, int x, int y) {
    gameInstance->keyEvent(button, x, y);
}

void Game::keyEventOfGlut(int button, int x, int y) {
    gameInstance->keyEvent(button, x, y);
}

void Game::reshapeOfGlut(int width, int height) {
    gameInstance->reshape(width,height);
}
