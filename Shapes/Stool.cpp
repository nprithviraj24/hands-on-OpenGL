
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include<stdlib.h>
#include <GL/freeglut.h> 

#define PI 3.14159265
using namespace std;

// Globals.
float t = 0;
static float R = 5.0; // Radius of hemisphere.
static int p = 15; // Number of longitudinal slices.
static int q = 2; // Number of latitudinal slices.
static float Xangle = 20.0, Yangle = 0.0, Zangle = 180.0; // Angles to rotate hemisphere.
static float *vertices = NULL; // Vertex array of sample points on the hemisphere.
static unsigned int **indices = NULL; // Array of index arrays.
static int *countIndices = NULL; // Array of countIndices.


								 // Begin globals.
static int isWire = 0; // Is wireframe?

					   // Vertex co-ordinate vectors for the annulus.
					   // Fill the vertex array with co-ordinates of the sample points.
void fillVertexArray(void)
{
	int i, j, k;

	k = 0;
	for (j = 0; j <= q; j++)
		for (i = 0; i <= p; i++)
		{	
			//vertices[k++] = R * cos((float)j ) + R * sin((float)j);
			//R * cos((float)j / q * PI / 15.0) * cos(2.0 * (float)i / p * PI);
			//vertices[k++] = R * sin((float)j);

			vertices[k++] = R * cos((float)j / q * PI / 20.0) * cos(2.0 * (float)i / p * PI);
			//cout << vertices[k]<<" ";
			vertices[k++] = R * sin((float)j / q * PI / 20.0);
			//cout << vertices[k]<<" ";
			vertices[k++] = R * cos((float)j / q * PI / 2.0) * sin(2.0 * (float)i / p * PI);
			//cout << vertices[k]<<" ";
		}
}
void drawLegs() {
	int i, j, k;

	k = 0;
	for (j = 0; j <= q; j++)
		for (i = 0; i <= p; i++)
		{
			vertices[k++] = 2 * cos(60) * cos(2.0 * (float)i / p * PI);
			vertices[k++] = 2 * sin(60);
			vertices[k++] = -2 * cos(60) * sin(2.0 * (float)i / p * PI);
		}

}
// Fill the array of index arrays.
void fillIndices(void)
{
	int i, j;
	for (j = 0; j < q; j++)
		// Note: indexes for the jth index array (given in the loop below) correspond exactly
		// to the points on the jth triangle strip in the drawing loop of hemisphere.cpp.
	{
		for (i = 0; i <= p; i++)
		{
			indices[j][2 * i] = (j + 1)*(p + 1) + i;
			indices[j][2 * i + 1] = j*(p + 1) + i;
		}
	}

}

// Fill the array countIndices.
void fillCountIndices(void)
{
	int j;
	for (j = 0; j < q; j++) countIndices[j] = 2 * (p + 1);
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glEnableClientState(GL_VERTEX_ARRAY); // Enable vertex array.
}


