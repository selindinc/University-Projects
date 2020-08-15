#include <GLUT/glut.h> //Max OSX
#include <cstdlib>
#include <stdlib.h>
#include <cmath>
#include <iostream>
using namespace std;

void bresenham(float x1, float y1, float x2, float y2);
void display();
void DisplayWakeOpenGL();
void mid_point(float X1, float Y1, float X2, float Y2);
int setQuadrant(float* x1, float* y1, float* x2, float* y2, float* dx, float* dy, float* absDx, float* absDy);
void convertQuadrant(int whichQuad, float* x, float* y);

void display() {
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
    glPointSize(1.0); // set the thickness
    //float x1, float y1, float x2, float y2
    //W
    bresenham(-450.0, 400.0, -400.0, 450.0);
    bresenham(-450.0, 400.0, -500.0, 450.0);
    bresenham(-400.0, 450.0, -350.0, 400.0);
    bresenham(-350.0, 400.0, -300.0, 450.0);
    //A
    bresenham(-300.0, 400.0, -250.0, 450.0); // /
    bresenham(-250.0, 450.0, -200.0, 400.0); // /
    bresenham(-280.0, 425.0, -220.0, 425.0); // -
    //K
    bresenham(-150.0, 400.0, -150.0, 450.0);
    bresenham(-100.0, 400.0, -150.0, 425.0);
    bresenham(-100.0, 450.0, -150.0, 425.0);
    //E
    bresenham(-50.0, 400.0, -50.0, 455.0);
    bresenham(-50.0, 400.0, 0.0, 400.0);
    bresenham(-50.0, 425.0, 0.0, 425.0);
    bresenham(-50.0, 450.0, 0.0, 450.0);
    
    //DisplayWakeOpenGL
    
    DisplayWakeOpenGL();
    
    //cartesian
    bresenham(0.0, 0.0, 0.0, 300.0); //Y cord.
    bresenham(20.0, 310.0, 20.0, 350.0); //Y
    bresenham(20.0, 350.0, 40.0, 370.0); //Y
    bresenham(20.0, 350.0, 0.0, 370.0); //Y

    
    bresenham(0.0,0.0, 300.0, 0.0);//X cord.
    bresenham(300.0,-20.0, 320.0, -40.0);//X
    bresenham(320.0,-20.0, 300.0, -40.0);//X
    
    bresenham(0.0, 0.0, -150.0, -150.0);//Z cord.
    bresenham(-170.0, -150.0, -200.0, -150.0);//Z
    bresenham(-170.0, -120.0, -200.0, -120.0);//Z
    bresenham(-200.0, -150.0, -170.0, -120.0);//Z

    // 460
    bresenham(100.0, 100.0, 100.0, 200.0);
    bresenham(120.0, 130.0, 50.0, 130.0);
    bresenham(50.0, 130.0, 100.0, 200.0);
    
    bresenham(140.0, 100.0, 200.0, 100.0);
    bresenham(140.0, 120.0, 200.0, 120.0);
    bresenham(140.0, 200.0, 200.0, 200.0);
    bresenham(140.0, 100.0, 140.0, 200.0);
    bresenham(200.0, 100.0, 200.0, 120.0);
    
    bresenham(240.0, 100.0, 280.0, 100.0);
    bresenham(240.0, 100.0, 240.0, 200.0);
    bresenham(280.0, 100.0, 280.0, 200.0);
    bresenham(240.0, 200.0, 280.0, 200.0);
    
    //560
    bresenham(50.0, -25.0, 100.0, -25.0);
    bresenham(50.0, -25.0, 25.0, -50.0);
    bresenham(25.0, -50.0, 90.0, -50.0);
    bresenham(90.0, -50.0, 45.0, -100.0);
    bresenham(45.0, -100.0, 0.0, -100.0);
    
    bresenham(140.0, -25.0, 190.0, -25.0);
    bresenham(140.0, -25.0, 90.0, -100.0);
    bresenham(90.0, -100.0, 150.0, -100.0);
    bresenham(150.0, -100.0, 163.0, -80.0);
    bresenham(163.0, -80.0, 105.0, -80.0);
    
    bresenham(220.0, -25.0, 260.0, -25.0);
    bresenham(220.0, -25.0, 180.0, -100.0);
    bresenham(180.0, -100.0, 220.0, -100.0);
    bresenham(220.0, -100.0, 260.0, -25.0);

    //CS
    bresenham(-150.0, -75.0, -100.0, -30.0);
    bresenham(-150.0, -75.0, -240.0, 0.0);
    bresenham(-240.0, 0.0, -200.0, 40.0);
    
    bresenham(-150.0, 100.0, -100.0, 140.0);
    bresenham(-150.0, 100.0, -90.0, 60.0);
    bresenham(-90.0, 60.0, -55.0, 90.0);
    bresenham(-55.0, 90.0, -20.0, 70.0);
    bresenham(-20.0, 70.0, -60.0, 30.0);
    
    glFlush();
    
    // - - - - - - -
    for(int x1=-450,x2=-430;x1<-100 & x2<-100;x1+=30,x2+=30){
            mid_point(x1,-190,x2,-190);
            glFlush();
    }
    // . . . . . .
    for(int x1=-450; x1<-100;x1+=10){
        mid_point(x1,-210,x1,-210);
        glFlush();
    }
    glPointSize(3.0); // set the thickness
    
    for(int x1=-450,x2=-430;x1<-100 & x2<-100;x1+=30,x2+=30){
        mid_point(x1,-230,x2,-230);
        glFlush();
    }
    glPointSize(2.0); // set the thickness
    for(int x1=-450,x2=-430;x1<-100 & x2<-100;x1+=40,x2+=40){
        mid_point(x1,-250,x2,-250);
        glFlush();
    }
    //- . - .
    glPointSize(1.0); // set the thickness
    
    mid_point(-450,-270,-410,-270);//-
    mid_point(-390,-270,-390,-270);//.
    mid_point(-350,-270,-350,-270);//.
    mid_point(-320,-270,-280,-270);
    mid_point(-260,-270,-260,-270);
    mid_point(-220,-270,-220,-270);
    mid_point(-190,-270,-150,-270);
    mid_point(-130,-270,-130,-270);
    mid_point(-90,-270,-90,-270);
    
    glFlush();
    
}

