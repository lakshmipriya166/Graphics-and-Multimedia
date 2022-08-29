#include <GL/glut.h>

void display1() {
    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-2.0, 2.0, -2.0, 2.0, -1.5, 1.5);

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);

    // render a wireframe teapot of size 1
    glutWireTeapot(1);
    glFlush();
}

void display2() {
    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);

    // Rotate and translate the world around to look like the camera moved.
    // gluLookAt(<#GLdouble eyeX#>, <#GLdouble eyeY#>, <#GLdouble eyeZ#>, 
              // <#GLdouble centerX#>, <#GLdouble centerY#>, <#GLdouble centerZ#>, 
              // <#GLdouble upX#>, <#GLdouble upY#>, <#GLdouble upZ#>)

    gluLookAt(0.0, 0.0, -3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // render a wireframe teapot of size 1
    glutWireTeapot(1);
    glFlush();
}


int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D Projections - Orthographic");
    glutDisplayFunc(display1);

    glutInitWindowPosition(700, 100);
    glutCreateWindow("3D Projections - Perspective");
    glutDisplayFunc(display2);

    glutMainLoop();
    return 1;
}

/*
#include <GL/glut.h>

void display1() {
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(1.0f, 0.0f, 0.0f);

    // render a wireframe teapot of size 1
    glutWireTeapot(1);
    glFlush();

}

void display2() {
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Rotate and translate the world around to look like the camera moved.
    // gluLookAt(<#GLdouble eyeX#>, <#GLdouble eyeY#>, <#GLdouble eyeZ#>, 
              // <#GLdouble centerX#>, <#GLdouble centerY#>, <#GLdouble centerZ#>, 
              // <#GLdouble upX#>, <#GLdouble upY#>, <#GLdouble upZ#>)

    gluLookAt(0.0, 0.0, -3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glColor3f(1.0f, 0.0f, 0.0f);

    // render a wireframe teapot of size 1
    glutWireTeapot(1);
    glFlush();

}

static void reshape1(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -1.5, 1.5);

    glMatrixMode(GL_MODELVIEW);
    glFlush();
}

static void reshape2(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D Projections - Orthographic");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glutDisplayFunc(display1);
    glutReshapeFunc(reshape1);

    glutInitWindowPosition(700, 100);
    glutCreateWindow("3D Projections - Perspective");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glutDisplayFunc(display2);
    glutReshapeFunc(reshape2);

    glutMainLoop();
    return 1;
}
*/