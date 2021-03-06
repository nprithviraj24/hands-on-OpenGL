#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h> 

#define PI 3.14159265
#define N 30.0 // Number of vertices on the boundary of the disc.

// Globals.
static int isWire = 0; // Is wireframe?
static long font = (long)GLUT_BITMAP_8_BY_13; // Font selection.

											  // Routine to draw a bitmap character string.
void writeBitmapString(void *font, char *string)
{
	char *c;

	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

// Function to draw a disc with center at (X, Y, Z), radius R, parallel to the xy-plane.
void drawDisc(float R, float X, float Y, float Z)
{
	float t;
	int i;

	/*glBegin(GL_TRIANGLE_FAN);
	glVertex3f(X, Y, Z);
	for (i = 0; i <= N; ++i)
	{
	t = 2 * PI * i / N;
	glVertex3f(X + cos(t) * R, Y + sin(t) * R, Z);
	}*/
	glEnd();
}

// Drawing routine.
void drawScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT);

	

	if (isWire) glPolygonMode(GL_FRONT, GL_LINE); else glPolygonMode(GL_FRONT, GL_FILL);
	// Draw a polygon with specified vertices..
	//glPolygonMode(GL_FRONT, GL_FILL);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_STRIP);


	glVertex3f(10.0, 10.0, 0.0);
	glVertex3f(20.0, 10.0, 0.0);
	glVertex3f(10.0, 100.0, 0.0);
	glVertex3f(20.0, 80.0, 0.0);
	glVertex3f(20.0, 100.0, 0.0);
	glVertex3f(50.0, 50.0, 0.0);
	
	//glEnd();

	//if (isWire) glPolygonMode(GL_FRONT, GL_LINE); else glPolygonMode(GL_FRONT, GL_FILL);
	glColor3f(0.0, 0.0, 0.0);
	//glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(50.0, 50.0, 0.0);
	glVertex3f(50.0, 50.0, 0.0);
	glVertex3f(80.0, 100.0, 0.0);
	glVertex3f(80.0, 80.0, 0.0);	
	glVertex3f(90.0, 100.0, 0.0);
	glVertex3f(90.0, 100.0, 0.0);
	
	//glEnd();

	//if (isWire) glPolygonMode(GL_FRONT, GL_LINE); else glPolygonMode(GL_FRONT, GL_FILL);
	glColor3f(0.0, 0.0, 0.0);
	//glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(90.0, 100.0, 0.0);
	glVertex3f(80.0, 80.0, 0.0);
	glVertex3f(90.0, 10.0, 0.0);
	glVertex3f(80.0, 10.0, 0.0);
	//glEnd();
	//glColor3f(0.0, 1.0, 0.0);

	// Draw a polygon with specified vertices.
	//(GL_POLYGON);
	//glVertex3f(30.0, 40.0, 0.0);
	//glVertex3f(40.0, 30.0, 0.0);
	//glVertex3f(40.0, 40.0, 0.0);
	//glVertex3f(30.0, 40.0, 0.0);
	glEnd();

	glFlush();

	// NOTE: I undertand i took redundant vertices. 
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
	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ' ':
		if (isWire == 0) isWire = 1;
		else isWire = 0;
		glutPostRedisplay();
		break;
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
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press the space bar to toggle between wirefrime and filled for the lower annulus." << std::endl;
}

// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Letter-M.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
