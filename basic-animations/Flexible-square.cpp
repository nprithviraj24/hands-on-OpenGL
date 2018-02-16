#include <GL/glew.h>
#include <GL/freeglut.h> 
#include<stdlib.h>
#include<iostream>


using namespace std;


float a = 0.0;
static int isAnimate = 0; // Animated?
static int animationPeriod = 500; // Time interval between frames.

									// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	//glTranslatef(0.0, -10.0, 0.0);

	//glColor3f(0.0, 0.0, 0.0);
	
	// Draw a polygon with specified vertices.
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2.0);

	//The unchanged line.	
	glBegin(GL_LINES);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(25.0, 25.0, 0.0);
	glVertex3f(25.0, 40.0, 0.0);
	glVertex3f(24.0, 40.0, 0.0);
	glVertex3f(24.0, 25.0, 0.0);
	glEnd();



	glPushMatrix();

	glTranslatef(25.0, 40.0, 0.0);
	glRotatef(a, 0.0, 0.0, 1.0);
	glTranslatef(-25.0, -40.0, 0.0);

	// second line
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(25.0, 40.0, 0.0);
	glVertex3f(40.0, 40.0, 0.0);
	glVertex3f(40.0, 41.0, 0.0);
	glVertex3f(25.0, 41.0, 0.0);
	glEnd();

	glPushMatrix();

	glTranslatef(40.0, 40.0, 0.0);
	glRotatef(a, 0.0, 0.0, 1.0);
	glTranslatef(-40.0, -40.0, 0.0);

	//The second to top line after animation
	glBegin(GL_LINES);
	glColor3f(0.5, 0.25, 0.75);
	glVertex3f(40.0, 40.0, 0.0);
	glVertex3f(40.0, 25.0, 0.0);

	glVertex3f(41.0, 25.0, 0.0);
	glVertex3f(41.0, 40.0, 0.0);

	glEnd();

	glPushMatrix();
	glTranslatef(40.0, 25.0, 0.0);
	glRotatef(a, 0.0, 0.0, 1.0);
	glTranslatef(-40.0, -25.0, 0.0);
	
	
	//The top line after animation
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 0.5, 1.0);
	glVertex3f(25.0, 25.0, 0.0);
	glVertex3f(25.0, 24.0, 0.0);
	glVertex3f(40.0, 24.0, 0.0);
	glVertex3f(40.0, 25.0, 0.0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glFlush();
}

//animation
void animate(int value)
{
	if (isAnimate)
	{
		if (a< 90.0)
			a++;
		
		glutPostRedisplay();
		glutTimerFunc(animationPeriod, animate, 1);

	}
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 100.0, 0.0, 100.0, -1.0, 1.0);
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
	case ' ':
		if (isAnimate) isAnimate = 0;
		else
		{
			isAnimate = 1;
			animate(1);
		}
		break;
	default:
		break;
	}
}

// Main routine.
int main(int argc, char **argv)
{

	cout << "Press Spacebar to see the animation.";
	glutInit(&argc, argv);

	glutInitContextVersion(2, 1);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Square-to-Line.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}