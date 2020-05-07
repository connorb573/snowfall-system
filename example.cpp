//	May Ang
//	mang@ucsc.edu
//	CS 161 - Animation & Visualization
//	Final Project - Rain/Hail/Snow Simulation

//source: https://classes.soe.ucsc.edu/cmps161/Winter09/projects/mang/finalproject.html
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GLUT/glut.h>


#define PARTICLE_NO 1000
#define WCX		640
#define WCY		480



float slowdown = 2.0;
float velocity = 0.0;
float zoom = -40.0;
float pan = 0.0;
float tilt = 0.0;
float hailsize = 0.1;

int i;
int fall;

//floor colors
float r = 0.0;
float g = 0.5;
float b = 0.0;
float ground_points[31][31][3];
float ground_colors[31][31][4];
float accum = -10.0;

float particleXMotion[PARTICLE_NO];
float particleZMotion[PARTICLE_NO];

typedef struct {
    // Life
    bool alive;	// is the particle alive?
    float life;	// particle lifespan
    float fade; // decay
    // color
    float red;
    float green;
    float blue;
    // Position/direction
    float xpos;
    float ypos;
    float zpos;
    // Velocity/Direction, only goes down in y dir
    float vel;
    // Gravity
    float gravity;
}particles;

// Paticle System
particles par_sys[PARTICLE_NO];

void normal_keys(unsigned char key, int x, int y) {
    if (key == ',') { // really '<' slow down
        if (slowdown > 4.0) slowdown += 0.01;
    }
    if (key == '.') { // really '>' speed up
        if (slowdown > 1.0) slowdown -= 0.01;
    }
    if (key == 'q') { // QUIT
        exit(0);
    }
}

void special_keys(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        zoom += 1.0;
    }
    if (key == GLUT_KEY_DOWN) {
        zoom -= 1.0;
    }
    if (key == GLUT_KEY_RIGHT) {
        pan += 1.0;
    }
    if (key == GLUT_KEY_LEFT) {
        pan -= 1.0;
    }
    if (key == GLUT_KEY_PAGE_UP) {
        tilt -= 1.0;
    }
    if (key == GLUT_KEY_PAGE_DOWN) {
        tilt += 1.0;
    }
}


// Initialize/Reset Particles - give them their attributes
void initParticles(int i) {
    par_sys[i].alive = true;
    par_sys[i].life = 1.0;
    par_sys[i].fade = float(rand()%100)/1000.0f+0.003f;

    par_sys[i].xpos = (float) (rand() % 21) - 10;
    par_sys[i].ypos = 10.0;
    par_sys[i].zpos = (float) (rand() % 21) - 10;

    par_sys[i].red = 0.5;
    par_sys[i].green = 0.5;
    par_sys[i].blue = 1.0;

    par_sys[i].vel = velocity;
    par_sys[i].gravity = -0.8;//-0.8;

}

double myRandom()
//Return random double within range [0,1]
{
    return (rand()/(double)RAND_MAX);
}

void init( ) {
    int x, z;

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);

    // Ground Verticies
    // Ground Colors
    for (z = 0; z < 31; z++) {
        for (x = 0; x < 31; x++) {
            ground_points[x][z][0] = x - 15.0;
            ground_points[x][z][1] = accum;
            ground_points[x][z][2] = z - 15.0;

            ground_colors[z][x][0] = r; // red value
            ground_colors[z][x][1] = g; // green value
            ground_colors[z][x][2] = b; // blue value
            ground_colors[z][x][3] = 0.0; // acummulation factor
        }
    }

    // Initialize particles
    for (i = 0; i < PARTICLE_NO; i++) {
        initParticles(i);

        if((int)myRandom()% 2 ==0)
            particleXMotion[i] = - myRandom() / 100;
        else
            particleXMotion[i] = myRandom() / 100;

        if((int)myRandom() % 2 == 0){
            particleZMotion[i] = -myRandom() / 100;
        }
        else
            particleZMotion[i] = myRandom() / 100;
    }
}


// For Snow
void drawSnow() {
    float x, y, z;
    for (i = 0; i < PARTICLE_NO; i=i+2) {
        if (par_sys[i].alive == true) {
            x = par_sys[i].xpos;
            y = par_sys[i].ypos;
            z = par_sys[i].zpos + zoom;

            // Draw particles
            glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            glTranslatef(x, y, z);
            glutSolidSphere(0.05, 16, 16);
            glPopMatrix();

            // Update values
            //Move
            par_sys[i].ypos += par_sys[i].vel / (slowdown*1000);
            par_sys[i].vel += par_sys[i].gravity;
            par_sys[i].xpos += particleXMotion[i];
            par_sys[i].zpos += particleZMotion[i];
            // Decay
            par_sys[i].life -= par_sys[i].fade;

            if (par_sys[i].ypos <= -10) {
                int zi = z - zoom + 10;
                int xi = x + 10;
                ground_colors[zi][xi][0] = 1.0;
                ground_colors[zi][xi][1] = 1.0;
                ground_colors[zi][xi][2] = 1.0;
                ground_colors[zi][xi][3] += 1.0;
                if (ground_colors[zi][xi][3] > 1.0) {
                    ground_points[xi][zi][1] += 0.1;
                }
                par_sys[i].life = -1.0;
            }

            //Revive
            if (par_sys[i].life < 0.0) {
                initParticles(i);
            }
        }
    }
}

// Draw Particles
void display( ) {
    int i, j;
    float x, y, z;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();


    glRotatef(pan, 0.0, 1.0, 0.0);
    glRotatef(tilt, 1.0, 0.0, 0.0);

    // GROUND?!
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    // along z - y const
    for (i = -15; i+1 < 16; i++) {
        // along x - y const
        for (j = -15; j+1 < 16; j++) {
            glColor3fv(ground_colors[i+15][j+15]);
            glVertex3f(ground_points[j+15][i+15][0],
                       ground_points[j+15][i+15][1],
                       ground_points[j+15][i+15][2] + zoom);
            glColor3fv(ground_colors[i+15][j+1+15]);
            glVertex3f(ground_points[j+1+15][i+15][0],
                       ground_points[j+1+15][i+15][1],
                       ground_points[j+1+15][i+15][2] + zoom);
            glColor3fv(ground_colors[i+1+15][j+1+15]);
            glVertex3f(ground_points[j+1+15][i+1+15][0],
                       ground_points[j+1+15][i+1+15][1],
                       ground_points[j+1+15][i+1+15][2] + zoom);
            glColor3fv(ground_colors[i+1+15][j+15]);
            glVertex3f(ground_points[j+15][i+1+15][0],
                       ground_points[j+15][i+1+15][1],
                       ground_points[j+15][i+1+15][2] + zoom);
        }

    }
    glEnd();

        drawSnow();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45, (float) w / (float) h, .1, 200);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void idle ( ) {
    glutPostRedisplay();
}

int main (int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WCX, WCY);
    glutCreateWindow("CMPS 161 - Final Project");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(normal_keys);
    glutSpecialFunc(special_keys);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}