void DisplayWakeOpenGL(){

    glLineWidth(1.0f);
    glBegin(GL_LINES);
    
    glColor3f(0.0f, 1.0f, 1.0f); // Blue
    
    //float x1, float y1, float x2, float y2);
    //W
    //W
    //500
    glVertex2f(50.0/500, 400.0/500);
    glVertex2f(0.0/500, 450.0/500);
    glVertex2f(50.0/500, 400.0/500);
    glVertex2f(100.0/500, 450.0/500);
    glVertex2f(100.0/500, 450.0/500);
    glVertex2f(150.0/500, 400.0/500);
    glVertex2f(150.0/500, 400.0/500);
    glVertex2f(200.0/500, 450.0/500);
    
    //A
    glVertex2f(200.0/500, 400.0/500);
    glVertex2f(250.0/500, 450.0/500);
    glVertex2f(250.0/500, 450.0/500);
    glVertex2f(300.0/500, 400.0/500);
    glVertex2f(220.0/500, 425.0/500);
    glVertex2f(280.0/500, 425.0/500);
    //K
    glVertex2f(350.0/500, 400.0/500);
    glVertex2f(350.0/500, 450.0/500);
    glVertex2f(400.0/500, 400.0/500);
    glVertex2f (350.0/500, 425.0/500);
    glVertex2f(400.0/500, 450.0/500);
    glVertex2f(350.0/500, 425.0/500);
    //E
    glVertex2f(450.0/500, 400.0/500);
    glVertex2f (450.0/500, 455.0/500);
    glVertex2f(450.0/500, 400.0/500);
    glVertex2f(500.0/500, 400.0/500);
    glVertex2f(450.0/500, 425.0/500);
    glVertex2f(500.0/500, 425.0/500);
    glVertex2f(450.0/500, 450.0/500);
    glVertex2f (500.0/500, 450.0/500);
    
    glEnd();
    
    
    glLineWidth(1.0);
    glEnable(GL_LINE_STIPPLE);
    
    float x1 = 0, y1 = -190.0, x2 = 400.0, y2 = -190.0;
    glLineStipple(1, 0x00FF);
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex2f((x1/500),(y1/500));
    glVertex2f((x2/500),(y2/500));
    glEnd();
    
    x1 = 0.0, y1 = -210.0, x2 = 400.0, y2 = -210.0;
    glLineStipple(2, 0x00FF);
    glBegin(GL_LINES);
    glVertex2f((x1/500),(y1/500));
    glVertex2f((x2/500),(y2/500));
    glEnd();
    
    glLineWidth(2.0);
    x1 = 0.0, y1 = -230.0, x2 = 400.0, y2 = -230.0;
    glLineStipple(2, 0x00FF);
    glBegin(GL_LINES);
    glVertex2f((x1/500),(y1/500));
    glVertex2f((x2/500),(y2/500));
    glEnd();
    
    
    x1 = 0.0, y1 = -250.0, x2 = 400.0, y2 = -250.0;
    glLineStipple(4, 0x0CCF);
    glBegin(GL_LINES);
    glVertex2f((x1/500),(y1/500));
    glVertex2f((x2/500),(y2/500));
    glEnd();
    
    glLineWidth(4.0);
    x1 = 0.0, y1 = -270.0, x2 = 400.0, y2 = -270.0;
    glLineStipple(2, 0x0FFF);
    glBegin(GL_LINES);
    glVertex2f((x1/500),(y1/500));
    glVertex2f((x2/500),(y2/500));
    glEnd();
    
    glDisable(GL_LINE_STIPPLE);
    
    
    
}

