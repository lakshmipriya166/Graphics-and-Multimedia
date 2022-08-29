#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

GLsizei winWidth = 600, winHeight = 600;
GLfloat xwcMin = -200.0, xwcMax = 200.0;
GLfloat ywcMin = -200.0, ywcMax = 200.0;
GLfloat zwcMin = -200.0, zwcMax = 200.0;

class point3d
{
public: GLfloat x, y, z;
};


static GLfloat input[8][3] =
{
    {40,40,-50}, {90,40,-50}, {90,90,-50}, {40,90,-50},
    {30,30,0}, {80,30,0}, {80,80,0}, {30,80,0} 
};


typedef GLfloat Matrix4x4[4][4];
Matrix4x4 matComposite;
const GLdouble pi = 3.14159;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void Matrix4x4SetIdentity(Matrix4x4 matIdent4x4)
{
	GLint row, col;
	for (row = 0; row < 4; row++)
		for (col = 0; col < 4; col++)
			matIdent4x4[row][col] = (row == col);
}

void Matrix4x4PreMultiply(Matrix4x4 m1, Matrix4x4 m2)
{
	GLint row, col;
	Matrix4x4 matTemp;
	for (row = 0; row < 4; row++)
		for (col = 0; col < 4; col++)
			matTemp[row][col] = m1[row][0] * m2[0][col] + m1[row][1] * m2[1][col] + m1[row][2] * m2[2][col] + m1[row][3] * m2[3][col];
	for (row = 0; row < 4; row++)
		for (col = 0; col < 4; col++)
			m2[row][col] = matTemp[row][col];
}

void translate3D(GLfloat tx, GLfloat ty, GLfloat tz)
{
	Matrix4x4 matTransl;
	Matrix4x4SetIdentity(matTransl);
	matTransl[0][3] = tx;
	matTransl[1][3] = ty;
	matTransl[2][3] = tz;
	Matrix4x4PreMultiply(matTransl, matComposite);
}

void rotate3D_x_axis(GLfloat theta)
{
    //x-axis rotation
	Matrix4x4 matRot;
	Matrix4x4SetIdentity(matRot);
	matRot[1][1] = cos(theta);
	matRot[1][2] = -sin(theta);
	matRot[2][1] = sin(theta);
	matRot[2][2] = cos(theta);
	Matrix4x4PreMultiply(matRot, matComposite);
}

void rotate3D_y_axis(GLfloat theta)
{
    //y-axis rotation
    Matrix4x4 matRot;
    Matrix4x4SetIdentity(matRot);
    matRot[0][0] = cos(theta);
    matRot[0][2] = sin(theta);
    matRot[2][0] = -sin(theta);
    matRot[2][2] = cos(theta);
    Matrix4x4PreMultiply(matRot, matComposite);
}

void rotate3D_z_axis(GLfloat theta)
{
    //z-axis rotation
    Matrix4x4 matRot;
    Matrix4x4SetIdentity(matRot);
    matRot[0][0] = cos(theta);
    matRot[0][1] = -sin(theta);
    matRot[1][0] = sin(theta);
    matRot[1][1] = cos(theta);
    Matrix4x4PreMultiply(matRot, matComposite);
}

void scale3D(GLfloat sx, GLfloat sy, GLfloat sz, point3d fixedPt)
{
	Matrix4x4 matScale;
	Matrix4x4SetIdentity(matScale);
	matScale[0][0] = sx;
	matScale[0][3] = (1 - sx) * fixedPt.x;
	matScale[1][1] = sy;
	matScale[1][3] = (1 - sy) * fixedPt.y;
	matScale[2][2] = sz;
	matScale[2][3] = (1 - sz) * fixedPt.z;
	Matrix4x4PreMultiply(matScale, matComposite);
}

void transformVerts3D(GLint nVerts, point3d* verts, point3d* plotverts)
{
	GLint k;
	for (k = 0; k < nVerts; k++)
	{
		plotverts[k].x = matComposite[0][0] * verts[k].x + matComposite[0][1] * verts[k].y + matComposite[0][2] * verts[k].z + matComposite[0][3];
		plotverts[k].y = matComposite[1][0] * verts[k].x + matComposite[1][1] * verts[k].y + matComposite[1][2] * verts[k].z + matComposite[1][3];
		plotverts[k].z = matComposite[2][0] * verts[k].x + matComposite[2][1] * verts[k].y + matComposite[2][2] * verts[k].z + matComposite[2][3];
	}
}

