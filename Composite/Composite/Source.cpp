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

void transformVerts2D(GLint nVerts, point2d* verts)
{
	GLint k;
	GLfloat temp;
	GLfloat xmin = verts[0].x, xmax = verts[0].x, ymin = verts[0].y, ymax = verts[0].y;
	for (k = 0; k < nVerts; k++)
	{
		temp = matComposite[0][0] * verts[k].x + matComposite[0][1] * verts[k].y + matComposite[0][2];
		verts[k].y = matComposite[1][0] * verts[k].x + matComposite[1][1] * verts[k].y + matComposite[1][2];
		verts[k].x = temp;
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
	point2d verts[10];// = { {50.0, 25.0}, {150.0, 25.0}, {100.0, 100.0} ,{50, 100} };

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
		float sf;

		while (true) {

			point2d pivPt, fixedPt;

			matrix3x3SetIdentity(matComposite);

			cout << "\nEnter\n\t<1> for translation" <<
					"\n\t<2> for rotation" <<
					"\n\t<3> for scaling" << 
					"\n\t<4> Reflection along x-axis" <<
					"\n\t<5> Reflection along y-axis" <<
					"\n\t<6> Reflection about origin" <<
					"\n\t<7> Reflection about line x=y" <<
					"\n\t<8> Shearing along x-axis" <<
					"\n\t<9> Shearing along y-axis" <<
					"\n\t<10> for new object\n\t: ";
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
				cout << "\nEnter pivot point x-coordinate: ";
				cin >> pivPt.x;
				cout << "Enter pivot point y-coordinate: ";
				cin >> pivPt.y;
				rotate2D(pivPt, theta * pi / 180);
				glColor3f(0.0, 0.0, 1.0);
				break;

			case 3:
				cout << "\nEnter scaling factor along x: ";
				cin >> sx;
				cout << "Enter scaling factor along y: ";
				cin >> sy; 
				cout << "\nEnter fixed point x-coordinate: ";
				cin >> fixedPt.x;
				cout << "Enter fixed point y-coordinate: ";
				cin >> fixedPt.y;
				scale2D(sx, sy, fixedPt);
				glColor3f(1.0, 1.0, 0.0);
				break; 
			
			case 4:
				reflection_x();
				glColor3f(0.0, 1.0, 0.0);
				break;

			case 5:
				reflection_y();
				glColor3f(0.0, 0.0, 1.0);
				break;

			case 6:
				reflection_origin();
				glColor3f(1.0, 1.0, 0.0);
				break;

			case 7:
				reflection_xy();
				glColor3f(0.0, 1.0, 1.0);
				break;

			case 8:
				cout << "Enter shearing factor: ";
				cin >> sf;

				shearing_x(sf);
				glColor3f(1.0, 0.0, 1.0);
				break;

			case 9:
				cout << "Enter shearing factor: ";
				cin >> sf;

				shearing_y(sf);
				glColor3f(1.0, 0.0, 1.0);
				break;

			case 10:
				break;

			default:
				cout << "Enter valid option!!" << endl;
				continue;
			}

			if (opt == 10)
				break;
			transformVerts2D(nVerts, verts);
			drawObject(nVerts, verts);
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
	glutCreateWindow("2D Composite Transformation");
	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
	return 0;
}