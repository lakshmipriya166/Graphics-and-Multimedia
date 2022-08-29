#include<GL/glut.h> //Handle window management operations
#include<iostream>
#include<math.h> //Mathematical functions
using namespace std;

//Initialization operation
void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);//Clear the window background color to white (red, green, blue, alpha transparency), the background color is not displayed
	//Next, tell OpenGL how to project the graphics to the display. The two-dimensional line is treated as a special case of the three-dimensional line in OpenGL.
	glMatrixMode(GL_PROJECTION);//Set the projection matrix, indicating that a series of operations are to be performed on the projection.
								/*glMatrixMode() function is to explain what to do next,
								 That is to tell the computer what I want to do before doing the next step,
								 GL_PROJECTION (projection), GL_MODELVIEW (model view), GL_TEXTURE (texture).
								 If the parameter is GL_PROJECTION, it is necessary to perform related operations on the projection,
								 That is to project an object onto a plane. */
	gluOrtho2D(0.0, 200.0, 0.0, 200.0);//gluOrtho2D(lift,right,bottom,top) refers to the model coordinate range corresponding to the screen area,
									   //The horizontal range of this projection operation is 0 to 200, and the vertical range is 0 to 150
	 //As long as it is an object defined in the matrix, it will be displayed on the window
}

void LineDDA(float xs, float ys, float xe, float ye)
{  //DDA drawing point and line algorithm

	float dx = (xe - xs);
	float dy = (ye - ys);

	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	float Xinc = dx / (float)steps;
	float Yinc = dy / (float)steps;

	float X = xs;
	float Y = ys;

	for (int i = 0; i <= steps; i++) {
		glVertex2i(round(X), round(Y));

		//cout << X << "-" << Y << "      " << round(X) << "-" << round(Y) << endl;
		X += Xinc;
		Y += Yinc;
	}
}

//Display straight line
void lineSegment(void)
{
	glClear(GL_COLOR_BUFFER_BIT);//Display the window as the color of the current buffer (the background color is not displayed),
							  //GL_COLOR_BUFFER_BIT is the color buffer, used to specify the bit value in the color buffer,
							//Is the value specified in the glClearColor function
	glColor3f(0.0, 0.0, 0.0);         //Set the color of the display object, which is black at this time. glColor3f(R,G,B),
								 //Set the color of the object displayed in the window, the minimum value of the three elements is 0 (not displayed), and the maximum is 1
	glPointSize(3.0f);          //Set the width of the point, that is, the line width      



	float xs, ys, xe, ye;
	while (true) {
		glColor3f(1, 0.0, 0.0);
		glBegin(GL_POINTS);            //Operate on element type glBegin(GLenum mode), mode is element type
								  //GL_LINES draws a set of straight lines. Use this constant to connect each set of adjacent endpoints to get a set of straight line segments,
								  //If only one point is specified in glBegin/glEnd, nothing is displayed. If an odd number of points are specified, the last point is ignored.
								 /*The OpenGL space uses the definition of the right-hand system, which is consistent with the horizontal direction of the screen, and the direction to the right is the x-axis;
								  The direction that is consistent with the vertical direction of the screen and the direction upward is the y-axis; the direction perpendicular to the screen and the direction outward is the z-axis
								 */
		cout << "\n\nEnter new coordinates: \n";
		cout << "X0: ";
		cin >> xs;
		cout << "Y0: ";
		cin >> ys;
		cout << "X1: ";
		cin >> xe;
		cout << "Y1: ";
		cin >> ye;

		LineDDA(xs, ys, xe, ye);      //DDA algorithm draw line
		glEnd();

		glFlush();                  //Forcibly clear the buffer and send the instruction to the slow hardware for immediate execution. After the instruction is transmitted, it will return immediately.
									//And glFinish immediately sends the instructions in the buffer to the hardware for execution, but it will wait until the hardware has executed these instructions before returning.

	}




}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);//Initialize GLUT
	/*This function is used to initialize the GLUT library. This function gets its two parameters from the main function. The form of the corresponding main function should be: int main(int argc, char* argv[]);
	 In this part we will create a main function in our program, this main function will complete the necessary initialization and open the event processing loop.
	 All GLUT functions have the glut prefix and those that do some initialization have the glutInit prefix. The first thing you need to do is to call the function glutInit(). */
	 /*GLUT (OpenGL Utility Toolkit) OpenGL program tool library, responsible for processing calls to the underlying operating system and I/O*/
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//Set the buffer and color mode of the window, the default single buffer and RGB color
	glutInitWindowPosition(50, 100);//Set the position of the window on the screen
	glutInitWindowSize(400, 300);//Set window size
	glutCreateWindow("DDA Line Drawing");//Create a window and display the window title
	init();
	glutDisplayFunc(lineSegment);//Assign the graph to the display window. glutDisplayFunc is used to refresh the window content when the window changes
	//glutDisplayFunc(&display) is automatically called when the program is running, that is, the program will automatically call the display function to redraw the window
	glutMainLoop();//Enter the GLUT event processing loop and let all the "event" related functions call an infinite loop. Once called, never return
}
