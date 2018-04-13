
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h> 

// Begin globals. 
// Initial control points.
static float controlPoints1[6][4][3] =
{
	
	{ { 0.0, 1,4.0 },{ -0.25, 1, 4.0 },{ 0.25, 1, 4.0 },{ 0.0, 1, 4.0 } },
	{ { -4.0, 0, 4.0 },{ -0.25, -2, 4.0 },{ 0.25, -2, 4.0 },{ 4.0, 0.0, 4.0 } },
	{ { 0.0, 0, 0.0 },{ 0.0, 0, 0.0 },{ 0.0, 0, 0 },{ 0, 0, 0 } },

	};



static float controlPoints31[6][4][3] =
{
	{ { 3, 3, 3 },{ 3, 3,3 },{ 3, 3, 3 },{ 3, 3, 3 } },
	{ { 4.0, 1, 0 },{ 2.5, 1, 2 },{ 2, 1, 2.5 },{ 0.0, 1, 4.0 } },
	{ { 0.0, 0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0, 0 },{ 0, 0.0, 0 } }

};

static float controlPoints21[6][4][3] =
{
	{ { -2, -2, -2 },{ -2, -2, -2 },{ -2, -2, -2},{ -2, -2, -2} },
	{ { -2.0, 1, 0 },{ -1.25, 1, -1 },{ -1, 1, -1.25},{ 0.0, 1, -2.0} },
	{ { 0.0, 0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0, 0 },{ 0, 0.0, 0 } }
	
};


static float controlPoints22[6][4][3] =
{
	{ { 2, -2, -2 },{ 2, -2, -2 },{ 2, -2, -2 },{ 2, -2, -2 } },
	{ { 2.0, 1, 0 },{ 1.25, 1, -1 },{ 1, 1, -1.25 },{ 0.0, 1, -2.0 } },
	{ { 0.0, 0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0, 0 },{ 0, 0.0, 0 } }

};

static float controlPoints23[6][4][3] =
{
	{ { 2, -2, 2 },{ 2, -2, 2 },{ 2, -2, 2 },{ 2, -2, 2 } },
	{ { 2.0, 1, 0 },{ 1.25, 1, 1 },{ 1, 1, 1.25 },{ 0.0, 1, 2.0 } },
	{ { 0.0, 0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0, 0 },{ 0, 0.0, 0 } }

};

static float controlPoints24[6][4][3] =
{
	{ { -2, -2, 2 },{ -2, -2, 2 },{ -2, -2, 2 },{ -2, -2, 2 } },
	{ { -2.0, 1, 0 },{ -1.25, 1, 1 },{ -1, 1, 1.25 },{ 0.0, 1, 2.0 } },
	{ { 0.0, 0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0, 0 },{ 0, 0.0, 0 } }

};

static float controlPoints41[6][4][3] =
{
	{ { 0.0, 0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0, 0 },{ 0, 0.0, 0 } },
	{ { 0, 0, 0 },{ 2, -2, -2 },{ 2, -2, -2 },{ 2, -2, -2 } },
	{ { 2.0, 1, 0 },{ 1.25, 1, -1 },{ 1, 1, -1.25 },{ 0.0, 1, -2.0 } }
	
};

static float controlPoints5[4][3]{
	{ 0, 1, 0.0 },{ 0.125, 2.5,0.0 },
	{ 0.25, 4,0.0 },{ 0.5, 6.5, 0.0 }
};


static float Xangle = 30.0, Yangle = 330.0, Zangle = 0.0; // Angles to rotate canoe.

