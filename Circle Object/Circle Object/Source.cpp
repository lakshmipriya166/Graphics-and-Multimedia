#include<iostream>
#include <GL/glut.h>
using namespace std;

int xc = 0, yc = 0;

void plot(int x, int y)
{
	//glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2i(x + xc, y + yc);
	glEnd();
}

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(10.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-200.0, 200.0, -200.0, 200.0);
}


void midPointCircleAlgorithm(float r)
{
	int x = 0;
	int y = r;
	float decision = 1 - r;
	plot(x, y);

	while (y > x)
	{
		if (decision < 0)
		{
			x++;
			decision += 2 * x + 1;
		}
		else
		{
			y--;
			x++;
			decision += 2 * (x - y) + 1;
		}
		plot(x, y);
		plot(x, -y);
		plot(-x, y);
		plot(-x, -y);
		plot(y, x);
		plot(-y, x);
		plot(y, -x);
		plot(-y, -x);
	}

}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2);

	//yellow inner circle
	glColor3f(1.0, 1.0, 0.0);
	for (int i = 1; i < 20; i++) {
		midPointCircleAlgorithm(i);
	}
	//black outline
	glColor3f(0.0, 0.0, 0.0);
	midPointCircleAlgorithm(10);
	midPointCircleAlgorithm(20);

	//red inner circle
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 21; i < 40; i++) {
		midPointCircleAlgorithm(i);
	}
	//black outline
	glColor3f(0.0, 0.0, 0.0);
	midPointCircleAlgorithm(30);
	midPointCircleAlgorithm(40);

	//blue inner circle
	glColor3f(0.0, 0.8, 0.8);
	for (int i = 41; i < 60; i++) {
		midPointCircleAlgorithm(i);
	}
	//black outline
	glColor3f(0.0, 0.0, 0.0);
	midPointCircleAlgorithm(50);
	midPointCircleAlgorithm(60);

	//black inner circle
	glColor3f(0.0, 0.0, 0.0);
	for (int i = 61; i < 80; i++) {
		midPointCircleAlgorithm(i);
	}
	//white outline
	glColor3f(1.0, 1.0, 1.0);
	midPointCircleAlgorithm(70);

	//black outline
	glColor3f(0.0, 0.0, 0.0);
	midPointCircleAlgorithm(80);
	midPointCircleAlgorithm(90);
	midPointCircleAlgorithm(100);

	glFlush();
}

int main(int argc, char** argv)
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Target");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();

}