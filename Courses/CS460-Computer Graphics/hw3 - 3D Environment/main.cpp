#define GL_SILENCE_DEPRECATION
#include"menu.hpp"
#include"display.hpp"
#include<stdio.h>
#include<iostream>
#include<math.h>
#include<GLUT/GLUT.h>
#include<vector>
#include<assert.h>


//glutMainLoop never return;
int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(1000,1000);
    glutInitWindowPosition(100,100);
    glutCreateWindow("HW3");
    
    setup();
    
    // initializing callbacks
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    
    glutSpecialFunc(specialKey); //register a special keyboard function.
    //Creates Menu on Right Click
    CreateMenu();
    
    glutMainLoop();
    return 0;
    
}