// Routine to draw a stroke character string.
void writeStrokeString(void *font, char *string)
{
	char *c;

	for (c = string; *c != '\0'; c++) glutStrokeCharacter(font, *c);
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// Drawing routine.
void drawScene(void)
{
	int i, j;
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 12.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// Rotate scene.
	glRotatef(Zangle, 0.0, 0.0, 1.0);
	glRotatef(Yangle, 0.0, 1.0, 0.0);
	glRotatef(Xangle, 1.0, 0.0, 0.0);

	glPointSize(5.0);
	glColor3f(0.9, 0.2, 0.8);

	// Draw the Bezier surface and draw control points depending on the step number.


		glLineWidth(1.5);
		for (int i = 1; i <= 4; i++) {
			glColor3f(0.9, 0.2, 0.8);
			glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 6, controlPoints1[0][0]);
			glEnable(GL_MAP2_VERTEX_3); // Enable the Bezier surface.

										// Make a mesh approximation of the Bezier surface.

			glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
			glEvalMesh2(GL_LINE, 0, 20, 0, 20);
			glRotatef(90, 0, 1, 0);
		}
		/*
		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 6, controlPoints13[0][0]);
		glEnable(GL_MAP2_VERTEX_3); // Enable the Bezier surface.

									// Make a mesh approximation of the Bezier surface.
		//glColor3f(0.9, 0.2, 0.8);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_LINE, 0, 20, 0, 20);

		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 6, controlPoints14[0][0]);
		glEnable(GL_MAP2_VERTEX_3); // Enable the Bezier surface.

									// Make a mesh approximation of the Bezier surface.
		//glColor3f(0.9, 0.2, 0.8);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_LINE, 0, 20, 0, 20);


		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 6, controlPoints15[0][0]);
		glEnable(GL_MAP2_VERTEX_3); // Enable the Bezier surface.

									// Make a mesh approximation of the Bezier surface.
		//glColor3f(0.9, 0.2, 0.8);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_LINE, 0, 20, 0, 20);
		*/

		glColor3f(0, 0.4, 0);
		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 6, controlPoints21[0][0]);
		glEnable(GL_MAP2_VERTEX_3); // Enable the Bezier surface.

									// Make a mesh approximation of the Bezier surface.
		//glColor3f(0, 0.4, 0);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_LINE, 0, 20, 0, 20);

		//glColor3f(0, 0.4, 0);
		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 6, controlPoints22[0][0]);
		glEnable(GL_MAP2_VERTEX_3); // Enable the Bezier surface.

									// Make a mesh approximation of the Bezier surface.
									//glColor3f(0, 0.4, 0);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_LINE, 0, 20, 0, 20);


		//glColor3f(0, 0.4, 0);
		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 6, controlPoints23[0][0]);
		glEnable(GL_MAP2_VERTEX_3); // Enable the Bezier surface.

									// Make a mesh approximation of the Bezier surface.
									//glColor3f(0, 0.4, 0);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_LINE, 0, 20, 0, 20);

		//glColor3f(0, 0.4, 0);
		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 6, controlPoints23[0][0]);
		glEnable(GL_MAP2_VERTEX_3); // Enable the Bezier surface.

									// Make a mesh approximation of the Bezier surface.
									//glColor3f(0, 0.4, 0);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_LINE, 0, 20, 0, 20);


		//glColor3f(0, 0.4, 0);
		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 6, controlPoints24[0][0]);
		glEnable(GL_MAP2_VERTEX_3); // Enable the Bezier surface.

									// Make a mesh approximation of the Bezier surface.
									//glColor3f(0, 0.4, 0);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_LINE, 0, 20, 0, 20);


		for (int i = 0; i < 5; i++) {
			glColor3f(1, 0.5, 0.0);
			glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 6, controlPoints31[0][0]);
			//glEnable(GL_MAP2_VERTEX_3); // Enable the Bezier surface.

										// Make a mesh approximation of the Bezier surface.
										//glColor3f(0, 0.4, 0);
			glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
			glEvalMesh2(GL_LINE, 0, 20, 0, 20);
			glRotatef(72, 0, 1, 0);
		}

	//	glColor3f(0.5, 0.5, 0.5);
	//	glLineWidth(5.0);
		//glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, controlPoints5[0]);
		//glEnable(GL_MAP1_VERTEX_3);

		/*glRotatef(72, 0, 1, 0);
		
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_LINE, 0, 20, 0, 20);
		glRotatef(72, 0, 1, 0);
		
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_LINE, 0, 20, 0, 20);
		glRotatef(72, 0, 1, 0);
		
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_LINE, 0, 20, 0, 20);

		/*
		glBegin(GL_POINT);
		for (i = 0; i < 6; i++)
			for (j = 0; j < 4; j++)
				glVertex3fv(controlPoints1[i][j]);
		glEnd();
		*/
		glLineWidth(2);
		glRotatef(80, -1, 0, 0);
		glScalef(0.75, 0.75, 0.75);
		for (int i = 0; i < 4; i++){
		
			glColor3f(1, 0.2, 0.2);
			glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 6, controlPoints1[0][0]);
			glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
			glEvalMesh2(GL_LINE, 0, 20, 0, 20);
			glRotatef(45, 0, 0, 1);
		}
		glRotatef(-80, -1, 0, 0);
		glScalef(1, 1, 1);
		
		glPushMatrix();
		glLineWidth(8);
		glColor3f(0.1, 0.4, 0.0);
		float stemPoints[6][3] = {
			{ 0, 0, 0.0 },{ 0, -8, 0.0 },{ 0, -16, 0.0 },
			{ 0, -18, 0.0 },{ 0, -20.0, 0.0 },{ 0, -25, 0.0 } 
		};

		
		/*
		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 6, stemPoints[0][0]);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_LINE, 0, 20, 0, 20);
		*/
		
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 2, stemPoints[0]);
		glEnable(GL_MAP1_VERTEX_3);

		// Draw the Bezier curve by defining a sample grid and evaluating on it.
	
		glMapGrid1f(100, 0.0, 1.0);
		glEvalMesh1(GL_LINE, 0, 100);

		
		glLineWidth(2);
		glTranslatef(0, -5, 0.0);
		glScalef(0.5, 0.5, 0.5);
		//glColor3f(1, 0.5, 0.0);
		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 6, controlPoints31[0][0]);
		glEnable(GL_MAP2_VERTEX_3); // Enable the Bezier surface.

		// Make a mesh approximation of the Bezier surface.
		//glColor3f(0, 0.4, 0);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEvalMesh2(GL_LINE, 0, 20, 0, 20);
		//glRotatef(72, 0, 1, 0);
		glPopMatrix();
		glutSwapBuffers();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 50.0);
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

// Callback routine for non-ASCII key entry.


// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press left and right arrow keys for successive steps." << std::endl
		<< "Press the x, X, y, Y, z, Z keys to rotate the viewpoint." << std::endl;
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
	glutCreateWindow("Flower.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	//glutSpecialFunc(specialKeyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
