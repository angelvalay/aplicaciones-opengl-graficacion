GLdouble base1[8][3]={
        {4,7,0},
        {4,7,0.5},
        {3.5,7,0},
        {3.5,7,0.5},
        {-4,7,0},
        {-4,7,0.5},
        {-3.5,7,0},
        {-3.5,7,0.5}
};


void DibujarBase1 ()
{
    glColor3f(1.0,0.0,1.0);
    glBegin(GL_POLYGON);
    glVertex3dv(base1[0]);
    glVertex3dv(base1[1]);
    glVertex3dv(base1[5]);
    glVertex3dv(base1[4]);
    glEnd();
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINES);
    glVertex3dv(base1[2]);
    glVertex3dv(base1[3]);
    glVertex3dv(base1[7]);
    glVertex3dv(base1[6]);
    glEnd();
}
