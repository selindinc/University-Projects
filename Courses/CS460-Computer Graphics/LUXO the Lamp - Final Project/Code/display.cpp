//
//  display.cpp
//  luxo_demo_2
//
//  Created by Selin Dinc on 8.05.2020.
//  Copyright © 2020 Selin Dinc. All rights reserved.
//
#define GL_SILENCE_DEPRECATION
#include "display.hpp"
#include"util.hpp"
#include "background.hpp"
#include <math.h>


GLsizei width, height;

float movex=0, movey=0, movez=0;
int flagLamp, flagTurn;
double baseR=0, firstR=0, secondR=0, lampR=0, baseFullR=0, lampR2=0;

int seq=0;

float x_angle = 0.0;
float y_angle = 0.0;
float scale_size = 1.0;
float camera_distance = 5.0;

#define XFORM_NONE    0
#define XFORM_ROTATE  1
#define XFORM_SCALE   2

#define BASE_HEIGHT  0.25
#define BASE_WIDE    0.05

typedef struct{
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;
} material;

int no_light = 0;
int draw_texture = 0;

float RED_LOW[] = {0.5f, 0.0f, 0.0f};
float BLACK[] = {0.0f, 0.0f, 0.0f, 1.0f};


void setup()
{
    glClearColor(0, 0, 0, 1.0); // *should* display black background
}

GLsizei getWidth(){
    return width;
}

GLsizei getHeight(){
    return height;
}

void lampLight() {
    float position[] = {1, 1, 1, 1.0f};
    float direction[] = {0.0, 0.0, 1.0};
    
    glLightfv(GL_LIGHT1, GL_DIFFUSE, RED_LOW);
    glLightfv(GL_LIGHT1, GL_POSITION, position);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
    
}