// Drawing routine.
void drawScene(void)
{
	int j;

	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	// Create global arrays.
	vertices = new float[3 * (p + 1)*(q + 1)];
	indices = new unsigned int*[q];
	for (j = 0; j < q; j++) indices[j] = new unsigned int[2 * (p + 1)];
	countIndices = new int[q];

	// Initialize global arrays.
	fillVertexArray();
	fillIndices();
	fillCountIndices();
	//drawLegs();
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	// Command to push the hemisphere, which is drawn centered at the origin, 
	// into the viewing frustum.
	glTranslatef(0.0, 0.0, -10.0);

	// Commands to turn the hemisphere.
	glRotatef(Zangle, 0.0, 0.0, 1.0);
	glRotatef(Yangle, 0.0, 1.0, 0.0);
	glRotatef(Xangle, 180.0, 0.0, 0.0);

	// Hemisphere properties.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (isWire) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(0.0, 1.0, .0);

	// Multidraw command equivalent to the drawing loop for(j = 0; j < q; j++){...} in hemisphere.cpp.
	glMultiDrawElements(GL_TRIANGLE_STRIP, countIndices, GL_UNSIGNED_INT, (const void **)indices, q);
	float length = 5, numSteps = 20, radius = 0.25;
	float hl = length * 0.5;
	float a = 0.0;
	float step = 2 * PI / (float)numSteps;

	int numVertices = 20,i;
	//glBegin(GL_LINE_STRIP);

	//glBegin(GL_TRIANGLE_FAN);
	//glRotatef(180.0, 0.0, 1.0, 1.0);
	//for (i = 0; i < numVertices; ++i)
	//{
		//glColor3f((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
		//glVertex3f(0 + R * cos(t), 0 + R * sin(t), 0.0);
		//t += 2 * PI / numVertices;
	//}
	//glEnd();


	//glRotatef(Zangle, 0.0, 0.0, 1.0);
	//glRotatef(Yangle, 0.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);

	glRotatef(120, 1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < numSteps+1; ++i)
	{
		float x = cos(a) * radius;
		float y = sin(a) * radius;
		glVertex3f(x - 4, y+1 , -hl - 3);
		glVertex3f(x - 4, y+1 , hl - 3);

		a += step;
	}

	glEnd();
	glColor3f(1.0, 0.0, 1.0);

	glRotatef(0, 0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < numSteps+1; ++i)
	{
		float x = cos(a) * radius;
		float y = sin(a) * radius;
		glVertex3f(x + 4, y +1, -hl - 3);
		glVertex3f(x + 4, y +1, hl - 3);

		a += step;
	}

	glEnd();
	glColor3f(0.0, 1.0, 1.0);

	glRotatef(0, 0.0, 0.0, 1.0);
	glRotatef(0, 0.0, 1.0, 0.0);
	glRotatef(180, 1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < numSteps+1; ++i)
	{
		float x = cos(a) * radius;
		float y = sin(a) * radius;
		glVertex3f(x, y + 3.5, 5);
		glVertex3f(x, y + 3.5, -2);

		a += step;
	}
	glEnd();
	//float radius, halfLength;
	//int slices;
	//for (int i = 0; i < slices; i++) {
	//float theta = ((float)i)*2.0*M_PI;
	//float nextTheta = ((float)i + 1)*2.0*M_PI;
	//glBegin(GL_TRIANGLE_STRIP);
	/*vertex at middle of end */
	//glVertex3f(0.0, halfLength, 0.0);
	/*vertices at edges of circle*/
	//glVertex3f(radius*cos(theta), halfLength, radius*sin(theta));
	//glVertex3f(radius*cos(nextTheta), halfLength, radius*sin(nextTheta));
	/* the same vertices at the bottom of the cylinder*/
	//glVertex3f(radius*cos(nextTheta), -halfLength, radius*sin(nextTheta));
	//glVertex3f(radius*cos(theta), -halfLength, radius*sin(theta));
	//glVertex3f(0.0, -halfLength, 0.0);
	//glEnd();
	//} 

	/*drawLegs();
	// The vertex and color array pointers point to the data for the legs.
	glVertexPointer(3, GL_FLOAT, 0, vertices1);
	//glColorPointer(3, GL_FLOAT, 0, colors1);
	// Draw first leg.
	glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, stripIndices);
	*/


	glFlush();
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
	case ' ':
		if (isWire == 0) isWire = 1;
		else isWire = 0;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	case 'P':
		p += 1;
		glutPostRedisplay();
		break;
	case 'p':
		if (p > 3) p -= 1;
		glutPostRedisplay();
		break;
	case 'Q':
		q += 1;
		glutPostRedisplay();
		break;
	case 'q':
		if (q > 3) q -= 1;
		glutPostRedisplay();
		break;
	case 'x':
		Xangle += 5.0;
		if (Xangle > 360.0) Xangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'X':
		Xangle -= 5.0;
		if (Xangle < 0.0) Xangle += 360.0;
		glutPostRedisplay();
		break;
	case 'y':
		Yangle += 5.0;
		if (Yangle > 360.0) Yangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'Y':
		Yangle -= 5.0;
		if (Yangle < 0.0) Yangle += 360.0;
		glutPostRedisplay();
		break;
	case 'z':
		Zangle += 5.0;
		if (Zangle > 360.0) Zangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'Z':
		Zangle -= 5.0;
		if (Zangle < 0.0) Zangle += 360.0;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press P/p to increase/decrease the number of longitudinal slices." << std::endl
		<< "Press Q/q to increase/decrease the number of latitudinal slices." << std::endl
		<< "Press x, X, y, Y, z, Z to turn the hemisphere." << std::endl;
}

// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(2, 1);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("stool.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}