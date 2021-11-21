#include "graphics.h"
#include "circle.h"
#include "rect.h"
#include "Triang.h"
#include <iostream>
#include <memory>
#include <ctime>
#include <vector>
using namespace std;


/**
 * HAIL STORM
 *
 * This game is generated using OpenGL and GLUT
 *
 * The objective is to not let the hail hit the
 * racecar. The user must hover over the hail
 * and click the left button to catch it.
 * Hovering over the hail will change the
 * hail color to red to indicate a correct
 * hover.
 *
 * If the user survives 5 rounds, the car
 * drives away from the storm.
 *
 *
 *
 */


/**
 * COLORS
 */
const color skyBlue(77/255.0, 213/255.0, 240/255.0);
const color grassGreen(26/255.0, 176/255.0, 56/255.0);
const color white(1, 1, 1);
const color brickRed(201/255.0, 20/255.0, 20/255.0);
const color darkBlue(1/255.0, 110/255.0, 214/255.0);
const color purple(119/255.0, 11/255.0, 224/255.0);
const color black(0, 0, 0);
const color magenta(1, 0, 1);
const color orange(1, 163/255.0, 22/255.0);
const color cyan (0, 1, 1);
const color cloudGrey (100/255.0, 100/255.0, 100/255.0, 1);
const color yellow (1,1,0,1);
const color asphault (91/255.0, 92/255.0, 88/255.0, 1);

/**
 * GLOBAL GAME VARIABLES
 */
GLdouble width, height;
int wd;
int hailCaught = 0;
vector<unique_ptr<Shape>> clouds;
int endCnt = 0;
int moveCar = 0;
int carTimer = 0;
int lightningTimer = 0;
double hailSpeed = 0;
int clickX, clickY;
int level = 1;
bool driveAway = false;
vector<Rect> road;
vector<Triang> lightning;
vector<Circle> targets;
vector<int> carXpos;


Rect user;
vector<unique_ptr<Shape>> car;

char gameMode = 'H';



void initBackground() {
}

void initTargets() {
    // Add hail
    for (int i = 0; i < 5; ++i) {
        targets.push_back(Circle(white, rand() % 400, rand() % 101+50, rand() % 15 + 5));
    }

}

void initLightning() {
    // Add lightning
    lightning.push_back(Triang(yellow, 79,145, dimensions1(10, 70), "down"));
    lightning.push_back(Triang(yellow, 73,182, dimensions1(10, 70), "down"));

    lightning.push_back(Triang(yellow, 272,190, dimensions1(8, 60), "down"));
    lightning.push_back(Triang(yellow, 277,217, dimensions1(10, 70), "down"));

    lightning.push_back(Triang(yellow, 436,150, dimensions1(11, 80), "down"));
    lightning.push_back(Triang(yellow, 430,188, dimensions1(10, 70), "down"));

}

void initCar() {
    // Create car
    dimensions carBody(350,50);
    car.push_back(make_unique<Rect>(brickRed, 250, 400, carBody));
    car.push_back(make_unique<Circle>(black, 340, 425, 40));
    car.push_back(make_unique<Circle>(black, 160, 425, 40));
    car.push_back(make_unique<Triang>(brickRed, 389, 355, dimensions1(70,40), "right"));
    carBody = {285,40};
    car.push_back(make_unique<Rect>(brickRed, 218, 355, carBody));
    car.push_back(make_unique<Triang>(white, 285, 310, dimensions1(60,55), "right"));
    car.push_back(make_unique<Rect>(white, 215, 310, dimensions(85, 55)));
    car.push_back(make_unique<Triang>(white, 145, 310, dimensions1(60,55),"left"));
    car.push_back(make_unique<Triang>(brickRed, 95, 310, dimensions1(40, 80), "right"));
    car.push_back(make_unique<Triang>(brickRed, 80, 270, dimensions1(90, 60), "right"));
    for (unique_ptr<Shape> &part : car) {
        carXpos.push_back(part->getCenterX());
    }

}

