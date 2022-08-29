#include<GL/glut.h>
#include<iostream>

void display();
void drawLine();
using namespace std;

float xmin, ymin, xmax, ymax;
float xd1, yd1, xd2, yd2;
int c;
int flag = 1;

void init(void)
{
    glClearColor(0.0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-12, 12, -12, 12);
}

int code(float x, float y)
{
    int c = 0;
    if (y > ymax) c = 8;
    if (y < ymin) c = 4;
    if (x > xmax) c = c | 2;
    if (x < xmin) c = c | 1;
    return c;
}

void CohenSutherlandLineClipping()
{
    int c1 = code(xd1, yd1);
    int c2 = code(xd2, yd2);

    while ((c1 | c2) > 0) {

        if ((c1 & c2) > 0) {
            cout << "\n\nLine lies outsite boundary!";
            flag = 0;
            break;
        }

        int c = 0;

        if (c1 != 0)
            c = c1;
        else
            c = c2;

        float x, y;
        float m = (yd2 - yd1) / (xd2 - xd1);

        if ((c & 8) > 0) {
            y = ymax;
            x = xd1 + 1.0 / m * (ymax - yd1);
        }
        else if ((c & 4) > 0) {
            y = ymin;
            x = xd1 + 1.0 / m * (ymin - yd1);
        }
        else if ((c & 2) > 0) {
            x = xmax;
            y = yd1 + m * (xmax - xd1);
        }
        else if ((c & 1) > 0) {
            x = xmin;
            y = yd1 + m * (xmin - xd1);
        }
                
        if (c == c1) {
            xd1 = x;
            yd1 = y;
            cout << "\nPress 1 to clip: ";
            cin >> c;
            drawLine();
            c1 = code(xd1, yd1);
        }
        else if (c == c2) {
            xd2 = x;
            yd2 = y;
            cout << "\nPress 1 to clip: ";
            cin >> c;
            drawLine();
            c2 = code(xd2, yd2);
        }
    }
    if (flag == 1) 
        cout << "\n\nLine lies within boundary!!";
}

//void mykey(unsigned char key, int x, int y)
//{
//    if (key == 0) {
//        CohenSutherlandLineClipping(xd1, yd1, xd2, yd2);
//        glFlush();
//    }
//    if (key == 1) {
//        display();
//    }
//}

void display()
{
    drawLine();
    glFlush();
    CohenSutherlandLineClipping();
}

void drawLine() 
{
    cout << "\nEnd points of line:\t(" << xd1 << ", " << yd1 << ") and (" << xd2 << ", " << yd2 << ")\n";
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(0, 12);
    glVertex2f(0, -12);
    glVertex2f(-12, 0);
    glVertex2f(12, 0);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmin, ymax);
    glVertex2f(xmax, ymax);
    glVertex2f(xmax, ymin);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(xd1, yd1);
    glVertex2f(xd2, yd2);
    glEnd();
    glFlush();
    
}

int main(int argc, char** argv)
{
    cout << "Enter window co-ordinates:\n";
    cout << "xmin: ";
    cin >> xmin;
    cout << "ymin: ";
    cin >> ymin;
    cout << "xmax: ";
    cin >> xmax;
    cout << "ymax: ";
    cin >> ymax;

    cout << "\n\nEnter line co-ordinates:\n";
    cout << "x1: ";
    cin >> xd1;
    cout << "y1: ";
    cin >> yd1;
    cout << "x2: ";
    cin >> xd2;
    cout << "y2: ";
    cin >> yd2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Cohen-Sutherland Line Clipping");
    glutDisplayFunc(display);
    //glutKeyboardFunc(mykey);
    init();
    glutMainLoop();
    return 0;
}
