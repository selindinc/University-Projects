#include <GLUT/glut.h> //Max OSX
#include <cstdlib>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;


struct Line{
    float mx1,my1,mx2,my2;
};

vector<Line> lines;
bool clickR=false;
bool clickL=false;

void mouse(int button, int state, int x, int y) {
    
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        Line line;
        if(clickR){
            lines.clear();
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
            glClear(GL_COLOR_BUFFER_BIT);
            clickR =false;
        }
        line.mx1 = x;
        line.my1 = y;
        line.mx2 = x;
        line.my2 = y;
        lines.push_back(line);
        clickL = true;
    }
    
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        lines.at(lines.size()-1).mx2 = x;
        lines.at(lines.size()-1).my2 = y;
        clickR = true;
        clickL =false;
    }
}

void motion(int x, int y) {
    if(clickL){
        lines.at(lines.size()-1).mx2 = x;
        lines.at(lines.size()-1).my2 = y;
        glutPostRedisplay();
    }
}

void display(){
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 1.0f); // Blue
    
    for(int i=0; i<lines.size(); i++){
        glVertex2f((500-lines.at(i).mx1)/-500,(lines.at(i).my1-390)/-420);
        glVertex2f((500-lines.at(i).mx2)/-500,(lines.at(i).my2-390)/-420);
    }
    
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);                 // Initialize GLUT
    glutInitWindowSize(1000, 1000);   // Set the window's initial width & height
    glutInitWindowPosition(1000, 1000); // Position the window's initial top-left corner
    
    glutCreateWindow("mouseClick");
    glutDisplayFunc(display); // Register display callback handler for window re-paint
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(motion);
    
    glutMainLoop();           // Enter the event-processing loop
    return 0;
}

