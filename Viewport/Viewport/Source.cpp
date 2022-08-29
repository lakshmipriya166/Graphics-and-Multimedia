#include <iostream>
#include <GL/glut.h>
using namespace std;

// boundary values for window
int x_wmax = 80, y_wmax = 80, x_wmin = 20, y_wmin = 40;

// boundary values for viewport
int x_vmax = 60, y_vmax = 60, x_vmin = 30, y_vmin = 40;

// points in object
int points[][2] = { {30, 60}, {40, 70}, {40, 65}, {60, 65}, {60, 70}, 
					{70, 60}, {60, 50}, {60, 55}, {40, 55}, {40, 50}
				  };
int npoints = 10;

// Function for window to viewport transformation
void WindowtoViewport(int x_w, int y_w, int result[])
{
	// point on viewport
	int x_v, y_v;

	// scaling factors for x coordinate and y coordinate
	float sx, sy;

	// calculating sx and sy
	sx = (float)(x_vmax - x_vmin) / (x_wmax - x_wmin);
	sy = (float)(y_vmax - y_vmin) / (y_wmax - y_wmin);

	// calculating the point on viewport
	x_v = x_vmin + (float)((x_w - x_wmin) * sx);
	y_v = y_vmin + (float)((y_w - y_wmin) * sy);

	cout << "\nThe point on window: (" << x_w << "," << y_w << ")" << endl;
	cout << "The point on viewport: (" << x_v << "," << y_v << ")" << endl;

	result[0] = x_v; 
	result[1] = y_v;
}

// Display1 callback
void display1()
{
	// clear the draw buffer .
	glClear(GL_COLOR_BUFFER_BIT);   // Erase everything
	// gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
	gluOrtho2D(0, 100, 0, 100);
	
	// create a polygon ( define the vertexs)
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2f(x_wmin, y_wmin);
	glVertex2f(x_wmin, y_wmax);
	glVertex2f(x_wmax, y_wmax);
	glVertex2f(x_wmax, y_wmin);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 0);

	for (int i = 0; i < npoints; i++) {
		glVertex2f(points[i][0], points[i][1]);
	}
	
	glEnd();

	glFlush();
}

// Display2 callback
void display2()
{
	// clear the draw buffer .
	glClear(GL_COLOR_BUFFER_BIT); 
	
	// gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
	gluOrtho2D(0, 100, 0, 100);

	// create a polygon ( define the vertexs)
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2f(x_vmin, y_vmin);
	glVertex2f(x_vmin, y_vmax);
	glVertex2f(x_vmax, y_vmax);
	glVertex2f(x_vmax, y_vmin);
	glEnd();
	
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 0);

	int result[2];
	for (int i = 0; i < npoints; i++) {
		WindowtoViewport(points[i][0], points[i][1], result); 
		glVertex2f(result[0], result[1]);
	}
	
	glEnd();

	glFlush();
}

// Main execution  function
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);      // Initialize GLUT

	glutInitWindowPosition(50, 50);
	glutInitWindowSize(500, 500);

	glutCreateWindow("Window");   // Create a window 1
	glutDisplayFunc(display1);   // Register display1 callback

	glutInitWindowPosition(650, 50);
	glutInitWindowSize(500, 500);

	glutCreateWindow("Viewport");   // Create a window 2
	glutDisplayFunc(display2);   // Register display2 callback

	glutMainLoop();             // Enter main event loop
}