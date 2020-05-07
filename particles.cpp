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

//Snowfall Simulation
//Author : Connor Brookes
// This programme simulates basic snowfall using a particle system, along with the simple buildup of snow on the
//grass below.
//Some techniques on the snowfall accumulation on the ground were inspired by a project found here:
// https://gist.github.com/Thaenor/4d9531cc9a7d1c34b998
/////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#ifdef MACOS
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include "frames.h"
#include "printvalues.h"


#define PARTICLE_NO 1000
#define RUN_SPEED 0.3
#define TURN_ANGLE 4.0
#define DEG_TO_RAD 0.01745329
// Display list for coordinate axis
GLuint axisList;

int AXIS_SIZE= 200;

int axisEnabled= 1;

GLdouble lat,     lon;              /* View angles (degrees)    */
GLdouble mlat,    mlon;             /* Mouse look offset angles */
GLdouble  eyex,    eyey,    eyez;    /* Eye point                */
GLdouble centerx, centery, centerz; /* Look point               */
GLdouble  upx,     upy,     upz;     /* View up vector           */
GLint width= 700, height= 500;      /* size of window           */
GLfloat windx, windz; /* wind vector */
GLfloat radius;
GLfloat alpha = 1.0;
GLint paused = 0;
int crouchCount = 0;




///////////////////////////////////////////////

typedef struct Particle{
    float xpos;
    float ypos;
    float zpos;
    float vel;
    float gravity;

    float red;
    float green;
    float blue;

    bool dead;
    float lifetime;
    float decay;

}Particle;

Particle particles[PARTICLE_NO];
float particleXMotion[PARTICLE_NO]; //Each particle has its own x and y variance in motion.
float particleZMotion[PARTICLE_NO];
float velocity = 0.0;
float gravity = -0.00025;

//floor colors
float r = 0.0;
float g = 0.5;
float b = 0.0;
float ground_points[31][31][3];
float ground_colors[31][31][4];
float accum = -10.0;

///////////////////////////////////////////////
void calculate_lookpoint(void) { /* Given an eyepoint and latitude and longitude angles, will
     compute a look point one unit away */

    double dir_x;
    double dir_y;
    double dir_z;

    dir_x = cos((lat + mlat)*DEG_TO_RAD)*sin((lon+mlon)*DEG_TO_RAD);
    dir_y = sin((lat+mlat)*DEG_TO_RAD);
    dir_z = cos((lat+mlat)*DEG_TO_RAD)*cos((lon+mlon)*DEG_TO_RAD);

    centerx = eyex + dir_x;
    centery = eyey + dir_y;
    centerz = eyez + dir_z;

} // calculate_lookpoint()

///////////////////////////////////////////////

double myRandom()
//Return random double within range [0,1]
{
    return (rand()/(double)RAND_MAX);
}

///////////////////////////////////////////////

void initialiseParticle(int i){
    particles[i].dead = false; //Particle begins alive.
    particles[i].lifetime = 1.0;
    particles[i].decay = (float)myRandom() / 10;
    //Particles are emitted from a square size 30 by 30, with an emitting point at each integer point in the square.
    particles[i].xpos = (float) (rand() % 31) - 15; //set location coordinates
    particles[i].ypos = 10;
    particles[i].zpos = (float) (rand() % 31) - 15;

    particles[i].red = 0.5;
    particles[i].green = 0.5; //Set colour of particle.
    particles[i].blue = 1.0;

    particles[i].vel = velocity;
    particles[i].gravity = gravity; //approx force of gravity

}

//////////////////////////////////////////////

void updateParticle(){
    for(int i = 0; i < PARTICLE_NO; i++) {
        if (!particles[i].dead) {
            float x = particles[i].xpos;
            float y = particles[i].ypos;
            float z = particles[i].zpos;

            //Draw Particle.
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(1.0, 1.0, 1.0, alpha);
            glPushMatrix();
            glTranslatef(x, y, z);
            glutSolidSphere(radius, 16, 16);
            glPopMatrix();

            //Update movement
            particles[i].ypos += particles[i].vel;
            particles[i].xpos += particleXMotion[i];
            particles[i].zpos += particleZMotion[i];
            particles[i].gravity = gravity;
            particles[i].vel += particles[i].gravity;

            //Decay
            particles[i].lifetime -= particles[i].decay;

            if (particles[i].ypos <= -10) {
                int zi = particles[i].zpos + 25;
                int xi = particles[i].xpos + 25;
                if(zi < 31 && xi< 31) {
                    ground_colors[zi][xi][0] = 1.0;
                    ground_colors[zi][xi][1] = 1.0;
                    ground_colors[zi][xi][2] = 1.0;
                    ground_colors[zi][xi][3] += 1.0;
                    if (ground_colors[zi][xi][3] > 1.0) {
                        ground_points[xi][zi][1] += 0.01;
                    }
                }
                particles[i].lifetime = -1.0;
            }

            if (particles[i].lifetime < 0.0) {
                initialiseParticle(i);
            }
        }
    }


}