int setQuadrant(float* x1, float* y1, float* x2, float* y2, float* dx, float* dy, float* absDx, float* absDy){
    
    int whichQuad=0;
    
    if(*dx>0 && *dy>=0 && *absDx>=*absDy){
        
        whichQuad=1;
        
    } //quadrant I
    
    else if(*dx>=0 && *dy>0 && *absDx<*absDy){
        
        whichQuad=2;
        
        swap(*x1,*y1);
        
        swap(*x2,*y2);
        
        
    } //quadrant II
    
    else if(*dx<0 && *dy>0 && *absDy>*absDx){
        
        whichQuad=3;
        
        *x1=*x1*(-1);
        
        *x2=*x2*(-1);
        
        swap(*x1,*y1);
        
        swap(*x2,*y2);
        
    } //quadrant III
    
    else if(*dx<0 && *dy>0 && *absDx>=*absDy){
        
        whichQuad=4;
        
        *x1=*x1*(-1);
        
        *x2=*x2*(-1);
        
    } //quadrant IV
    
    else if(*dx<0 && *dy<=0 && *absDx>=*absDy){
        
        whichQuad=5;
        
        *y1=*y1*(-1);
        
        *y2=*y2*(-1);
        
        *x1=*x1*(-1);
        
        *x2=*x2*(-1);
        
    } //quadrant V
    
    else if(*dx<=0 && *dy<0 && *absDy>*absDx){
        
        whichQuad=6;
        
        *y1=*y1*(-1);
        
        *y2=*y2*(-1);
        
        *x1=*x1*(-1);
        
        *x2=*x2*(-1);
        
        swap(*x1,*y1);
        
        swap(*x2,*y2);
        
    } //quadrant VI
    
    else if(*dx>0 && *dy<0 && *absDy>*absDx){
        
        whichQuad=7;
        
        *y1=*y1*(-1);
        
        *y2=*y2*(-1);
        
        swap(*x1,*y1);
        
        swap(*x2,*y2);
    } //quadrant VII
    
    else if(*dx>0 && *dy<0 && *absDx>=*absDy){
        
        whichQuad=8;
        
        *y1=*y1*(-1);
        
        *y2=*y2*(-1);
        
    } //quadrant VIII
    
    return whichQuad;
}

