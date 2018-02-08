
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h> 

#define PI 3.14159265

// Globals.
bool isWire = false;

// Initialization routine.
void setup(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
}

float r = 15.0f;
float x = 50.0f;
float y = 50.0f;
float z = 0.0f;

float *vertices;
float *colors;
int *startIndices;
int *countIndices;
int noOfDiscs = 5;
float colour[3] = { 0, 0, 0 };

int count = 42;

//Setting colour of each vertex
void settingColour(int i) {

	switch (i) {
	case 0:
		colour[0] = 0;
		colour[1] = 0;
		colour[2] = 1;
		r = 25;
		break;
	case 1:
		colour[0] = 1;
		colour[1] = 0;
		colour[2] = 0;
		r = 20;
		break;
	case 2:
		colour[0] = 0;
		colour[1] = 1;
		colour[2] = 1;
		r = 15;
		break;
	case 3:
		colour[0] = 1;
		colour[1] = 0;
		colour[2] = 1;
		r = 10;
		break;
	case 4:
		colour[0] = 1;
		colour[1] = 1;
		colour[2] = 0;
		r = 5;
		break;
	default:
		colour[0] = 1;
		colour[1] = 1;
		colour[2] = 0;
		break;
	}

}
void fillVertexArray() {
	int k = 0;
	float t;
	int i, j;

	//defining vertices and colors
	vertices = new float[noOfDiscs * 3 * (count + 3)];
	colors = new float[noOfDiscs * 3 * (count + 3)];
	
	//defining indices
	startIndices = new int[noOfDiscs];
	countIndices = new int[noOfDiscs];
	t = 0;


	for (i = 0; i < noOfDiscs; i++) {
		if (i == 0) {
			startIndices[i] = 0;
		}
		else {
			startIndices[i] = startIndices[i - 1] + countIndices[i - 1] + 1;
		}

		countIndices[i] = count + 2;

		settingColour(i);
		
		for (j = 0; j < count + 3; j++) {
			vertices[k++] = x + (r)* cos(t);
			vertices[k++] = y + (r)* sin(t);
			vertices[k++] = z + i;
			colors[k - 3] = colour[0];
			colors[k - 2] = colour[1];
			colors[k - 1] = colour[2];
			t += 2 * PI / (float)count;
		}
	}
	return;
}

// Drawing routine.
void drawScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	fillVertexArray();

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);
	if (isWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glMultiDrawArrays(GL_TRIANGLE_FAN , (const int*)startIndices, (const int*)countIndices, noOfDiscs);

	glFlush();
}

// OpenGL window reshape routine.

void resize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 100.0, 0.0, 100.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y) {
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case ' ':
		isWire = !isWire;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void) {
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press spacebar to toggle between solid and line." << std::endl;
}

// Main routine.
int main(int argc, char **argv) {
	printInteraction();
	glutInit(&argc, argv);

	/* glutInitContextVersion(4, 3); */
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("bullseye.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}