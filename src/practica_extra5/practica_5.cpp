
#include <iostream>
#include "build.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "getbmp.h"


using namespace std;

static unsigned int texture[4]; // Array of texture indices.

double aumentoZ = -15.00;


GLUquadric* carcasa= gluNewQuadric();
GLUquadric* membrana = gluNewQuadric();
GLUquadric* base = gluNewQuadric();
GLUquadric* aro = gluNewQuadric();


GLfloat angleX = 0;

GLfloat angleY = 0;

GLfloat angleZ = 0;

static float R = 2.0; // Radius of hemisphere.
static int p = 20; // Number of longitudinal slices.
static int q = 4; // Number of latitudinal slices.

/*scalex - scaling of sphere around x-axis
   scaley - scaling of sphere around y-axis
   r - radius of sphere
  */
void drawHalfSphere() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    int  i, j;
    // Array of latitudinal triangle strips, each parallel to the equator, stacked one
    // above the other from the equator to the north pole.
    for(j = 0; j < q; j++)
    {
        // One latitudinal triangle strip.
        glBegin(GL_TRIANGLE_STRIP);
        for(i = 0; i <= p; i++)
        {
            glVertex3f( R * cos( (float)(j+1)/q * PI/2.0 ) * cos( 2.0 * (float)i/p * PI ),
                        R * sin( (float)(j+1)/q * PI/2.0 ),
                        R * cos( (float)(j+1)/q * PI/2.0 ) * sin( 2.0 * (float)i/p * PI ) );
            glVertex3f( R * cos( (float)j/q * PI/2.0 ) * cos( 2.0 * (float)i/p * PI ),
                        R * sin( (float)j/q * PI/2.0 ),
                        R * cos( (float)j/q * PI/2.0 ) * sin( 2.0 * (float)i/p * PI ) );
            glTexCoord2f(sin( (float)(j+1)/q * PI/2.0 ),
                         cos( (float)(j+1)/q * PI/2.0 ) * sin( 2.0 * (float)i/p * PI ) );
            glTexCoord2f(sin( (float)j/q * PI/2.0 ),
                         cos( (float)j/q * PI/2.0 ) * sin( 2.0 * (float)i/p * PI ) );
        }
        glEnd();
    }
}

// Load launch image as a texture.
void loadExternalTextures()
{
    BitMapFile *image[1];
    image[0] = getbmp("/home/angel/PycharmProjects/practicas-graficacion/src/practica_extra5/texture1.bmp");
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->sizeX, image[0]->sizeY, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    BitMapFile *image2[1];
    image2[0] = getbmp("/home/angel/PycharmProjects/practicas-graficacion/src/practica_extra5/texture_membrana.bmp");
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image2[0]->sizeX, image2[0]->sizeY, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image2[0]->data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    BitMapFile *image3[1];
    image3[0] = getbmp("/home/angel/PycharmProjects/practicas-graficacion/src/practica_extra5/texture_membrana.bmp");
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image3[0]->sizeX, image3[0]->sizeY, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image3[0]->data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    BitMapFile *image4[1];
    image4[0] = getbmp("/home/angel/PycharmProjects/practicas-graficacion/src/practica_extra5/sphere.bmp");
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image4[0]->sizeX, image4[0]->sizeY, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image4[0]->data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


}

// Drawing routine.
void drawScene(void)
{
    glutPostRedisplay();
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glLoadIdentity();
    // Viewing transformation.
    gluLookAt(0.0, 0.0, aumentoZ,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    glPopMatrix();
    glRotatef(90,1,0,0);
    glRotatef(angleX, 1,0,0);
    glRotatef(angleY, 1,0,0);
    glRotatef(angleZ, 0,0,1);

    //dibujado de carcaza
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    gluQuadricTexture(carcasa,1);
    gluQuadricNormals(carcasa,GLU_SMOOTH);
    gluCylinder(carcasa, 5,2,3,20,20);
    // DIBJUANDO LA MEMBRANA
    gluQuadricTexture(membrana, 2);
    gluQuadricNormals(membrana,GLU_SMOOTH);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    gluCylinder(membrana,4,1.5,3,20,20);
    gluQuadricTexture(aro, 2);
    gluQuadricNormals(aro,GLU_SMOOTH);
    gluCylinder(aro,4,5,0.0,20,20);
    //dibujando la base
    glTranslatef(0.0,0.0,3.0);
    gluQuadricTexture(base, 3);
    gluQuadricNormals(base,GLU_SMOOTH);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    gluCylinder(base,2,2,1.5,20,20);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glRotatef(-90, 1,0,0);
    drawHalfSphere();
    glPopMatrix();
    glFlush();
}


// Initialization routine.
void setup(void)
{
    // Enable depth testing and the vertex and texture coordinates arrays.
//    glEnable(GL_DEPTH_TEST);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glClearColor(1.0, 1.0, 1.0, 0.0);

    // Create texture ids.
    // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGenTextures.xhtml
    glGenTextures(3, texture);

    // Load launch texture.
    loadExternalTextures();

    // Specify how texture values combine with current surface color values.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Turn on OpenGL texturing.
    glEnable(GL_TEXTURE_2D);

}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5.0, 5.0, -5.0, 5.0, 10.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch(key)
    {
        case '+':
            angleY +=5;
            if(angleY >=360)
                angleY = 0;
            drawScene();
            break;
        case '-':
            angleY -=5;
            if(angleY <0)
                angleY = 360;
            drawScene();
            break;
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

// Main routine.
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitContextVersion(2, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Practica 5");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}

