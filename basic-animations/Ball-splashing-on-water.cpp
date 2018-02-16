
#include <cmath>
#include <cstdlib>
#include <iostream>
#include<stdlib.h>
#include <fstream>

#include <GL/glew.h>
#include <GL/freeglut.h> 

#define PI 3.14159265

// Globals.
static int isAnimate = 0; // Animated?
static int animationPeriod = 100; // Time interval between frames.
static float t = 0.0; // Time parameter.
static float h = 0.0; // Horizontal component of initial velocity.
static float v = -1.0; // Vertical component of initial velocity.
static float g = 0.2;  // Gravitational accelaration.
static char theStringBuffer[10]; // String buffer.
static long font = (long)GLUT_BITMAP_8_BY_13; // Font selection.
bool collision = FALSE; // initial value
float R_sphere = 1.0; 
float viscosity = 1; //initially 

float bowlX = 20; // this is where ball will collide.
float bowlY = 5.0;
float translateCall[3] = { 0.0,15.0,-25.0 };
											  // Routine to draw a bitmap character string.
void writeBitmapString(void *font, char *string)
{
	char *c;

	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

// Routine to onvert floating point to char string.
void floatToString(char * destStr, int precision, float val)
{
	sprintf(destStr, "%f", val);
	destStr[precision] = '\0';
}

// Write data.
void writeData(void)
{
	glColor3f(0.0, 0.0, 0.0);

	floatToString(theStringBuffer, 4, h);
	glRasterPos3f(-4.5, 4.5, -5.1);
	writeBitmapString((void*)font, "Horizontal component of initial velocity: ");
	writeBitmapString((void*)font, theStringBuffer);

	floatToString(theStringBuffer, 4, v);
	glRasterPos3f(-4.5, 4.2, -5.1);
	writeBitmapString((void*)font, "Vertical component of initial velocity: ");
	writeBitmapString((void*)font, theStringBuffer);

	floatToString(theStringBuffer, 4, g);
	glRasterPos3f(-4.5, 3.9, -5.1);
	writeBitmapString((void*)font, "Gravitation: ");
	writeBitmapString((void*)font, theStringBuffer);
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers including the depth buffer.
	

	glLoadIdentity();

	writeData();
	glBegin(GL_TRIANGLE_FAN);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT, GL_FILL);
	glColor3f(0.439216, 0.858824, 0.576471);
	glVertex3f(-bowlX, -bowlY, -25.0);
	glVertex3f(bowlX, -bowlY, -25.0);
	glVertex3f(bowlX, -(bowlY+19), -25.0);
	glVertex3f(-bowlX, -(bowlY + 19), -25.0);
	glEnd();


	// Place scene in frustum.
	glTranslatef(translateCall[0], translateCall[1], translateCall[2]);

	//if (collision == TRUE) {
		//std::cout << "\t \t translate \n ";
		//glTranslatef(translateCall[0], v*t - (g / 2.0)*t*t, translateCall[2]);
	//}
	// Apply equations of motion to transform sphere.
	glTranslatef(h*t, v*t - (g / 2.0)*t*t, 0.0);

	// Sphere.
	glColor3f(0.0, 0.0, 0.0);
	glutWireSphere(R_sphere, 10, 10);

	glutSwapBuffers();
}

// Timer function.
void animate(int value)
{
	//

	float yC = v*t - (g / 2.0)*t*t;
	if (isAnimate &&  collision == FALSE)
	{
		t += 1.0;
		//std::cout << " \n y coordinate: " << yC << " \t h value: "<<h<<" \t v value: "<<v<<"  t value: "<<t;
		
		if (yC  < -translateCall[1] ) {
			std::cout << "\n Collision at : "<< yC;
			collision = TRUE;
			//t = 0;
			
		}

		glutPostRedisplay();
		glutTimerFunc(animationPeriod, animate, 1);
	}

	if (isAnimate &&  collision == TRUE && yC>-(37.5-R_sphere))
	{
		t += 0.25;
		v = v - 0.1*v;
		
		//std::cout << " \n y coordinate: " << yC << " \t h value: " << h << " \t v value: " << v << "  t value: " << t;
		glutPostRedisplay();
		glutTimerFunc(animationPeriod+250, animate, 1);
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
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
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
	case 'r':
		isAnimate = 0;
		t = 0.0;
		v = -1.0;
		collision = FALSE;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
	if (key == GLUT_KEY_UP) v += 0.05;;
	if (key == GLUT_KEY_DOWN) if (v > 0.1) v -= 0.05;
	if (key == GLUT_KEY_RIGHT) h += 0.05;
	if (key == GLUT_KEY_LEFT) if (h > 0.1) h -= 0.05;
	if (key == GLUT_KEY_PAGE_UP) g += 0.05;
	if (key == GLUT_KEY_PAGE_DOWN) if (g > 0.1) g -= 0.05;

	glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press space to toggle between animation on and off." << std::endl
		<< "Press right/left arrow kes to increase/decrease the initial horizontal velocity." << std::endl
		<< "Press up/down arrow keys to increase/decrease the initial vertical velocity." << std::endl
		<< "Press page up/down keys to increase/decrease gravitational acceleration." << std::endl
		<< "Press r to reset." << std::endl;
}

// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("drowning.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}

