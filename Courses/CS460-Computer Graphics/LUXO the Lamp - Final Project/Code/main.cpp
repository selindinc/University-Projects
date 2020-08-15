#define GL_SILENCE_DEPRECATION
#include"display.hpp"
#include"util.hpp"
#include <GLUT/glut.h>
#include <OpenGL/gl.h>

void init(void){
    gluOrtho2D(0.0,1000.0,0.0,1000.0);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);
    
}
void timer(int){
    /* update animation */
    glutPostRedisplay();
    glutTimerFunc(1000.0/60.0, timer, 0);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH| GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowSize(1000, 1000);
    //glutInitWindowPosition(1000, 1000);
    glutCreateWindow("Luxo");
    
    init();
    
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glShadeModel(GL_SMOOTH);
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutTimerFunc(1000.0/60.0, timer, 0);
    glutMainLoop();
    return 0;
}