void drawObject(point3d* verts)
{
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 0.0); //behind face
    glVertex3f(verts[0].x, verts[0].y, verts[0].z);
    glVertex3f(verts[1].x, verts[1].y, verts[1].z);
    glVertex3f(verts[2].x, verts[2].y, verts[2].z);
    glVertex3f(verts[3].x, verts[3].y, verts[3].z);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 1.0);  //bottom face
    glVertex3f(verts[0].x, verts[0].y, verts[0].z);
    glVertex3f(verts[1].x, verts[1].y, verts[1].z);
    glVertex3f(verts[5].x, verts[5].y, verts[5].z);
    glVertex3f(verts[4].x, verts[4].y, verts[4].z);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 1.0); //left face
    glVertex3f(verts[0].x, verts[0].y, verts[0].z);
    glVertex3f(verts[4].x, verts[4].y, verts[4].z);
    glVertex3f(verts[7].x, verts[7].y, verts[7].z);
    glVertex3f(verts[3].x, verts[3].y, verts[3].z);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 1.0);  //right face
    glVertex3f(verts[1].x, verts[1].y, verts[1].z);
    glVertex3f(verts[2].x, verts[2].y, verts[2].z);
    glVertex3f(verts[6].x, verts[6].y, verts[6].z);
    glVertex3f(verts[5].x, verts[5].y, verts[5].z);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0); //up face
    glVertex3f(verts[2].x, verts[2].y, verts[2].z);
    glVertex3f(verts[3].x, verts[3].y, verts[3].z);
    glVertex3f(verts[7].x, verts[7].y, verts[7].z);
    glVertex3f(verts[6].x, verts[6].y, verts[6].z);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0); //front face
    glVertex3f(verts[4].x, verts[4].y, verts[4].z);
    glVertex3f(verts[5].x, verts[5].y, verts[5].z);
    glVertex3f(verts[6].x, verts[6].y, verts[6].z);
    glVertex3f(verts[7].x, verts[7].y, verts[7].z);
    glEnd();

	glFlush();

	/*
    // outlines
    glBegin(GL_LINE_LOOP);
    glLineWidth(10);
    glColor3f(0.0, 0.0, 0.0); //behind outline
    glVertex3f(verts[0].x, verts[0].y, verts[0].z);
    glVertex3f(verts[1].x, verts[1].y, verts[1].z);
    glVertex3f(verts[2].x, verts[2].y, verts[2].z);
    glVertex3f(verts[3].x, verts[3].y, verts[3].z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glLineWidth(10);
    glColor3f(0.0, 0.0, 0.0);  //bottom outline
    glVertex3f(verts[0].x, verts[0].y, verts[0].z);
    glVertex3f(verts[1].x, verts[1].y, verts[1].z);
    glVertex3f(verts[5].x, verts[5].y, verts[5].z);
    glVertex3f(verts[4].x, verts[4].y, verts[4].z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glLineWidth(10);
    glColor3f(0.0, 0.0, 0.0); //left outline
    glVertex3f(verts[0].x, verts[0].y, verts[0].z);
    glVertex3f(verts[4].x, verts[4].y, verts[4].z);
    glVertex3f(verts[7].x, verts[7].y, verts[7].z);
    glVertex3f(verts[3].x, verts[3].y, verts[3].z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glLineWidth(10);
    glColor3f(0.0, 0.0, 0.0);  //right outline
    glVertex3f(verts[1].x, verts[1].y, verts[1].z);
    glVertex3f(verts[2].x, verts[2].y, verts[2].z);
    glVertex3f(verts[6].x, verts[6].y, verts[6].z);
    glVertex3f(verts[5].x, verts[5].y, verts[5].z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glLineWidth(10);
    glColor3f(0.0, 0.0, 0.0); //up outline
    glVertex3f(verts[2].x, verts[2].y, verts[2].z);
    glVertex3f(verts[3].x, verts[3].y, verts[3].z);
    glVertex3f(verts[7].x, verts[7].y, verts[7].z);
    glVertex3f(verts[6].x, verts[6].y, verts[6].z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glLineWidth(10);
    glColor3f(0.0, 0.0, 0.0); //front outline
    glVertex3f(verts[4].x, verts[4].y, verts[4].z);
    glVertex3f(verts[5].x, verts[5].y, verts[5].z);
    glVertex3f(verts[6].x, verts[6].y, verts[6].z);
    glVertex3f(verts[7].x, verts[7].y, verts[7].z);
    glEnd();

    glFlush();
	*/
}

