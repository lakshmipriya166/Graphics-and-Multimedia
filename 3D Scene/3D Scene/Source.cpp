//#define _CRT_SECURE_NO_WARNINGS
#include <GL/glut.h>
int INC = 1;

void initialize(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glShadeModel(GL_SMOOTH);
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 0, 0, 1, 0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void drawScene(int state)
{
	if (state == 0)
		INC = 1;
	else if (state == 10)
		INC = -1;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 1.0, 7.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);

	// Cube
	glPushMatrix();
	GLfloat cube_color[] = { 1, 0.5, 0.0, 0.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_color);
	glScalef(4, 1.5, 1.0);
	glTranslatef(0.2, -1.0, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();

	// Torus
	glPushMatrix();
	GLfloat torus_color[] = { 0.59, 0.1, 0.55, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, torus_color);
	glTranslatef(-3, -1.5, 0.0);
	glutSolidTorus(0.3, 0.7, 10, 10);
	glPopMatrix();

	// Teapot
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	GLfloat teapot_color[] = { 0.7, 0.7, 0.7, 0.0 };
	GLfloat mat_shininess[] = { 100 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, teapot_color);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glRotatef(45, 0, 0, 1);
	glTranslatef(-1.2, 0.8, 0.0);
	glutSolidTeapot(0.7);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// Sphere
	glPushMatrix();
	GLfloat ball_color[] = { 0.0, 1, 1, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ball_color);
	glTranslatef(2, 2.1 - 0.25 * state, 0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();

	glutSwapBuffers();
	glutTimerFunc(1000 / 60, drawScene, state + INC);
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 20);
	glMatrixMode(GL_MODELVIEW);
}

void sceneDemo() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutTimerFunc(1000 / 60, drawScene, 0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("3D Scene");
	initialize();
	glutDisplayFunc(sceneDemo);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}