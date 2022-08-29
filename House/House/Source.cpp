#include <GL\glut.h>

// Function to initialize the drivers
void myInit(void)
{
	// Clear all the screen color
	glClearColor(0.5, 0.8, 0.9, 1.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	// Specify the display area
	gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}

// Function to display the House

void myDisplay(void)
{
	// Clear the screen buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// Lawn
	glColor3f(0.36f, 0.83f, 0.28f);
	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glVertex2i(0, 100);
	glVertex2i(400, 100);
	glVertex2i(400, 0);
	glEnd();

	// Rectangular part of house
	glColor3f(0.60f, 0.42f, 0.16f);
	glBegin(GL_QUADS);
	glVertex2i(125, 250);
	glVertex2i(125, 100);
	glVertex2i(275, 100);
	glVertex2i(275, 250);
	glEnd();

	// Rectangular inner part of house
	glColor3f(0.96f, 0.74f, 0.44f);
	glBegin(GL_QUADS);
	glVertex2i(130, 242);
	glVertex2i(130, 107);
	glVertex2i(270, 107);
	glVertex2i(270, 242);
	glEnd();

	// Rectangular outline of house
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(10);
	glBegin(GL_LINES);
	glVertex2i(125, 250);
	glVertex2i(125, 95);

	glVertex2i(125, 98);
	glVertex2i(275, 98);

	glVertex2i(275, 95);
	glVertex2i(275, 250);
	glEnd();

	// Door
	glColor3f(0.396f, 0.24f, 0.016f);
	glBegin(GL_POLYGON);
	glVertex2i(180, 120);
	glVertex2i(180, 200);
	//glVertex2i(195, 210);
	glVertex2i(220, 200);
	glVertex2i(220, 120);
	glEnd();

	// Door outline
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	glVertex2i(180, 120);
	glVertex2i(180, 200);
	glVertex2i(220, 200);
	glVertex2i(220, 120);
	glEnd();

	// Left Window
	glColor3f(0.83f, 0.58f, 0.82f);
	glBegin(GL_POLYGON);
	glVertex2i(140, 160);
	glVertex2i(140, 200);
	glVertex2i(170, 200);
	glVertex2i(170, 160);
	glEnd();

	// Left Window outline
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(5);
	glBegin(GL_LINE_LOOP);
	glVertex2i(140, 160);
	glVertex2i(140, 200);
	glVertex2i(170, 200);
	glVertex2i(170, 160);
	glEnd();

	// Left Window inner outline
	glBegin(GL_LINES);
	glVertex2i(140, 185);
	glVertex2i(170, 185);

	glVertex2i(155, 185);
	glVertex2i(155, 160);
	glEnd();

	// Right Window
	glColor3f(0.83f, 0.58f, 0.82f);
	glBegin(GL_POLYGON);
	glVertex2i(230, 160);
	glVertex2i(230, 200);
	glVertex2i(260, 200);
	glVertex2i(260, 160);
	glEnd();

	// Right Window outline
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(5);
	glBegin(GL_LINE_LOOP);
	glVertex2i(230, 160);
	glVertex2i(230, 200);
	glVertex2i(260, 200);
	glVertex2i(260, 160);
	glEnd();

	// Right Window inner outline
	glBegin(GL_LINES);
	glVertex2i(230, 185);
	glVertex2i(260, 185);

	glVertex2i(245, 185);
	glVertex2i(245, 160);
	glEnd();

	// Door knob
	glColor3f(0.0f, 0.0f, 0.0f);
	//size of point
	glPointSize(15);
	glBegin(GL_POINTS);
	glVertex2i(185, 150);
	glEnd();

	// Create foot steps
	glColor3f(0.396f, 0.24f, 0.016f);
	// Begin the polygon
	glBegin(GL_POLYGON);
	glVertex2i(160, 100);
	glVertex2i(160, 120);
	glVertex2i(240, 120);
	glVertex2i(240, 100);
	glEnd();

	// House's top triangle
	glColor3f(0.60f, 0.42f, 0.16f);
	glBegin(GL_TRIANGLES);
	glVertex2i(100, 250);
	glVertex2i(300, 250);
	glVertex2i(200, 350);
	glEnd();

	// Top triangle inner triangle
	glColor3f(0.96f, 0.74f, 0.44f);
	glLineWidth(10);
	glBegin(GL_TRIANGLES);
	glVertex2f(120, 260);
	glVertex2f(280, 260);
	glVertex2f(200, 340);
	glEnd();

	// House's top triangle part
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2i(200, 270);
	glVertex2i(180, 280);
	glVertex2i(185, 290);
	glVertex2i(200, 300);
	glVertex2i(215, 290);
	glVertex2i(220, 280);
	glEnd();

	// chimney outlet smoke
	glColor3f(0.4f, 0.38f, 0.38f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(250, 340);
	glVertex2f(260, 345);
	glVertex2f(255, 350);
	glVertex2f(265, 355);
	glVertex2f(250, 360);
	glVertex2f(260, 365);
	glVertex2f(255, 370);
	glVertex2f(265, 375);
	glEnd();

	// chimney outlet
	glColor3f(0.396f, 0.24f, 0.016f);
	glBegin(GL_QUADS);
	glVertex2f(240, 320);
	glVertex2f(240, 335);
	glVertex2f(270, 335);
	glVertex2f(270, 320);
	glEnd();

	// chimney body
	glColor3f(0.96f, 0.74f, 0.44f);
	glLineWidth(5);
	glBegin(GL_QUADS);
	glVertex2f(250, 300);
	glVertex2f(250, 320);
	glVertex2f(260, 320);
	glVertex2f(260, 290);
	glEnd();

	// chimney outlet outline
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(5);
	glBegin(GL_LINE_LOOP);
	glVertex2f(240, 320);
	glVertex2f(240, 335);
	glVertex2f(270, 335);
	glVertex2f(270, 320);
	glEnd();

	glColor3f(0.60f, 0.42f, 0.16f);
	glLineWidth(10);
	glBegin(GL_LINE_LOOP);
	glVertex2f(250, 316);
	glVertex2f(260, 316);
	glEnd();

	// chimney body outline
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(250, 300);
	glVertex2f(250, 320);

	glVertex2f(260, 320);
	glVertex2f(260, 290);
	glEnd();

	// Top triangle outline
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(10);
	glBegin(GL_LINE_LOOP);
	glVertex2f(100, 250);
	glVertex2f(300, 250);
	glVertex2f(200, 350);
	glEnd();

	// Steps outline
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	glVertex2i(160, 100);
	glVertex2i(160, 120);
	glVertex2i(240, 120);
	glVertex2i(240, 100);
	glEnd();

	glBegin(GL_LINES);
	glVertex2i(160, 110);
	glVertex2i(240, 110);
	glEnd();

	// Pathway
	glColor3f(0.03f, 0.56f, 0.15f);
	glLineWidth(10);
	glBegin(GL_QUAD_STRIP);
	glVertex2f(180, 95);
	glVertex2f(220, 95);
	glVertex2f(170, 75);
	glVertex2f(210, 75);
	glVertex2f(180, 50);
	glVertex2f(220, 50);
	glVertex2f(170, 25);
	glVertex2f(210, 25);
	glVertex2f(180, 0);
	glVertex2f(220, 0);
	glEnd();

	// Sends all output to display
	glFlush();
}

// Driver Code
int main(int argc, char** argv)
{
	// Initialize using the init function
	glutInit(&argc, argv);

	// Sets the display mode and specify the colour scheme
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Specify the window size
	glutInitWindowSize(1200, 740);

	// Sets the starting position for the window
	glutInitWindowPosition(0, 0);

	// Creates the window and sets the title
	glutCreateWindow("House");

	glutDisplayFunc(myDisplay);

	// Additional initializations
	myInit();

	// Go into a loop until event occurs
	glutMainLoop();

	return 0;
}
