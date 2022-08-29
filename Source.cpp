#include<GL/glut.h>

void myInit()
{
	//background color red + blue = yellow
	glClearColor(1.0, 1.0, 0, 0.2);
	//setting color of objects = dark red
	glColor3f(0.5f, 0.0f, 0.0f);
	//size of point
	glPointSize(10);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}
void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);
	glVertex2d(50, 120);
	glVertex2d(50, 160);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(150, 120);
	glVertex2d(200, 160);

	glVertex2d(200, 120);
	glVertex2d(150, 160);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2d(250, 120);
	glVertex2d(260, 160);
	glVertex2d(270, 120);
	glVertex2d(280, 160);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2d(250, 200);
	glVertex2d(260, 240);
	glVertex2d(270, 200);
	glVertex2d(280, 240);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2d(310, 120);
	glVertex2d(330, 120);
	glVertex2d(320, 160);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(330, 210);
	glVertex2f(340, 215);
	glVertex2f(310, 220);
	glVertex2f(330, 235);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(330, 300);
	glVertex2d(310, 310);
	glVertex2d(320, 315);
	glVertex2d(340, 315);
	glVertex2d(350, 310);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2d(390, 120);
	glVertex2d(390, 160);
	glVertex2d(440, 140);
	glVertex2d(440, 100);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glVertex2d(390, 210);
	glVertex2d(410, 210);
	glVertex2d(400, 240);
	glVertex2d(410, 250);
	glVertex2d(430, 230);
	glVertex2d(430, 260);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(440, 300);
	glVertex2d(440, 310);
	glVertex2d(450, 320);
	glVertex2d(430, 325);
	glVertex2d(420, 325);
	glVertex2d(400, 320);
	glEnd();

	glFlush();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(840, 680);

	glutCreateWindow("Output Primitives");
	glutDisplayFunc(myDisplay);

	myInit();
	glutMainLoop();

	return 1;
}