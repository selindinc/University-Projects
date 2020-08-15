//
//  background.cpp
//  luxo_demo_2
//
//  Created by Selin Dinc on 8.05.2020.
//  Copyright © 2020 Selin Dinc. All rights reserved.
//
#define GL_SILENCE_DEPRECATION
#include "background.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>


int press_x, press_y;
int release_x, release_y;
int xform_mode = 0;


//  Draw x-y-z axes in three different colors
void draw_axes()
{
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(.15,0,0);
    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,.15,0);
    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,.15);
    glEnd();
    glLineWidth(1.0);
}

//   draw a quad for floor
void draw_floor()
{
    glColor3f(.560784,.560784,0.737255);
    glPushMatrix();
    glScalef(4, 0.01, 4);
    glBegin(GL_QUADS);
    glNormal3f(-1,0,1);
    glVertex3f(-0.5, 0, 0.5);
    glNormal3f(1,0,1);
    glVertex3f(0.5, 0, 0.5);
    glNormal3f(1,0,-1);
    glVertex3f(0.5, 0 , -0.5);
    glNormal3f(-1, 0, -1);
    glVertex3f(-0.5, 0, -0.5);
    glEnd();
    glPopMatrix();
}

//  draw a wall
void draw_wall()
{
    glColor4f(.6,.6,1,1);
    glPushMatrix();
    glScalef(4, 0.01, 5);
    glutSolidCube(1.0);
    glPopMatrix();
}