void convertQuadrant(int whichQuad, float* x, float* y){
    
    if(whichQuad==1){
        
        glVertex2f(*x/500,*y/500);
    }
    if(whichQuad==2){

        glVertex2f(*y/500,*x/500);
    }
    else if(whichQuad==3){
        
        glVertex2f(-*y/500,*x/500);
    }
    else if(whichQuad==4){
        
        glVertex2f(-*x/500,*y/500);
    }
    else if(whichQuad==5){
        
        glVertex2f(-*x/500,-*y/500);
    }
    else if(whichQuad==6){
        
        glVertex2f(-*y/500,-*x/500);
    }
    else if(whichQuad==7){
        
        glVertex2f(*y/500,-*x/500);
    }
    else if(whichQuad==8){
        
        glVertex2f(*x/500,-*y/500);
    }
}
void mid_point(float x1, float y1, float x2, float y2){
    
    // calculate dx & dy
    float dx = x2 - x1;
    float dy = y2 - y1;
    
    float absDx=abs(dx);
    float absDy=abs(dy);
    int whichQuad=0;
    
    whichQuad = setQuadrant(&x1, &y1, &x2, &y2, &dx, &dy, &absDx, &absDy);
    
    float ddx=x2-x1;
    float ddy=y2-y1;
    
    float d = dy - (dx/2);
    float x = x1, y = y1;
    
    glBegin(GL_POINTS);
    glColor3f(0.0f, 1.0f, 1.0f); // Blue
    glVertex2f(x/500,y/500);
    glEnd();
    
    for (x = x1; x< x2; x++){
    
        glBegin(GL_POINTS);
        glColor3f(0.0f, 1.0f, 1.0f); // Blue
        convertQuadrant(whichQuad, &x, &y);
        
        // E or East is chosen
        if (d < 0){
            d = d + ddy;
        }
        // NE or North East is chosen
        else
        {
            d += (ddy - ddx);
            y++;
        }
        
        glVertex2f(x/500,y/500);
        glEnd();
        
    }
}

void bresenham(float x1, float y1, float x2, float y2) {
    
    float dx = x2-x1;
    float dy = y2-y1;
    float absDx=abs(dx);
    float absDy=abs(dy);
    int whichQuad=0;
    
    whichQuad = setQuadrant(&x1, &y1, &x2, &y2, &dx, &dy, &absDx, &absDy);
    
    float ddx=x2-x1;
    float ddy=y2-y1;
    float error= 2*ddy-ddx;
    float deltaD1 = 2*ddy;
    float deltaD2 = 2*(ddy-ddx);
    float y = y1;
    
    for (float x = x1; x< x2; x++){

        glBegin(GL_POINTS);

        glColor3f(1.0f, 0.0f, 0.0f); // Red

        convertQuadrant(whichQuad, &x, &y);

        if (error < 0){

            error = error + deltaD1;
        }
        else{
            error = error + deltaD2;
            y = y + 1;
        }
        glEnd();
    }
}


int main(int argc, char** argv) {
 
    glutInit(&argc, argv);                 // Initialize GLUT
    glutCreateWindow("Hello CS460/560"); // Create a window with the given title
    glutInitWindowSize(500, 500);   // Set the window's initial width & height
    glutInitWindowPosition(200, 200); // Position the window's initial top-left corner
    glutDisplayFunc(display); // Register display callback handler for window re-paint
    glutMainLoop();           // Enter the event-processing loop
    return 0;
}



