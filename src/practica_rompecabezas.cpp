//
// Created by angel on 28/10/19.
//
#import "core/Librerias.h"
void drawScene(){
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(0.0, 0.0, 10, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glColor3f(0,0,1);
    glPointSize(10);
    glBegin(GL_POLYGON);
    glVertex3d(7,-7,0);
    glVertex3d(-7,-7,0);
    glVertex3d(-7,7,0);
    glVertex3d(7,7,0);
    glEnd();

    glPointSize(2);
    glBegin(GL_POINTS);
    glEnd();
    glutSwapBuffers();
}

void resize(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-10.0, 10.0, -5.0, 5.0, 5.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y){

}

void confiInitial(){
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1000, 500);
    glutInitWindowPosition(5, 5);
    glutCreateWindow("compareFilters.cpp");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    confiInitial();

    glutMainLoop();
}
