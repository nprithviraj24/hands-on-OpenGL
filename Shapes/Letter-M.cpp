///////////////////////////////////
// square.cpp
//
// OpenGL program to draw a M.
// 
// Sumanta Guha.
///////////////////////////////////

#include <GL/glew.h>
#include <GL/freeglut.h> 

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 0.0, 0.0);

	// Draw a polygon with specified vertices.
	glBegin(GL_TRIANGLE_STRIP);

	//glVertex3f(10.0, 10.0, 0.0);
	//glVertex3f(20.0, 10.0, 0.0);
	//glVertex3f(10.0, 100.0, 0.0);
	//glVertex3f(20.0, 80.0, 0.0);
	//glVertex3f(20.0, 100.0, 0.0);
	//glVertex3f(37.5, 50.0, 0.0);
//	glVertex3f(40.0, 60.0, 0.0);
	//glVertex3f(45.0, 50.0, 0.0);
	//glVertex3f(45.0, 60.0, 0.0);

	glVertex3f(10.0, 10.0, 0.0);
	glVertex3f(20.0, 10.0, 0.0);
	glVertex3f(10.0, 100.0, 0.0);
	glVertex3f(20.0, 80.0, 0.0);
	glVertex3f(20.0, 100.0, 0.0);
	glVertex3f(50.0, 50.0, 0.0);

	glEnd();
	glBegin(GL_TRIANGLE_STRIP);


	glVertex3f(90.0, 10.0, 0.0);
	glVertex3f(80.0, 10.0, 0.0);
	glVertex3f(90.0, 100.0, 0.0);
	glVertex3f(80.0, 80.0, 0.0);
	glVertex3f(80.0, 100.0, 0.0);
	glVertex3f(50.0, 50.0, 0.0);
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

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("square.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}