void reshape( int w, int h ){
    glViewport( 0, 0, (GLsizei)w, (GLsizei)h ); // set to size of window
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    
    glOrtho( 0, w, h, 0, -1, 1 );
    width = w;  // records width globally
    height = h; // records height globally
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void display(){
    glClearColor(0,0,0,1);  // specify the background color
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //clear framebuffer
    
    glEnable(GL_DEPTH_TEST);
    if (!no_light) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }
    glEnable(GL_NORMALIZE);   // normalize normals
    
    // set up texture mapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    // set up the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, .1, 100);
    
    
    // set up the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // set up the parameters for lighting
    GLfloat light_ambient[] = {0,0,0,1};
    GLfloat light_diffuse[] = {.6,.6,.6,1};
    GLfloat light_specular[] = {1,1,1,1};
    GLfloat light_pos[] = {1,1,1,0};
    
    glLightfv(GL_LIGHT0,GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    
    // position the camera
    gluLookAt(2, 0.5, 0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    /*eyeX, eyeY, eyeZ
     Specifies the position of the eye point.
     
     centerX, centerY, centerZ
     Specifies the position of the reference point.
     
     upX, upY, upZ
     Specifies the direction of the up vector.*/
    
    glRotatef(x_angle, 0, 1,0);
    glRotatef(y_angle, 1,0,0);
    glScalef(scale_size, scale_size, scale_size);
    
    // Start to draw the scene
    
    
    GLfloat mat_specular[] = {.7, .7, .7,1};
    GLfloat mat_shine[] = {60};
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shine);
    
    //draw_axes();
    
    // ------    draw floor
    draw_floor();                 // the floow is a 4x0.01x4 cube
    
    if (draw_texture)  {
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
    }
    
    // -------   draw wall
    glPushMatrix();
    glTranslatef(-0.5,1.5,0);
    
    glRotatef(90, 0, 0, 1);
    draw_wall();
    glPopMatrix();
    glColor3f(1,1,1);
        glPushMatrix();
        glScalef(0.01, 0.01, 0.01);
        
        double rStand = 0.5;
        int hStand = 10;
        
        int rJoint = 0.7;
        int hJoint = 5;
        
        
        basePlate(10, 10, 1);
        firstHalf(rStand, hStand, rJoint, hJoint, firstR);
        secondHalf(rStand, hStand, rJoint, hJoint, secondR);
        lamp(rStand, hStand, rJoint, hJoint, lampR);
        
        if(seq==0){
            flagLamp = 1;
        }
        else if(seq == 50){
            flagLamp = 0;
        }
        
        if(movez<120){
            forward();
        }
        else{
            if(movex == 0){
                flagTurn = 1;
                lampMove();
            }
            if(movex <-20.000000 ){
                flagTurn = 1;
                lampMove();
                
            }
            if(!flagTurn){
                in();
            }
            
        }
    
    
        glFlush();
        glPopMatrix();
    glPushMatrix();
    drawPixar();
    
    glFlush();
    glPopMatrix();
    
    glutSwapBuffers(); // display newly drawn image in window
}

void lampMove(){
    if(flagLamp==1){
        baseR+=0.6;
        firstR-=1;
        secondR-=2;
        lampR-=0.4;
        movey+=0.2;
        seq++;
    }
    else if (flagLamp==0){
        baseR-=0.6;
        firstR+=1;
        secondR+=2;
        lampR+=0.4;
        movey-=0.2;
        seq--;
    }
    else{
        if(lampR2<60){
            lampR2+=0.4;
        }
        else{
            glEnable(GL_LIGHT1);
        }
    }
    
    if(flagTurn && baseFullR <= 90){
        baseFullR+=2;
    }
    else if(flagTurn && movex <=-20 && baseFullR<=180){
        baseFullR+=2;
    }
    else if(flagTurn && movex <=-20 && baseFullR>180){
        if(flagLamp==1){
            flagLamp=2;
        }
    }
    else{
        flagTurn = false;
    }
    
}

void forward(){
    movez+=0.2;
    lampMove();
}

void in(){
    movex=movex-0.2;
    lampMove();
}


void basePlate(int base_radius, int top_radius, int height){
    GLUquadricObj* quadObj = gluNewQuadric ();
    gluQuadricDrawStyle (quadObj, GLU_FILL);
    glTranslated(0, 0, -70);
    glTranslated(movex, movey, movez);
    glRotated(90, 1, 0, 0);
    glRotated(baseFullR,0,0,1);
    glRotated(baseR,1,0,0);
    gluCylinder(quadObj, 10, 10, 1, 20, 10);
    gluDisk(quadObj, 0, 10, 20, 10);
    glRotated(-baseR,1,0,0);
    
    gluDeleteQuadric(quadObj);
}

void firstHalf(double rStand, int hStand, int rJoint, int hJoint, int fsAngle){
    GLUquadricObj* quadObj = gluNewQuadric ();
    gluQuadricDrawStyle (quadObj, GLU_FILL);
    
    
    //vertical cylinder
    glTranslated(0, 0, -1);
    gluCylinder(quadObj, 0.5, 0.5, 1,20,10);
    
    //horzontal cylinder - joint
    glTranslated(-2.5, 0, -1);
    glRotated(90, 0, 1, 0);
    glRotated(fsAngle, 0, 0, 1);
    gluCylinder(quadObj, 1, 1, 5,20,10);
    gluDisk(quadObj, 0, 1, 20, 10);//side disk1 (left)
    glTranslated(0, 0, 5);
    gluDisk(quadObj, 0, 1, 20, 10);//side disk2 (right)
    
    //vertical cylinder 1
    glTranslated(1, 0, -1.5);
    glRotated(90, 0, 1, 0);
    gluCylinder(quadObj, rStand, rStand, hStand,20,10);
    
    //vertical cylinder 2
    glTranslated(2, 0, 0);
    gluCylinder(quadObj, rStand, rStand, hStand,20,10);
    
    gluDeleteQuadric(quadObj);
}

void secondHalf(double rStand, int hStand, int rJoint, int hJoint, int fsAngle){
    GLUquadricObj* quadObj = gluNewQuadric ();
    gluQuadricDrawStyle (quadObj, GLU_FILL);
    
    //horzontal cylinder - joint
    glTranslated(1.5, 0, 10);
    glRotated(-90, 0, 1, 0);
    gluCylinder(quadObj, 1, 1, 5,20,10);
    gluDisk(quadObj, 0, 1, 20, 10);//side disk1 (left)
    glTranslated(0, 0, 5);
    gluDisk(quadObj, 0, 1, 20, 10);//side disk2 (right)
    
    //vertical cylinder 1
    glTranslated(1, 0, -1.5);
    glRotated(90, 0, 1, 0);
    glRotated(fsAngle, 1, 0, 0);
    gluCylinder(quadObj, rStand, rStand, hStand,20,10);
    
    //vertical cylinder 2
    glTranslated(2, 0, 0);
    gluCylinder(quadObj, rStand, rStand, hStand,20,10);
    
}

void lamp(double rStand, int hStand, int rJoint, int hJoint, int fsAngle){
    GLUquadricObj* quadObj = gluNewQuadric ();
    gluQuadricDrawStyle (quadObj, GLU_FILL);
    
    //horzontal cylinder - joint
    glTranslated(-2.5, 0, 10);
    glRotated(90, 0, 1, 0);
    glRotated(90, 0, 0, -1);
    glRotated(fsAngle, 0, 0, 1);
    glRotated(lampR2, 0, 1, 0);
    gluCylinder(quadObj, 1, 1, 5,20,10);
    gluDisk(quadObj, 0, 1, 20, 10);//side disk1 (left)
    glTranslated(0, 0, 5);
    gluDisk(quadObj, 0, 1, 20, 10);//side disk2 (right)
    
    //vertical cylinder
    glTranslated(-1, 0, -2.5);
    glRotated(280, 0, 1, 0);
    gluCylinder(quadObj, 0.5, 0.5, 4,20,10);
    
    //lamp base
    glTranslated(0, 0, 1);
    gluCylinder(quadObj, 2, 2, 2,20,10);
    gluDisk(quadObj, 0, 2, 20, 10);//side disk1 (left)
    
    //lamp
    glTranslated(0, 0, 2);
    gluCylinder(quadObj, 2, 4, 4,20,10);
    
    lampLight();
    glMaterialfv(GL_FRONT, GL_EMISSION, RED_LOW);
    gluSphere(quadObj,1.5,20,10);
    glMaterialfv(GL_FRONT, GL_EMISSION, BLACK);
    
    gluDeleteQuadric(quadObj);
}

void drawPixar(){
    GLUquadricObj* quadObj = gluNewQuadric ();
    gluQuadricDrawStyle (quadObj, GLU_FILL);
    
    
    glPushMatrix();
    
    glTranslated(-0.2, 0.55, 0.8);
    glRotatef(90.0f, 100.0f, 0.0f, 0.0f);
    gluCylinder(quadObj, 0.03, 0.03, 0.60, 20, 10);
    
    glRotatef(60.0f, 100.0f, 0.0f, 0.0f);
    gluCylinder(quadObj, 0.03, 0.03, 0.25, 20, 10);
    
    glTranslated(-0.01, 0.3, 0.2);
    glRotatef(80.0f, 100.0f, 0.0f, 0.0f);
    gluCylinder(quadObj, 0.03, 0.03, 0.30, 20, 10);
    
    glPopMatrix();
    
    glPushMatrix();
    
    glTranslated(-0.2, 0.45, -0.1);
    glRotatef(45.0f, 100.0f, 0.0f, 0.0f);
    gluCylinder(quadObj, 0.03, 0.03, 0.6, 20, 10);
    
    glTranslated(0, -0.3, 0.3); 
    glRotatef(-90.0f, 100.0f, 0.0f, 0.0f);
    gluCylinder(quadObj, 0.03, 0.03, 0.6, 20, 10);
    
    glPopMatrix();
    
    glPushMatrix();
    
    glTranslated(-0.2, 0.55, -0.3);
    glRotatef(90.0f, 100.0f, 0.0f, 0.0f);
    gluCylinder(quadObj, 0.03, 0.03, 0.60, 20, 10);
    
    glRotatef(90.0f, 100.0f, 0.0f, 0.0f);
    gluCylinder(quadObj, 0.03, 0.03, 0.20, 20, 10);
    
    glTranslated(0, 0.3, 0);
    gluCylinder(quadObj, 0.03, 0.03, 0.20, 20, 10);
    
    glTranslated(0, 0.3, 0.2);
    glRotatef(90.0f, 100.0f, 0.0f, 0.0f);
    gluCylinder(quadObj, 0.03, 0.03, 0.60, 20, 10);
    
    glPopMatrix();
    
    glPushMatrix();
    
    glTranslated(-0.2, 0.55, -0.7);
    glRotatef(90.0f, 100.0f, 0.0f, 0.0f);
    gluCylinder(quadObj, 0.03, 0.03, 0.60, 20, 10);
    
    glRotatef(60.0f, 100.0f, 0.0f, 0.0f);
    gluCylinder(quadObj, 0.03, 0.03, 0.25, 20, 10);
    
    glTranslated(-0.01, 0.3, 0.2);
    glRotatef(80.0f, 100.0f, 0.0f, 0.0f);
    gluCylinder(quadObj, 0.03, 0.03, 0.30, 20, 10);
    
    glTranslated(0, 0.25, -0.05);
    glRotatef(80.0f, 100.0f, 0.0f, 0.0f);
    gluCylinder(quadObj, 0.03, 0.03, 0.25, 20, 10);
    
    glPopMatrix();
    
    glFlush();
}