void initRoad() {
    // Create road
    road.push_back(Rect(asphault, width/2, 600, dimensions(width, 400)));
    road.push_back(Rect(yellow, 50, 450, dimensions(100, 20)));
    road.push_back(Rect(yellow, 200, 450, dimensions(100, 20)));
    road.push_back(Rect(yellow, 350, 450, dimensions(100, 20)));
    road.push_back(Rect(yellow, 500, 450, dimensions(100, 20)));
    road.push_back(Rect(yellow, 650, 450, dimensions(100, 20)));
    road.push_back(Rect(yellow, 800, 450, dimensions(100, 20)));
    road.push_back(Rect(yellow, 950, 450, dimensions(100, 20)));
    road.push_back(Rect(yellow, 1100, 450, dimensions(100, 20)));
    road.push_back(Rect(yellow, 1250, 450, dimensions(100, 20)));
    road.push_back(Rect(yellow, 1400, 450, dimensions(100, 20)));
    road.push_back(Rect(yellow, 1550, 450, dimensions(100, 20)));
    road.push_back(Rect(yellow, 1700, 450, dimensions(100, 20)));
    road.push_back(Rect(yellow, 1850, 450, dimensions(100, 20)));
}

void initClouds() {
    // Create clouds
    clouds.clear();
    dimensions cloudBottom(105, 60);
    int radius = 40;
    int y = 70;
    int y2 = 50;
    int x1 = 50;
    int x2 = 150;
    int x3 = 95;
    int cloudX = 100;
    clouds.push_back(make_unique<Circle>(cloudGrey, x1, y, radius));
    clouds.push_back(make_unique<Circle>(cloudGrey, x2, y, radius));
    clouds.push_back(make_unique<Circle>(cloudGrey, x3, y2, radius));
    clouds.push_back(make_unique<Rect>(cloudGrey, cloudX, 80, cloudBottom));

    int transform = 55;
    clouds.push_back(make_unique<Circle>(cloudGrey, x1 + transform, y, radius));
    clouds.push_back(make_unique<Circle>(cloudGrey, x2 + transform, y, radius));
    clouds.push_back(make_unique<Circle>(cloudGrey, x3 + transform, y2, radius));
    clouds.push_back(make_unique<Rect>(cloudGrey, cloudX + transform, 80, cloudBottom));

    transform = 260;
    clouds.push_back(make_unique<Circle>(cloudGrey, x1 + transform, y, radius));
    clouds.push_back(make_unique<Circle>(cloudGrey, x2 + transform, y, radius));
    clouds.push_back(make_unique<Circle>(cloudGrey, x3 + transform, y2, radius));
    clouds.push_back(make_unique<Rect>(cloudGrey, cloudX + transform, 80, cloudBottom));
    transform = 180;
    clouds.push_back(make_unique<Circle>(cloudGrey, x1 + transform, y + 50, radius));
    clouds.push_back(make_unique<Circle>(cloudGrey, x2 + transform, y + 50, radius));
    clouds.push_back(make_unique<Circle>(cloudGrey, x3 + transform, y2 + 50, radius));
    clouds.push_back(make_unique<Rect>(cloudGrey, cloudX + transform, 80 + 50, cloudBottom));

    transform = 330;
    clouds.push_back(make_unique<Circle>(cloudGrey, x1 + transform, y, radius));
    clouds.push_back(make_unique<Circle>(cloudGrey, x2 + transform, y, radius));
    clouds.push_back(make_unique<Circle>(cloudGrey, x3 + transform, y2, radius));
    clouds.push_back(make_unique<Rect>(cloudGrey, cloudX + transform, 80, cloudBottom));
}
void initUser() {
    // centered in the top left corner of the graphics window
    user.setSize(5,5);
    user.setColor(0,0,0,1);
    user.setCenter(0,0);
}

