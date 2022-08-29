#include<iostream>
#include<GL/glut.h>
using namespace std;

int xc, yc, r;

void plot(int x, int y)
{
	glColor3f(0.5f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex2i(x + xc, y + yc);
	glEnd();
}

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-200.0, 200.0, -200.0, 200.0);
}


void midPointCircleAlgorithm()
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
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);

	glBegin(GL_LINES);
	glVertex2d(0, -200);
	glVertex2d(0, 200);
	glVertex2d(-200, 0);
	glVertex2d(200, 0);
	glEnd();

	midPointCircleAlgorithm();

	glFlush();
}

void main(int argc, char** argv)
{
	cout << "Enter coordinates of center:" << endl;
	cout << "xc	: "; 
	cin >> xc;
	cout << "yc	: "; 
	cin >> yc;
	cout << "\nEnter radius : "; 
	cin >> r;


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Midpoint Circle Drawing Alogrithm");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();

}
