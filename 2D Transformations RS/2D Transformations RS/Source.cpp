#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

GLsizei winWidth = 600, winHeight = 600;
GLfloat xwcMin = -200.0, xwcMax = 200.0;
GLfloat ywcMin = -200.0, ywcMax = 200.0;

class point2d
{
public: GLfloat x, y;
};

typedef GLfloat Matrix3x3[3][3];
Matrix3x3 matComposite;
const GLdouble pi = 3.14159;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void matrix3x3SetIdentity(Matrix3x3 matIdent3x3)
{
	GLint row, col;
	for (row = 0; row < 3; row++)
		for (col = 0; col < 3; col++)
			matIdent3x3[row][col] = (row == col);
}

void matrix3x3PreMultiply(Matrix3x3 m1, Matrix3x3 m2)
{
	GLint row, col;
	Matrix3x3 matTemp;
	for (row = 0; row < 3; row++)
		for (col = 0; col < 3; col++)
			matTemp[row][col] = m1[row][0] * m2[0][col] + m1[row][1] * m2[1][col] + m1[row][2] * m2[2][col];
	for (row = 0; row < 3; row++)
		for (col = 0; col < 3; col++)
			m2[row][col] = matTemp[row][col];
}

void reflection_x()
{
	Matrix3x3 matRef;
	matrix3x3SetIdentity(matRef);
	matRef[1][1] = -1;
	matrix3x3PreMultiply(matRef, matComposite);
}

void reflection_y()
{
	Matrix3x3 matRef;
	matrix3x3SetIdentity(matRef);
	matRef[0][0] = -1;
	matrix3x3PreMultiply(matRef, matComposite);
}

void reflection_origin()
{
	Matrix3x3 matRef;
	matrix3x3SetIdentity(matRef);
	matRef[0][0] = -1;
	matRef[1][1] = -1;
	matrix3x3PreMultiply(matRef, matComposite);
}

void reflection_xy()
{
	Matrix3x3 matRef;
	matrix3x3SetIdentity(matRef);
	matRef[0][0] = 0;
	matRef[0][1] = 1;
	matRef[1][0] = 1;
	matRef[1][1] = 0;
	matrix3x3PreMultiply(matRef, matComposite);
}

void shearing_x(float sf)
{
	Matrix3x3 matShear;
	matrix3x3SetIdentity(matShear);
	matShear[0][1] = sf;
	matrix3x3PreMultiply(matShear, matComposite);
}

void shearing_y(float sf)
{
	Matrix3x3 matShear;
	matrix3x3SetIdentity(matShear);
	matShear[1][0] = sf;
	matrix3x3PreMultiply(matShear, matComposite);
}

void transformVerts2D(GLint nVerts, point2d* verts, point2d* plotverts)
{
	GLint k;
	GLfloat temp;
	for (k = 0; k < nVerts; k++)
	{
		temp = matComposite[0][0] * verts[k].x + matComposite[0][1] * verts[k].y + matComposite[0][2];
		plotverts[k].y = matComposite[1][0] * verts[k].x + matComposite[1][1] * verts[k].y + matComposite[1][2];
		plotverts[k].x = temp;
	}
}

void drawObject(GLint nVerts, point2d* verts)
{
	GLint k;
	glBegin(GL_POLYGON);
	for (k = 0; k < nVerts; k++)
		glVertex2f(verts[k].x, verts[k].y);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (k = 0; k < nVerts; k++)
		glVertex2f(verts[k].x, verts[k].y);
	glEnd();

}

void displayFcn(void)
{
	GLint nVerts;// = 3;
	point2d verts[10];// = { {10, 10}, {20, 50}, {30, 40} };//{ {50, 50}, {25, 100}, {50, 150} ,{100, 125}, {100, 75} };
	point2d plotverts[10];

	while (true) {

		cout << "\n\nEnter number of vertices: ";
		cin >> nVerts;

		for (int i = 0; i < nVerts; i++) {
			cout << "\n\nVertex " << i + 1 << ": " << endl;
			cout << "Enter x-coordiante: ";
			cin >> verts[i].x;
			cout << "Enter y-coordiante: ";
			cin >> verts[i].y;
		}

		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex2d(0, -200);
		glVertex2d(0, 200);
		glVertex2d(-200, 0);
		glVertex2d(200, 0);
		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		drawObject(nVerts, verts);
		glFlush();

		int opt;
		float sf;

		while (true) {

			matrix3x3SetIdentity(matComposite);

			cout << "\nEnter" <<
				"\n\t<1> Reflection along x-axis" << 
				"\n\t<2> Reflection along y-axis" << 
				"\n\t<3> Reflection about origin" <<
				"\n\t<4> Reflection about line x=y" <<
				"\n\t<5> Shearing along x-axis" <<
				"\n\t<6> Shearing along y-axis" <<
				"\n\t<7> for new object" <<
				"\n\t: ";
			cin >> opt;

			switch (opt) {
			case 1:
				reflection_x();
				glColor3f(0.0, 1.0, 0.0);
				break;

			case 2:
				reflection_y();
				glColor3f(0.0, 0.0, 1.0);
				break;

			case 3:
				reflection_origin();
				glColor3f(1.0, 1.0, 0.0);
				break;

			case 4:
				reflection_xy();
				glColor3f(0.0, 1.0, 1.0);
				break;

			case 5:
				cout << "Enter shearing factor: ";
				cin >> sf;

				shearing_x(sf);
				glColor3f(1.0, 0.0, 1.0);
				break;

			case 6:
				cout << "Enter shearing factor: ";
				cin >> sf;

				shearing_y(sf);
				glColor3f(1.0, 0.0, 1.0);
				break;

			case 7:
				break;

			default:
				cout << "Enter valid option!!" << endl;
				continue;
			}

			if (opt == 7)
				break;

			transformVerts2D(nVerts, verts, plotverts);
			drawObject(nVerts, plotverts);
			glFlush();
		}
	}
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("2D Transformation");
	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
	return 0;
}