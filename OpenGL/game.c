#include <GL/glut.h>
#include "../header.h"
#include "../local.h"
#include <GL/freeglut.h> 
#include <sys/time.h>

extern  char L_sum1[10];
extern  char L_sum2[10];
extern  char value1_T1[10];
extern  char value2_T1[10];
extern char value1_T2[10];
extern char value2_T2[10];

extern  char result[10];
extern char number_of_Rounds[10];



static double lasttime;
double getftime(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec*1e-6;
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
     
     
     double finishtime ,delta_t;
    // Set camera position and orientation
    gluLookAt(0, 30, 0, 0, 0, 0, 0, 0, -1);
     // Draw the playing field
    glColor3f(0.2, 0.8, 0.2);
    glBegin(GL_QUADS);
    glVertex3f(-20, 0, -20);
    glVertex3f(-20, 0, 20);
    glVertex3f(20, 0, 20);
    glVertex3f(20, 0, -20);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(-10, 10);
    // Render the number 42 using GLUT_BITMAP_TIMES_ROMAN_24 font
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)L_sum1);
    //glutBitmapCha(GLUT_BITMAP_TIMES_ROMAN_24, '2');

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(-5, 5);
    // Render the number 42 using GLUT_BITMAP_TIMES_ROMAN_24 font
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,L_sum2);

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(5,- 5);
    // Render the number 42 using GLUT_BITMAP_TIMES_ROMAN_24 font
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,value1_T1);


    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(5,- 5);
    // Render the number 42 using GLUT_BITMAP_TIMES_ROMAN_24 font
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,value2_T1 );


    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(5,- 5);
    // Render the number 42 using GLUT_BITMAP_TIMES_ROMAN_24 font
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,value1_T2 );


    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(5,- 5);
    // Render the number 42 using GLUT_BITMAP_TIMES_ROMAN_24 font
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,value2_T2);
 

     glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(5,- 5);
    // Render the number 42 using GLUT_BITMAP_TIMES_ROMAN_24 font
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,result );

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(5,- 5);
    // Render the number 42 using GLUT_BITMAP_TIMES_ROMAN_24 font
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,number_of_Rounds );


    glColor3f(0.5, 0.5, 0.5); // gray color
    glPushMatrix();
    glScalef(2, 2, 2); // make the parent bigger
    glTranslatef(0, 0, -5);
    glutSolidSphere(2, 20, 20);
    glPopMatrix();


// Draw the judge
    glColor3f(1, 1, 0); // yellow color
    glPushMatrix();
    glTranslatef(0, 2,13); // put the judge above the field
    glScalef(2,2,2);
    glutSolidCube(1);
    glPopMatrix();

    // Draw the two teams
    glColor3f(1, 0, 0); // red team
    glPushMatrix();
    glTranslatef(18, 0, -1); // move the red team to the right edge
    glutSolidSphere(1, 20, 20); // player 1
    glTranslatef(0, 0, 7);
    glutSolidSphere(1, 20, 20); // player 2
    glPopMatrix();

    glColor3f(0, 0, 1); // blue team
    glPushMatrix();
    glTranslatef(-18, 0, -1); // move the blue team to the left edge
    glutSolidSphere(1, 20, 20); // player 1
    glTranslatef(0, 0, 7);
    glutSolidSphere(1, 20, 20); // player 2
    glPopMatrix();

    glutSwapBuffers();
    finishtime = getftime();
    delta_t = finishtime = lasttime;
    lasttime = finishtime ;
}
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)width/height, 1, 100);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Playground");

    glEnable(GL_DEPTH_TEST);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(glutPostRedisplay);
    lasttime = getftime();   
    glutMainLoop();
    
}