void init() {
    width = 500;
    height = 500;
    clickX = clickY = 0;
    srand(time(0));
    initClouds();
    initBackground();
    initRoad();
    initUser();
    initCar();
    initTargets();
    initLightning();
    //startTime = time(0);

}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0, 0, 0, 1.0f);
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE (unless you are running Catalina on Mac)

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

    // HOME SCREEN
    if (gameMode == 'H') {
        // Draw road
        for (Rect &r : road) {
            r.draw();
        }
        // Draw car
        for (unique_ptr<Shape> &part : car) {
            part->setCenterX(part->getCenterX() + moveCar);
            part->draw();
        }
        if (carTimer > 50)
            ++moveCar;

        if (carTimer > 50) {
            if (carTimer % 25 != 0 && carTimer % 25 != 1) {
                string message = "PRESS p TO PLAY";
                glColor3f(1, 0, 0);
                glRasterPos2i(180, 225);
                for (char letter : message) {
                    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
                }
            }
        }
        string message = "WELCOME TO HAIL STORM";
        glColor3f(1, 0, 0);
        glRasterPos2i(90, 150);
        for (char letter : message) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }

        ++carTimer;
    }
    // WIN SCREEN
    if (gameMode == 'W') {
        glClearColor(135/255.0, 206/255.0, 235/255.0, 1.0f);
        ++moveCar;
        // Draw road
        for (int i = 0; i < road.size(); ++i) {
            if (driveAway) {
                if (i > 0)
                    road[i].setCenterX(road[i].getCenterX() - moveCar);
                if (road[road.size()-1].getRightX() < width)
                    gameMode = 'E';
            }
            road[i].draw();
        }
        // Draw car
        for (unique_ptr<Shape> &part : car) {
            part->setCenterX(part->getCenterX() + moveCar);
            part->draw();
        }
        string message = "YOU WIN!!!";
        glColor3f(1, 0, 0);
        glRasterPos2i(90, 150);
        for (char letter : message) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }

        ++carTimer;
    }
    // END SCREEN
    if (gameMode == 'E') {
        glClearColor(0, 0, 0, 1.0f);
        bool gameOver = true;
        string message = "GAME OVER";
        glColor3f(1, 0, 0);
        glRasterPos2i(175, 190);
        for (char letter : message) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
        endCnt += 1;
        if (gameOver && endCnt > 100) {
            glutDestroyWindow(wd);
            exit(0);
        }

    }
    // PLAY SCREEN
    if (gameMode == 'P'){

        if (!driveAway) {
            for (int i = 0; i < car.size(); ++i) {
                car[i]->setCenterX(carXpos[i]);
            }
        }
        // Set hail speed
        if (level == 1) {
            hailSpeed = .75;
        }
        else if (level == 2) {
            hailSpeed = 1;
        }
        else if (level == 3) {
            hailSpeed = 1.15;
        }
        else if (level == 4) {
            hailSpeed = 1.25;
        }
        else if (level == 5) {
            hailSpeed = 1.5;
        }
        else if (level == 6) {
            hailSpeed = 0;
            // Draw car
            driveAway = true;
        }

        // Draw road
        for (int i = 0; i < road.size(); ++i) {
            if (driveAway) {
                if (i > 0)
                    road[i].setCenterX(road[i].getCenterX() - moveCar);
                if (road[road.size()-1].getRightX() < width)
                    moveCar = 0;
                    gameMode = 'W';
            }
            road[i].draw();
        }

        // Draw clouds
        for (unique_ptr<Shape> &s : clouds) {
            if (driveAway)
                s->setCenterX(s->getCenterX() - moveCar);
            s->draw();
        }

        // Draw Lightning
        if (!driveAway) {
            if (rand() % 35 == 12) {
                for (int i = 0; i < rand() % lightning.size(); ++i) {
                    lightning[rand() % lightning.size()].draw();
                }
            }
        }
        if (driveAway)
            ++carTimer;

        // Draw car
        for (unique_ptr<Shape> &part : car) {
            if (moveCar)
                part->setCenterX(part->getCenterX() + moveCar);
            else
                part->setCenterX(part->getCenterX() + moveCar);
            part->draw();
        }
        if (carTimer > 50)
            ++moveCar;

        for (Circle &s : targets) {
            if (s.isOverlapping(user)) {
                s.setColor(darkBlue);
            } else {
                s.setColor(brickRed);
            }
            s.draw();
        }

        // Check if user catches hail
        if (targets.size() > 0) {
            int iterator = targets.size();
            for (int i = 0; i < iterator; ++i) {
                if (targets[i].isOverlapping(user)) {
                    targets[i].setColor(brickRed);
                    if ((clickX > targets[i].getLeftX() && clickX < targets[i].getRightX() &&
                         clickY > targets[i].getTopY() && clickY < targets[i].getBottomY())) {
                        targets.erase(targets.begin() + i);
                        ++hailCaught;
                        if (targets.size() == 0)
                            break;
                        targets.push_back(Circle(white, rand() % 400, rand() % 101 + 50, rand() % 15 + 5));
                        --iterator;
                    }
                } else {
                    targets[i].setColor(white);
                }
                targets[i].draw();
            }
        }
        // Draw user
        user.draw();

        // Check if hail has hit car
        for (Shape &s : targets) {
            for(unique_ptr<Shape> &c : car) {
                if (c->isOverlapping(s)) {
                    gameMode = 'E';
                }
            }
        }
        // Display hail caught
        string message = "You have caught " + to_string(hailCaught) + " pieces of hail!";
        glColor3f(0, 0, 0);
        glRasterPos2i(0, 10);
        for (char letter : message) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        // Display level
        ++lightningTimer;
        message = "LEVEL:  " + to_string(level);
        glColor3f(0, 0, 0);
        glRasterPos2i(0, height);
        for (char letter : message) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, letter);
        }
    }

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {

    switch(key) {
        case 27: {
            glutDestroyWindow(wd);
            exit(0);
        }
        case 112: {
            gameMode = 'P';
            glClearColor(190/255.0, 190/255.0, 190/255.0,1);
            moveCar = 0;
            carTimer = 0;
            break;

        }
        case 104: {
            gameMode = 'H';
            glClearColor(0, 0, 0, 1.0f);
            level = 1;
            break;
        }
    }
    
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            
            break;
        case GLUT_KEY_LEFT:
            
            break;
        case GLUT_KEY_RIGHT:
            
            break;
        case GLUT_KEY_UP:
            
            break;
    }
    
    glutPostRedisplay();
}

