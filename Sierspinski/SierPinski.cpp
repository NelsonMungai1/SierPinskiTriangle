#include <GL/glut.h>
#include <cmath>

// defining the three colors of the GL_TRIANGLES
GLfloat colors[][3]={
    {0.0,1.0,0.0},
    {1.0,0.0,0.0},
    {0.0,0.0,1.0}
};

// Function to draw a triangle
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3,int color_index) {
    glBegin(GL_TRIANGLES);
    glColor3fv(colors[color_index]);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

// Function to recursively draw Sierpinski triangle
void drawSierpinski(float x1, float y1, float x2, float y2, float x3, float y3, int depth) {
    if (depth == 0) {
        drawTriangle(x1, y1, x2, y2, x3, y3,1);
    } else {
        float x12 = (x1 + x2) / 2.0;
        float y12 = (y1 + y2) / 2.0;
        float x23 = (x2 + x3) / 2.0;
        float y23 = (y2 + y3) / 2.0;
        float x31 = (x3 + x1) / 2.0;
        float y31 = (y3 + y1) / 2.0;

        drawSierpinski(x1, y1, x12, y12, x31, y31, depth - 1);
        drawSierpinski(x12, y12, x2, y2, x23, y23, depth - 1);
        drawSierpinski(x31, y31, x23, y23, x3, y3, depth - 1);
    }
}

// Function to display rendering
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // White color
    glLoadIdentity();

    // Adjust these values according to your window size
    float x1 = -0.5, y1 = -0.5;
    float x2 = 0.5, y2 = -0.5;
    float x3 = 0.0, y3 = 0.5;

    int depth = 0; // Adjust the depth for desired level of detail

    drawSierpinski(x1, y1, x2, y2, x3, y3, depth);

    glFlush();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500); // Set your window size
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sierpinski Triangle");

    glClearColor(0.0, 0.0, 0.0, 0.0); // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
