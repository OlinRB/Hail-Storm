#include "graphics.h"
#include "circle.h"
#include "rect.h"
#include "Triang.h"
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

GLdouble width, height;
int wd;
int hailCaught = 0;
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

vector<unique_ptr<Shape>> clouds;
Rect grass;
int endCnt = 0;
int moveCar = 0;
int carTimer = 0;
int lightningTimer = 0;
int tempLightning;
int hailSpeed = 1;
int clickX, clickY;
int levelTimer = 0;
int level = 1;
bool inLevel = false;
vector<Rect> road;
vector<Triang> lightning;
vector<Circle> targets;
vector<int> carXpos;
vector<int> levels{2,3,4,5};

vector<unique_ptr<Shape>> targetsPtr;
Rect user;
vector<unique_ptr<Shape>> car;
vector<unique_ptr<Shape>> startCar;

char gameMode = 'H';



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

void initLightning() {
    lightning.push_back(Triang(yellow, 79,145, dimensions1(10, 70), "down"));
    lightning.push_back(Triang(yellow, 73,182, dimensions1(10, 70), "down"));

    lightning.push_back(Triang(yellow, 272,190, dimensions1(8, 60), "down"));
    lightning.push_back(Triang(yellow, 277,217, dimensions1(10, 70), "down"));

    lightning.push_back(Triang(yellow, 436,150, dimensions1(11, 80), "down"));
    lightning.push_back(Triang(yellow, 430,188, dimensions1(10, 70), "down"));

//    lightning.push_back(Triang(yellow, 500,150, dimensions1(11, 80), "down"));
//    lightning.push_back(Triang(yellow, 500,188, dimensions1(10, 70), "down"));

}

void initCar() {
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
    // Draw grass
//    int roadHeight = 400;
//    glColor3f(91/255.0, 92/255.0, 88/255.0);
//    glBegin(GL_QUADS);
//    glVertex2i(0, grassHeight);
//    glVertex2i(width, grassHeight);
//    glVertex2i(width, height);
//    glVertex2i(0, height);
    road.push_back(Rect(asphault, width/2, 600, dimensions(width, 400)));
    road.push_back(Rect(yellow, 50, 450, dimensions(100, 20)));
    road.push_back(Rect(yellow, 200, 450, dimensions(100, 20)));
    road.push_back(Rect(yellow, 350, 450, dimensions(100, 20)));
    road.push_back(Rect(yellow, 500, 450, dimensions(100, 20)));
}

void initClouds() {
    // Note: the Rect objects that make up the flat bottom of the clouds
    // won't appear until you implement the Rect::draw method.
    clouds.clear();
    dimensions cloudBottom(105, 60);
    // First cloud
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
//    // Second cloud
    int transform = 55;
    clouds.push_back(make_unique<Circle>(cloudGrey, x1 + transform, y, radius));
    clouds.push_back(make_unique<Circle>(cloudGrey, x2 + transform, y, radius));
    clouds.push_back(make_unique<Circle>(cloudGrey, x3 + transform, y2, radius));
    clouds.push_back(make_unique<Rect>(cloudGrey, cloudX + transform, 80, cloudBottom));
//    // Third cloud
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
    initClouds();
    initBackground();
    initRoad();
    initUser();
    initCar();
    initTargets();
    initLightning();
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
        string message = "WELCOME TO HAIL STORM";
        glColor3f(1, 0, 0);
        glRasterPos2i(90, 150);
        for (char letter : message) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }

        ++carTimer;


    }

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

    if (gameMode == 'P') {
        for (int i = 0; i < car.size(); ++i) {
            car[i]->setCenterX(carXpos[i]);
        }
        carTimer = 0;
        // Draw road
        for (Rect &r : road) {
            r.draw();
        }

        // Draw clouds
        for (unique_ptr<Shape> &s : clouds) {
            s->draw();
        }

            // Draw Lightning
        if (rand() % 35 == 12){
            for (int i = 0; i < rand() % lightning.size(); ++i) {
                lightning[rand() % lightning.size()].draw();
            }
        }

        // Draw car
        for (unique_ptr<Shape> &part : car) {
            part->draw();
        }

        for (Circle &target : targets) {
            target.draw();
        }

        for (Circle &s : targets) {
            if (s.isOverlapping(user)) {
                s.setColor(darkBlue);
            } else {
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
                if (s.isOverlapping(*c)) {
                    gameMode = 'E';
                }
            }
        }

        string message = "You have caught " + to_string(hailCaught) + " pieces of hail!";
        glColor3f(0, 0, 0);
        glRasterPos2i(0, 10);
        for (char letter : message) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        tempLightning = hailCaught;
        if (hailCaught != 0 && hailCaught % 25 == 0) {
            ++level;

        }
        ++lightningTimer;
        message = "LEVEL:  " + to_string(level);
        glColor3f(0, 0, 0);
        glRasterPos2i(0, height);
        for (char letter : message) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, letter);
        }
//        message = "You clicked the mouse at coordinate (" + to_string(clickX) + ", " + to_string(clickY) + ")";
//        glColor3f(1, 1, 1);
//        glRasterPos2i(0, height);
//        for (char letter : message) {
//            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
//        }

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
            break;

        }
        case 104: {
            gameMode = 'H';
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

void levelTime(int dummy) {
    ++level;
    glutPostRedisplay();
    glutTimerFunc(20000, levelTime, dummy);
}

void targetTimer(int dummy) {

    if (gameMode == 'P') {
        for (Circle &s : targets) {
            s.setCenterY(s.getCenterY() + hailSpeed);
        }
    }

    
    glutPostRedisplay();
    glutTimerFunc(50, targetTimer, dummy);
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
    
    // Enter the event-processing loop
    glutMainLoop();

    return 0;
}