void cursor(int x, int y) {
    user.setCenter(x,y);
    // passed in as parameters to this function. This will make
    // the user block move with the mouse.
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    clickX = x;
    clickY = y;
    glutPostRedisplay();
}

void levelTime(int dummy) {
    ++level;
    glutPostRedisplay();
    glutTimerFunc(20000, levelTime, dummy);
}

void targetTimer(int dummy) {
    // Move hail downwards
    if (gameMode == 'P') {
        for (Circle &s : targets) {
            s.setCenterY(s.getCenterY() + hailSpeed);
        }
    }
    glutPostRedisplay();
    glutTimerFunc(50, targetTimer, dummy);
}

void driveAwayTimer(int dummy) {
    if (driveAway) {
        for (unique_ptr<Shape> &part : car) {
            part->setCenterX(part->getCenterX() + moveCar);
            if (part->getCenterX() + moveCar > width + 50)
                driveAway = false;
        }
        ++moveCar;
        glutTimerFunc(0, driveAwayTimer, dummy);

    }
}


/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    
    init();
    
    glutInit(&argc, argv);          // Initialize GLUT
    
    glutInitDisplayMode(GLUT_RGBA);
    
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("HAIL STORM" /* title */ );
    
    // Register callback handler for window re-paint event
    glutDisplayFunc(display);
    
    // Our own OpenGL initialization
    initGL();
    
    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);
    
    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);
    
    // handles mouse movement
    glutPassiveMotionFunc(cursor);
    
    // handles mouse click
    glutMouseFunc(mouse);
    
    // handles timer
    glutTimerFunc(0, targetTimer, 0);
    glutTimerFunc(20000, levelTime, 0);
    glutTimerFunc(0, driveAwayTimer, 0);
    
    // Enter the event-processing loop
    glutMainLoop();

    return 0;
}
