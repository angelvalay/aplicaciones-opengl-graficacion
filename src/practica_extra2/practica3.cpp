
#include <cstdlib>
#include <vector>
#include <iostream>
#  include <GL/glew.h>
#  include <GL/freeglut.h>

// Use the STL extension of C++.
using namespace std;

// Globals.
static int width, height; // OpenGL window size.
static float pointSize = 20.0; // Size of point

// Point class.
class Point
{
public:
    Point(int x, int y)
    {
        xVal = x; yVal = y;
    }
    Point(){};
    void setCoords(int x, int y)
    {
        xVal = x; yVal = y;
    }
    int getCoordX(){
        return xVal;
    }
    int getCoordY(){
        return yVal;
    }
    void drawPoint(void); // Function to draw a point.
private:
    int xVal, yVal; // x and y co-ordinates of point.
    static float size; // Size of point.
};

float Point::size = pointSize; // Set point size.

static Point letterM[12] = {
    Point(100,100), Point(150,100), Point(150,350), Point(250,250),
    Point(350,350), Point(350,100), Point(400,100), Point(400,450),
    Point(350,450), Point(250,325), Point(150,450),Point(100,450)

};

// Function to draw a point.
void Point::drawPoint(void)
{
    glPointSize(size);
    glBegin(GL_POINTS);
    glVertex3f(xVal, yVal, 0.0);
    glEnd();
}


static int isWithInLetter(Point point, Point letter[], int length){
    // delimitadores
    int iXMin = letter[0].getCoordX();
    int iXMax = letter[0].getCoordX();
    int iYMin = letter[0].getCoordY();
    int iYMax = letter[0].getCoordY();
    for (int i = 0; i < length; ++i) {
        if(letter[i].getCoordX() > iXMax){
            iXMax = letter[i].getCoordX();
        }else if(letter[i].getCoordX() < iXMin){
            iXMin = letter[i].getCoordX();
        }

        if(letter[i].getCoordY() > iYMax){
            iYMax = letter[i].getCoordY();
        }else if(letter[i].getCoordY() < iYMin){
            iYMin = letter[i].getCoordY();
        }
    }
    if ((point.getCoordX() > iXMin && point.getCoordX() < iXMax) &&
        (point.getCoordY() > iYMin && point.getCoordY() < iYMax)){
        /*Line segment*/
        int j = length - 1;
        int inter = 0;
        for (int i = 0; i < length; ++i) {
            if((point.getCoordY() > letter[i].getCoordY()
                && point.getCoordY() <= letter[j].getCoordY())||
               (point.getCoordY() <= letter[i].getCoordY()
                && point.getCoordY() > letter[j].getCoordY())){
                if(((point.getCoordY() - letter[i].getCoordY())
                    *((letter[j].getCoordX() - letter[i].getCoordX())/
                      (letter[j].getCoordY() - letter[i].getCoordY())) + letter[i].getCoordX())
                   < point.getCoordX()){
                    inter++;
                }
            }
            j = i;
        }
        return inter != 0;
    }else{
        return false;
    }
}

// Vector of points.
vector<Point> points;

// Iterator to traverse a Point array.
vector<Point>::iterator pointsIterator;

// Is or not pressed the mouse left.
int isPressed;

// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    // Loop through the points array drawing each point.
    pointsIterator = points.begin();
    while(pointsIterator != points.end() )
    {
        pointsIterator->drawPoint();
        pointsIterator++;
    }

    glBegin(GL_LINE_LOOP);
    glPointSize(1);
    glColor3f(0.5,0.5,0.5);
    for (int i = 0; i < 12; ++i) {
        glVertex3i(letterM[i].getCoordX(), letterM[i].getCoordY(),0);
    }
    glEnd();
    glFlush();
}

// Mouse callback routine.
void mouseControl(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isPressed = 1;
        }
        if (state == GLUT_UP) {
            isPressed = 0;
        }
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) exit(0);

    glutPostRedisplay();
}

// Mouse motion callback routine.
void mouseMove( int x, int y)
{
    // Update the location of the current point as the mouse moves with button pressed.
    if (isPressed)
        points.emplace_back(x, height - y );

    glutPostRedisplay();
}

// Initialization routine.
void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport (0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set viewing box dimensions equal to window dimensions.
    glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

    // Pass the size of the OpenGL window to globals.
    width = w;
    height = h;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
    cout << "Interaction:" << endl;
    cout << "Left mouse click to draw a square point, keep left button pressed to drag point," << endl
         << "right mouse click to exit." << endl;
}



// Main routine.
int main(int argc, char **argv) {
    printInteraction();
    glutInit(&argc, argv);

    glutInitContextVersion(2, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("mouseMotion.cpp");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    // Register the mouse callback function.
    glutMouseFunc(mouseControl);

    // Register the mouse motion callback function.
    glutMotionFunc(mouseMove);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}