//////////////////////////////////////////////
void drawScene(){
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    // along z - y const
    for (int i = -15; i+1 < 16; i++) {
        // along x - y const
        for (int j = -15; j+1 < 16; j++) {
            glColor3fv(ground_colors[i+15][j+15]);
            glVertex3f(ground_points[j+15][i+15][0],
                       ground_points[j+15][i+15][1],
                       ground_points[j+15][i+15][2]);
            glColor3fv(ground_colors[i+15][j+1+15]);
            glVertex3f(ground_points[j+1+15][i+15][0],
                       ground_points[j+1+15][i+15][1],
                       ground_points[j+1+15][i+15][2]);
            glColor3fv(ground_colors[i+1+15][j+1+15]);
            glVertex3f(ground_points[j+1+15][i+1+15][0],
                       ground_points[j+1+15][i+1+15][1],
                       ground_points[j+1+15][i+1+15][2]);
            glColor3fv(ground_colors[i+1+15][j+1 +15]);
            glVertex3f(ground_points[j+15][i+1+15][0],
                       ground_points[j+15][i+1+15][1],
                       ground_points[j+15][i+1+15][2]);
        }

    }
    glEnd();
}
//////////////////////////////////////////////

void display()
{
    if(paused == 0) {
        frameStart();
        glLoadIdentity();
        calculate_lookpoint();
        gluLookAt(eyex, eyey, eyez,
                  centerx, centery, centerz,
                  upx, upy, upz);
        // Clear the screen

        glClearColor(0.302, 0.600, 0.8, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT);
        // If enabled, draw coordinate axis
        if (axisEnabled) glCallList(axisList);
        drawScene();
        updateParticle();

        frameEnd(GLUT_BITMAP_HELVETICA_10, 1.0, 1.0, 1.0, 0.05, 0.95);
        printValue(GLUT_BITMAP_HELVETICA_10, gravity, 0.7, 0.95);


        glutSwapBuffers();
    }
}

///////////////////////////////////////////////

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 27:  /* Escape key */
            exit(0);

            //Comma
        case 44:
            eyex = eyex + RUN_SPEED;
            break;

            //Full Stop
        case 46:
            eyex = eyex - RUN_SPEED;
            break;

        case 'g':
            gravity -= 0.0001;
            break;

        case 'h':
            if(gravity + 0.0001 < 0) {
                gravity += 0.0001;
            }
            break;

        case '=':
            radius += 0.01;
            break;

        case '-':
            radius -= 0.01;
            break;

        case 'o':
            eyey += 1.0;
            break;

        case 'l':
            eyey -= 1.0;
            break;

        case 'a':
            if(alpha < 1.0)
                alpha += 0.1;
            break;

        case 's':
            if(alpha > 0.0)
                alpha -=0.1;
            break;

        case 'p':
            if(paused == 0)
                paused=1;
            else
                paused=0;

    }

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

void idle(){
    glutPostRedisplay();
}

///////////////////////////////////////////////

void initialise() {
    // Ground Vertices
    // Ground Colors
    for (int z = 0; z < 31; z++) {
        for (int x = 0; x < 31; x++) {
            ground_points[x][z][0] = x - 15.0;
            ground_points[x][z][1] = accum;
            ground_points[x][z][2] = z - 15.0;

            ground_colors[z][x][0] = r; // red value
            ground_colors[z][x][1] = g; // green value
            ground_colors[z][x][2] = b; // blue value
            ground_colors[z][x][3] = 0.0; // acummulation factor
        }
    }

    //Initialise particles
    for(int i =0; i<PARTICLE_NO; i++) {
        initialiseParticle(i);

        if((int)myRandom()% 2 ==0)
            particleXMotion[i] = - myRandom() / 20;
        else
            particleXMotion[i] = myRandom() / 50 ;

        if((int)myRandom() % 2 == 0){
            particleZMotion[i] = -myRandom() / 50;
        }
        else
            particleZMotion[i] = myRandom() / 50;
    }

    eyex = 13.0;
    eyey =-8.0; //Camera is at ground level
    eyez = 13.0;
    centerx = 5.0;
    centery = -8.0;
    centerz= 0.0;

    upx = 0.0;
    upy = 1.0;
    upz = 0.0;

    lat = 0.0;
    lon = 255;

    mlat = 0.0;
    mlon = 0.0;
    radius = 0.02;

}
//////////////////////////////////////////////
void cursor_keys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            lon = lon + TURN_ANGLE;
            break;

        case GLUT_KEY_RIGHT:
            lon = lon - TURN_ANGLE;
            break;

        case GLUT_KEY_PAGE_UP:
            if(lat + mlat + TURN_ANGLE < 90)
                lat = lat + TURN_ANGLE;
            break;

        case GLUT_KEY_PAGE_DOWN:
            if(lat + mlat - TURN_ANGLE > -90)
                lat = lat - TURN_ANGLE;
            break;

        case GLUT_KEY_HOME:
            lat = 0;
            break;

        case GLUT_KEY_UP:
            eyex = eyex + RUN_SPEED*sin(lon*DEG_TO_RAD);
            eyez = eyez + RUN_SPEED*cos(lon*DEG_TO_RAD);
            eyey = eyey + RUN_SPEED*sin(lat*DEG_TO_RAD);

            break;

        case GLUT_KEY_DOWN:
            eyex = eyex - RUN_SPEED*sin(lon*DEG_TO_RAD);
            eyez = eyez - RUN_SPEED*cos(lon*DEG_TO_RAD);
            eyey = eyey - RUN_SPEED*sin(lat*DEG_TO_RAD);
            break;
    }
} // cursor_keys()

//////////////////////////////////////////////

void mouse_motion(int x, int y) {

    mlon = ((width/2) - x)*100/width;
    mlat = ((height/2) - y)*100/height;

} // mouse_motion()

//////////////////////////////////////////////

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
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("COMP37111 Particles");
    initialise();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(cursor_keys);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutPassiveMotionFunc(mouse_motion);
    //makeAxes();
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
