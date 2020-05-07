////////////////////////////////////////////////////////////////
// Department of Computer Science
// The University of Manchester
//
// This code is licensed under the terms of the Creative Commons
// Attribution 2.0 Generic (CC BY 3.0) License.
//
// Skeleton code for COMP37111 coursework, 2019-20
//
// Authors: Toby Howard and Arturs Bekasovs
//
/////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <GLUT/glut.h>

#define MAX 1000


// Display list for coordinate axis
GLuint axisList;

int AXIS_SIZE= 200;
int axisEnabled= 1;

float slowrate = 2.0;
float velocity = 0.0;


typedef struct Particle{
    float xposition; //Location of particle in X, Y, Z planes
    float yposition;
    float zposition;

    float velocity; //Only one for y direction.
    float g; //Force of gravity

    float re;
    float gr; //Colour
    float bl;

    bool dead;
    float lifetime;

}Particle;

Particle sys[MAX];


///////////////////////////////////////////////

double myRandom()
//Return random double within range [0,1]
{
    return (rand()/(double)RAND_MAX);
}

///////////////////////////////////////////////

void initialiseParticles(int i){
    sys[i].dead = false;
    sys[i].lifetime = 1.0;

    sys[i].xposition = (float) (myRandom() * 10);
    sys[i].yposition = 10.0;
    sys[i].zposition = (float) (myRandom() * 10);

    sys[i].re = 0.5;
    sys[i].gr = 0.5;
    sys[i].bl = 1.0;

    sys[i].velocity = velocity;
    sys[i].g = -0.9;

}

void update() {
    //Draw snow particles
    for(int index = 1; index<MAX; index++) {
        glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        glTranslatef(sys[index].xposition, sys[index].yposition, sys[index].zposition);
        glutSolidSphere(0.2, 16, 16);
        glPopMatrix();

        //Now update their positions
    }
}

void display()
{
    glLoadIdentity();
    gluLookAt(0.0, 100.0, 1000.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);
    // If enabled, draw coordinate axis
    if(axisEnabled) glCallList(axisList);

    glutSwapBuffers();
}

///////////////////////////////////////////////

void keyboard(unsigned char key, int x, int y)
{
    if(key == 27) exit(0);
    glutPostRedisplay();
}

///////////////////////////////////////////////

void reshape(int width, int height)
{
    glClearColor(0.9, 0.9, 0.9, 1.0);
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 10000.0);
    glMatrixMode(GL_MODELVIEW);
}

///////////////////////////////////////////////

void makeAxes() {
// Create a display list for drawing coord axis
    axisList = glGenLists(1);
    glNewList(axisList, GL_COMPILE);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);       // X axis - red
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(AXIS_SIZE, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);       // Y axis - green
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, AXIS_SIZE, 0.0);
    glColor3f(0.0, 0.0, 1.0);       // Z axis - blue
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, AXIS_SIZE);
    glEnd();
    glEndList();
}

///////////////////////////////////////////////
void initGraphics(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutCreateWindow("COMP37111 Particles");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    makeAxes();
}

/////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    double f;
    srand(time(NULL));
    initGraphics(argc, argv);
    glEnable(GL_POINT_SMOOTH);
    glutMainLoop();
}
