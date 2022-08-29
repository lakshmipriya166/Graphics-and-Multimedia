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

void translate2D(GLfloat tx, GLfloat ty)
{
	Matrix3x3 matTransl;
	matrix3x3SetIdentity(matTransl);
	matTransl[0][2] = tx;
	matTransl[1][2] = ty;
	matrix3x3PreMultiply(matTransl, matComposite);
}

void rotate2D(point2d pivotPt, GLfloat theta)
{
	Matrix3x3 matRot;
	matrix3x3SetIdentity(matRot);
	matRot[0][0] = cos(theta);
	matRot[0][1] = -sin(theta);
	matRot[0][2] = pivotPt.x * (1 - cos(theta)) + pivotPt.y * sin(theta);
	matRot[1][0] = sin(theta);
	matRot[1][1] = cos(theta);
	matRot[1][2] = pivotPt.y * (1 - cos(theta)) - pivotPt.x * sin(theta);
	matrix3x3PreMultiply(matRot, matComposite);
}

void scale2D(GLfloat sx, GLfloat sy, point2d fixedPt)
{
	Matrix3x3 matScale;
	matrix3x3SetIdentity(matScale);
	matScale[0][0] = sx;
	matScale[0][2] = (1 - sx) * fixedPt.x;
	matScale[1][1] = sy;
	matScale[1][2] = (1 - sy) * fixedPt.y;
	matrix3x3PreMultiply(matScale, matComposite);
}

void transformVerts2D(GLint nVerts, point2d* verts, point2d* plotverts)
{
	GLint k;
	for (k = 0; k < nVerts; k++)
	{
		plotverts[k].x = matComposite[0][0] * verts[k].x + matComposite[0][1] * verts[k].y + matComposite[0][2];
		plotverts[k].y = matComposite[1][0] * verts[k].x + matComposite[1][1] * verts[k].y + matComposite[1][2];
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
	GLint nVerts;
	point2d verts[10]; // = { {50, 50}, {25, 100}, {50, 150}, {75, 100} };
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

		GLfloat tx, ty;
		GLfloat sx, sy;
		GLdouble theta;
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
		while (true) {

			point2d centroidPt;
			GLint k, xSum = 0, ySum = 0;
			for (k = 0; k < nVerts; k++)
			{
				xSum += verts[k].x;
				ySum += verts[k].y;
			}
			centroidPt.x = GLfloat(xSum) / GLfloat(nVerts);
			centroidPt.y = GLfloat(ySum) / GLfloat(nVerts);
			point2d pivPt, fixedPt;
			pivPt = centroidPt;
			fixedPt = centroidPt;

			matrix3x3SetIdentity(matComposite);

			cout << "\nEnter\n\t<1> for translation" <<
					"\n\t<2> for rotation" <<
					"\n\t<3> for scaling"<<
					"\n\t<4> for new object\n\t: ";
			cin >> opt;

			switch (opt) {
			case 1:
				cout << "\nEnter translation along x: ";
				cin >> tx;
				cout << "Enter translation along y: ";
				cin >> ty;
				translate2D(tx, ty);
				glColor3f(0.0, 1.0, 0.0);
				break;
			case 2:
				cout << "\nEnter rotation angle (in degrees): ";
				cin >> theta;
				rotate2D(pivPt, theta * pi / 180);
				glColor3f(0.0, 0.0, 1.0);
				break;
			case 3:
				cout << "\nEnter scaling factor along x: ";
				cin >> sx;
				cout << "Enter scaling factor along y: ";
				cin >> sy;
				scale2D(sx, sy, fixedPt);
				glColor3f(1.0, 1.0, 0.0);
				break;
			case 4: 
				break;
			default:
				cout << "Enter valid option!!" << endl;
				continue;
			}

			if (opt == 4)
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