void displayFcn(void)
{
	GLint nVerts;
	point3d verts[10]; // = { {50, 50}, {25, 100}, {50, 150} ,{75, 100} };
	point3d plotverts[10];

    drawObject(verts);
    glFlush();
	while (true) {

        nVerts = 8;

		/*
		cout << "\n\nEnter number of vertices: ";
		cin >> nVerts;

		for (int i = 0; i < nVerts; i++) {
			cout << "\n\nVertex " << i + 1 << ": " << endl;
			cout << "Enter x-coordiante: ";
			cin >> verts[i].x;
			cout << "Enter y-coordiante: ";
			cin >> verts[i].y;
			cout << "Enter z-coordiante: ";
			cin >> verts[i].z;
		}
		*/
		
		
        for (int i = 0; i < nVerts; i++) {
            verts[i].x = input[i][0];
            verts[i].y = input[i][1];
            verts[i].z = input[i][2];
        }
		

		GLfloat tx, ty, tz;
		GLfloat sx, sy, sz;
		GLdouble theta;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINES);

		glVertex3d(0, -200, 0);
		glVertex3d(0, 200, 0);

		glVertex3d(-200, 0, 0);
		glVertex3d(200, 0, 0);

		glVertex3d(0, 0, -200);
		glVertex3d(0, 0, 200);

		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		drawObject(verts);
		glFlush();

		int opt;
		while (true) {

			point3d centroidPt;
			GLint k, xSum = 0, ySum = 0, zSum = 0;
			for (k = 0; k < nVerts; k++)
			{
				xSum += verts[k].x;
				ySum += verts[k].y;
				zSum += verts[k].z;

			}
			centroidPt.x = GLfloat(xSum) / GLfloat(nVerts);
			centroidPt.y = GLfloat(ySum) / GLfloat(nVerts);
			centroidPt.z = GLfloat(zSum) / GLfloat(nVerts);
			point3d fixedPt;
			fixedPt = centroidPt;

			Matrix4x4SetIdentity(matComposite);

			cout << "\nEnter\n\t<1> for translation" <<
				    "\n\t<2> for rotation about x axis" <<
                    "\n\t<3> for rotation about y axis" <<
                    "\n\t<4> for rotation about z axis" <<
				    "\n\t<5> for scaling" <<
				    "\n\t<6> for new object\n\t: ";
			cin >> opt;

			switch (opt) {
			case 1:
				cout << "\nEnter translation along x: ";
				cin >> tx;
				cout << "Enter translation along y: ";
				cin >> ty;
				cout << "Enter translation along z: ";
				cin >> tz;
				translate3D(tx, ty, tz);
				glColor3f(0.0, 1.0, 0.0);
				break;
			case 2:
				cout << "\nEnter rotation angle (in degrees): ";
				cin >> theta;
				rotate3D_x_axis(theta * pi / 180);
				glColor3f(0.0, 0.0, 1.0);
				break;
            case 3:
                cout << "\nEnter rotation angle (in degrees): ";
                cin >> theta;
                rotate3D_y_axis(theta * pi / 180);
                glColor3f(0.0, 0.0, 1.0);
                break;
            case 4:
                cout << "\nEnter rotation angle (in degrees): ";
                cin >> theta;
                rotate3D_z_axis(theta * pi / 180);
                glColor3f(0.0, 0.0, 1.0);
                break;
			case 5:
				cout << "\nEnter scaling factor along x: ";
				cin >> sx;
				cout << "Enter scaling factor along y: ";
				cin >> sy;
				cout << "Enter scaling factor along z: ";
				cin >> sz;
				scale3D(sx, sy, sz, fixedPt);
				glColor3f(1.0, 1.0, 0.0);
				break;
			case 6:
				break;
			default:
				cout << "Enter valid option!!" << endl;
				continue;
			}

			if (opt == 6)
				break;

			transformVerts3D(nVerts, verts, plotverts);
			drawObject(plotverts);
			glFlush();
		}
	}
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xwcMin, xwcMax, ywcMin, ywcMax, zwcMin, zwcMax);
	// To Render the surfaces Properly according to their depths
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("3D Transformation");
	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
	return 0;
}