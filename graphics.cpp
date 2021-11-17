#include "graphics.h"
#include "circle.h"
#include "rect.h"
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

GLdouble width, height;
int wd;
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

vector<unique_ptr<Shape>> clouds;
Rect grass;
int clickX, clickY;
vector<Rect> buildings1;
vector<Rect> buildings2;
vector<Rect> buildings3;
vector<Circle> targets;
vector<Circle> targetsTemp;
vector<unique_ptr<Shape>> targetsPtr;
Rect user;
vector<unique_ptr<Shape>> car;



void initBackground() {
    grass.setCenter(250, 450);
    grass.setSize(width, height/3);
    grass.setColor(grassGreen);
}

void initTargets() {
    for (int i = 0; i < 5; ++i) {
        targets.push_back(Circle(white, rand() % 400, rand() % 101+50, rand() % 15 + 5));
    }
    for (int i = 0; i < 5; ++i) {
        targetsPtr.push_back(make_unique<Circle>(white, rand() % 400, rand() % 400, rand() % 30 + 15));
    }

}

void initCar() {
    dimensions carBody(350,50);
    car.push_back(make_unique<Rect>(brickRed, 250, 400, carBody));
    car.push_back(make_unique<Circle>(black, 340, 425, 40));
    car.push_back(make_unique<Circle>(black, 160, 425, 40));
}
void initUser() {
    // TODO: Initialize the user to be a 20x20 white block
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
    //initClouds();
    initBackground();
    //initBuildings();
    initUser();
    initCar();
    initTargets();
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(skyBlue.red, skyBlue.green, skyBlue.blue, 1.0f);
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


    // Draw grass
    int grassHeight = 400;
    glColor3f(0,1,0);
    glBegin(GL_QUADS);
    glVertex2i(0, grassHeight);
    glVertex2i(width, grassHeight);
    glVertex2i(width, height);
    glVertex2i(0, height);\

    glEnd();

    // Draw car

    for (unique_ptr<Shape> &part : car) {
        part->draw();
    }

    for (Circle &target : targets) {
        target.draw();
    }
//    for (unique_ptr<Shape> &t : targetsPtr) {
//        t->draw();
//    }

//    for (int i = 0; i < targetsPtr.size(); ++i) {
//        if (targetsPtr.size() == 0) {
//            break;
//        }
//        if (targetsPtr[i]->isOverlapping(user)) {
//            targetsPtr[i]->setColor(darkBlue);
//            //targetsPtr.erase(targetsPtr.begin()+i);
//        }
//        else {
//            targetsPtr[i]->setColor(brickRed);
//        }
//        targetsPtr[i]->draw();
//    }

    for (Circle &s : targets) {
        if (s.isOverlapping(user)) {
            s.setColor(darkBlue);
        }
        else {
            s.setColor(brickRed);
        }
        s.draw();
    }

//    targetsTemp.clear();
    if (targets.size() > 0) {
        int iterator = targets.size();
        for (int i = 0; i < iterator; ++i) {
            if (targets[i].isOverlapping(user)) {
                targets[i].setColor(brickRed);
                if ((clickX > targets[i].getLeftX() && clickX < targets[i].getRightX() &&
                clickY > targets[i].getTopY() && clickY < targets[i].getBottomY())) {
                    targets.erase(targets.begin() + i);
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


    // Check if the user is overlapping with the cloud
    // Only check the Rect object within the cloud
    for (int i = 0; i < targets.size(); ++i) {
        if (dynamic_cast<Shape&>(targets[i]).isOverlapping(grass)){
            string message = "GAME OVER";
            glColor3f(0, 0, 0);
            glRasterPos2i(150, 150);
            cout << "Yes" << endl;
            for (char letter : message) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
            }
            //_sleep(5000);
            glutDestroyWindow(wd); // put in timer
            exit(0);
        }
    }

//    string message = "GAME OVER";
//    glColor3f(1, 0, 0);
//    glRasterPos2i(150, 150);
//    for (char letter : message) {
//        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
//    }
    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
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
    // TODO: Set the user's center point to be the coordinates
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


void targetTimer(int dummy) {

//    for (unique_ptr<Shape> &s : targetsPtr) {
//
//    }
    for (Circle &s : targets) {
        s.setCenterY(s.getCenterY() + 1);
    }

    
    glutPostRedisplay();
    glutTimerFunc(50, targetTimer, dummy);
}

void buildingTimer(int dummy) {
    // TODO: Make the other two vectors of buildings move.
    // The larger the buildings, the slower they should move.

    for (int i = 0; i < buildings1.size(); ++i) {
        // Move all the red buildings to the left
        buildings1[i].moveX(-3);
        // If a shape has moved off the screen
        if (buildings1[i].getCenterX() < -(buildings1[i].getWidth()/2)) {
            // Set it to the right of the screen so that it passes through again
            int buildingOnLeft = (i == 0) ? buildings1.size()-1 : i - 1;
            buildings1[i].setCenterX(buildings1[buildingOnLeft].getCenterX() + buildings1[buildingOnLeft].getWidth()/2 + buildings1[i].getWidth()/2 + 5);
        }
    }
    for (int i = 0; i < buildings2.size(); ++i) {
        // Move all the blue buildings to the left
        buildings2[i].moveX(-2);
        // If a shape has moved off the screen
        if (buildings2[i].getCenterX() < -(buildings2[i].getWidth()/2)) {
            // Set it to the right of the screen so that it passes through again
            int buildingOnLeft = (i == 0) ? buildings2.size()-1 : i - 1;
            buildings2[i].setCenterX(buildings2[buildingOnLeft].getCenterX() + buildings2[buildingOnLeft].getWidth()/2 + buildings2[i].getWidth()/2 + 5);
        }
    }
    for (int i = 0; i < buildings3.size(); ++i) {
        // Move all the purple buildings to the left
        buildings3[i].moveX(-1);
        // If a shape has moved off the screen
        if (buildings3[i].getCenterX() < -(buildings3[i].getWidth()/2)) {
            // Set it to the right of the screen so that it passes through again
            int buildingOnLeft = (i == 0) ? buildings3.size()-1 : i - 1;
            buildings3[i].setCenterX(buildings3[buildingOnLeft].getCenterX() + buildings3[buildingOnLeft].getWidth()/2 + buildings3[i].getWidth()/2 + 5);
        }
    }


    glutPostRedisplay();
    glutTimerFunc(30, buildingTimer, dummy);
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
    glutTimerFunc(0, buildingTimer, 0);
    
    // Enter the event-processing loop
    glutMainLoop();

    return 0;
}
