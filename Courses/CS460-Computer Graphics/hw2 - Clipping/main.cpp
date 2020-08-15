//  main.cpp
//  hw2
//
//  Created by Selin Dinc on 1.03.2020.
//  Copyright © 2020 Selin Dinc. All rights reserved.
//
#include <GLUT/glut.h>//Max OSX
#include <cstdlib>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

struct Line{
    float mx1,my1,mx2,my2;
};

struct Point {
    float px,py;
};

void DrawWindow();
void ClipPolygon();
void FillRegion();
float x_intersect(Line polygon, Point point1,Point point2);
float y_intersect(Line polygon,Point point1,Point point2);
void suthHodgClip();
void DrawViewPort();
void WindowToViewMapCalc(Line line);
void motionForViewPortAndWindow(int x, int y);
void motion(int x, int y);


vector<Line> clipperWindowLines; //clipper
vector<Line> lines; //polygon
vector<Point> polygon_points; //polygon
vector<Line> viewPortLines;

bool clickR=false;
bool clickL=false;
bool clickWindow=false;
bool clickViewPort=false;
bool moveWindow=false;
float sdx;
float sdy;
float xwmin =100, xwmax=600, ywmin=100, ywmax=600;
float xvmin=650, xvmax=850, yvmin=50, yvmax=250;
float holdVertical , holdHorizontal;

void display(void)
{
    
    glColor3f(1.0, 0.0, 0.0);
    DrawWindow();
    DrawViewPort();
    
    glBegin(GL_LINES);
    glLineWidth(2.0f);
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    for(int i=0; i<lines.size(); i++){
        glVertex2f(lines.at(i).mx1,lines.at(i).my1);
        glVertex2f(lines.at(i).mx2,lines.at(i).my2);
    }
    glEnd();
    
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    for(int i=0; i<viewPortLines.size(); i++){
        glVertex2f(viewPortLines.at(i).mx1, viewPortLines.at(i).my1);
        glVertex2f(viewPortLines.at(i).mx2, viewPortLines.at(i).my2);
    }
    glEnd();
    glFlush();
    
}
void boundaryFill4(float x, float y){
    float pixel_buffer[ 3 ];
    
    glReadPixels( x, 1000-y, 1, 1, GL_RGB, GL_FLOAT, &pixel_buffer );
    
    if((pixel_buffer[0] == 1.0 && pixel_buffer[1] == 0.0 && pixel_buffer[2] == 0.0)||(pixel_buffer[0] == 0.0 && pixel_buffer[1] == 1.0 && pixel_buffer[2] == 1.0)){
        cout<<"red"<<endl;
        return;
    }
    else if(!(pixel_buffer[0] == 1.0 && pixel_buffer[1] == 0.0 && pixel_buffer[2] == 0.0) || !(pixel_buffer[0] == 0.0 && pixel_buffer[1] == 1.0 && pixel_buffer[2] == 1.0)){
        
        glBegin(GL_POINTS);
        glColor3f(0.0f, 1.0f, 1.0f); // Blue
        glVertex2f(x,y);
        glEnd();
        glFlush();
        glReadPixels( x, y, 1, 1, GL_RGB, GL_FLOAT, &pixel_buffer );
        //cout<<pixel_buffer[0]<<" "<<pixel_buffer[1]<<" "<<pixel_buffer[2]<<endl;
        boundaryFill4(x+1, y);
        boundaryFill4(x-1, y);
        boundaryFill4(x, y+1);
        boundaryFill4(x, y-1);
        
    }
}

void polygonFill(float x, float y){
    
    boundaryFill4(x,  y);
    glFlush();
    
}

void clip(int whichSideInWindow){
    
    int polygon_size=polygon_points.size();
    vector<Point> new_points;
    new_points.clear();
    
    
    float wx1=clipperWindowLines[whichSideInWindow].mx1;
    float wy1=clipperWindowLines[whichSideInWindow].my1;
    float wx2=clipperWindowLines[whichSideInWindow].mx2;
    float wy2=clipperWindowLines[whichSideInWindow].my2;
    
    cout<<"p size "<<polygon_size<<endl;
    
    for (int i = 0; i < polygon_size; i++)
    {
       
        // i and k form a line in polygon
        int k = (i+1);
        if(k==polygon_size){k=0;}
        Point p;
        
        
        float ix = polygon_points.at(i).px;
        float iy = polygon_points.at(i).py;
        float kx = polygon_points.at(k).px;
        float ky = polygon_points.at(k).py;
        
        
        float i_pos = (wx2-wx1) * (iy-wy1) - (wy2-wy1) * (ix-wx1);
        float k_pos = (wx2-wx1) * (ky-wy1) - (wy2-wy1) * (kx-wx1);
        
        if (i_pos <= 0  && k_pos <= 0) { //in-in - only add the second point
            
            
            p.px=kx;
            p.py=ky;
            new_points.push_back(p);
            
        }
        else if (i_pos > 0  && k_pos <= 0){ //out-in
            Point p1,p2;
            
            
            p1.px=ix;
            p1.py=iy;
            p2.px=kx;
            p2.py=ky;
            
            p.px = x_intersect(clipperWindowLines[whichSideInWindow],p1,p2);
            p.py = y_intersect(clipperWindowLines[whichSideInWindow],p1,p2);
            new_points.push_back(p);
            
            Point pp;
            pp.px=kx;
            pp.py=ky;
            new_points.push_back(pp);
            
        }
        else if (i_pos <= 0  && k_pos > 0){ //in-out
            Point p1,p2;
            
            p1.px=ix;
            p1.py=iy;
            p2.px=kx;
            p2.py=ky;
            
            p.px = x_intersect(clipperWindowLines[whichSideInWindow],p1,p2);
            p.py = y_intersect(clipperWindowLines[whichSideInWindow],p1,p2);
            new_points.push_back(p);
            
            
        }
        else{}
        
    }
    polygon_points.clear();
    for (int i = 0; i < new_points.size(); i++)
    {
        polygon_points.push_back(new_points.at(i));
    }
}
void suthHodgClip(){
    
    for(int i=0;i<lines.size();i++){
        
        Point p1;
        Point p2;
        p1.px=lines.at(i).mx1;
        p1.py=lines.at(i).my1;
        p2.px=lines.at(i).mx2;
        p2.py=lines.at(i).my2;
        polygon_points.push_back(p1);
    }
    
    for (int j=0; j<4; j++){
        clip(j);
    }
    lines.clear();
    for(int s=0;s<polygon_points.size();s++)
    {
        
        Line line;
        int d = (s+1);
        if(d==polygon_points.size()){d=0;}
        
        line.mx1=polygon_points[s].px;
        line.my1=polygon_points[s].py;
        line.mx2=polygon_points[d].px;
        line.my2=polygon_points[d].py;
        lines.push_back(line);
        
    }
    polygon_points.clear();
}

void DrawWindow(){
    
    glEnable(GL_LINE_STIPPLE);
    
    glLineWidth(1.0f);
    
    
    glLineStipple(1, 0x00FF);
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 1.0f); // Blue
    
    glBegin(GL_LINE_LOOP);
    glVertex2f(xwmin, ywmax);//left2
    glVertex2f(xwmin, ywmin);//left1
    
    
    glVertex2f(xwmax, ywmin);//right2
    glVertex2f(xwmax, ywmax);//right1
    
    
    glVertex2f(xwmax, ywmax);//bottom1
    glVertex2f(xwmin, ywmax);//bottom2
    
    
    glVertex2f(xwmin, ywmin);//top2
    glVertex2f(xwmax, ywmin);//top1
    
    
    glEnd();
    
    glDisable(GL_LINE_STIPPLE);
}
void DrawViewPort(){
    
    glEnable(GL_LINE_STIPPLE);
    glLineWidth(1.0f);
    
    glLineStipple(1, 0x00FF);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    
    glBegin(GL_LINE_LOOP);
    glVertex2f(xvmin, yvmax);//left2
    glVertex2f(xvmin, yvmin);//left1
    
    
    glVertex2f(xvmax, yvmin);//right2
    glVertex2f(xvmax, yvmax);//right1
    
    
    glVertex2f(xvmax, yvmax);//bottom1
    glVertex2f(xvmin, yvmax);//bottom2
    
    
    glVertex2f(xvmin, yvmin);//top2
    glVertex2f(xvmax, yvmin);//top1
    
    
    glEnd();
    
    glDisable(GL_LINE_STIPPLE);
}

void WindowToViewMapCalc(Line line){
    Line viewLine;
    viewLine.mx1=(line.mx1-xwmin)*(xvmax-xvmin)/(xwmax-xwmin)+xvmin;
    viewLine.mx2=(line.mx2-xwmin)*(xvmax -xvmin)/(xwmax - xwmin) +xvmin;
    viewLine.my1=(line.my1-ywmin)*(yvmax -yvmin)/(ywmax - ywmin) +yvmin;
    viewLine.my2=(line.my2-ywmin)*(yvmax -yvmin)/(ywmax - ywmin) +yvmin;
    viewPortLines.push_back(viewLine);
    
}

void WindowToViewMap(){
    viewPortLines.clear();
    for(int i=0;i<lines.size();i++){
        WindowToViewMapCalc(lines.at(i));
    }
}

float x_intersect(Line polygon, Point point1,Point point2){
    float x1, y1, x2, y2, x3, y3, x4, y4;
    x1= polygon.mx1;
    y1= polygon.my1;
    x2=polygon.mx2;
    y2=polygon.my2;
    
    x3= point1.px;
    y3=point1.py;
    x4= point2.px;
    y4= point2.py;
    
    float num = (x1*y2 - y1*x2) * (x3-x4) - (x1-x2) * (x3*y4 - y3*x4);
    float den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    return num/den;
}

float y_intersect(Line polygon,Point point1,Point point2){
    float x1, y1, x2, y2, x3, y3, x4, y4;
    x1= polygon.mx1;
    y1= polygon.my1;
    x2=polygon.mx2;
    y2=polygon.my2;
    
    x3= point1.px;
    y3=point1.py;
    x4= point2.px;
    y4= point2.py;
    
    float num = (x1*y2 - y1*x2) * (y3-y4) - (y1-y2) * (x3*y4 - y3*x4);
    float den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    return num/den;
}

void mouse(int button, int state, int x, int y) {
    
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if(x>=xvmax-30 && x<= xvmax+30 && y >= yvmax-30 && y<=yvmax +30){
            clickViewPort=true;
            clickWindow=false;
            moveWindow=false;
        }
        else if (x>=xwmax-30 && x<= xwmax+30 && y >= ywmax-30 && y<=ywmax +30){
            clickWindow=true;
            clickViewPort=false;
            moveWindow=false;
        }
        else if(x>=xwmin-30 && x<= xwmax+30 && y >= ywmax-30 && y<=ywmax +30){
            moveWindow=true;
            
            holdVertical=y;
            holdHorizontal=x;
        }
        else{
            glutDetachMenu(GLUT_RIGHT_BUTTON);
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
            clickViewPort=false;
            clickWindow=false;
            moveWindow=false;
            
        }
    }
    
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        lines.at(lines.size()-1).mx2 = x;
        lines.at(lines.size()-1).my2 = y;
        clickR = true;
        clickL =false;
        clickWindow=false;
        clickViewPort=false;
        glutAttachMenu(GLUT_RIGHT_BUTTON);
        
    }
}

void motion(int x, int y) {
    if(clickL){
        lines.at(lines.size()-1).mx2 = x;
        lines.at(lines.size()-1).my2 = y;
        
        glutPostRedisplay();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        
    }
    sdx=x;
    sdy=y;
}

void motionForViewPortAndWindow(int x, int y){
    if(clickViewPort){
        xvmax=x;
        yvmax=y;
        WindowToViewMap();
        glutPostRedisplay();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }
    else if(clickWindow){
        xwmax=x;
        ywmax=y;
        WindowToViewMap();
        glutPostRedisplay();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }
    else if(moveWindow){
        float len=x-holdHorizontal;
        holdHorizontal=holdHorizontal+len;
        xwmax=xwmax+len;
        xwmin=xwmin+len;
        
        len=y-holdVertical;
        holdVertical=holdVertical+len;
        ywmax=ywmax+len;
        ywmin=ywmin+len;
        WindowToViewMap();
        glutPostRedisplay();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        
    }
    
}


void menu(int value)
{
    
    switch(value) {
        case 1:
            suthHodgClip();
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            break;
        case 2:
            polygonFill(sdx,sdy);
            break;
        case 3:
            WindowToViewMap();
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            break;
            
    }
    glutPostRedisplay();
}

void make_menu(void)
{
    /*MainMenu*/
    // main_menu
    glutCreateMenu(menu);
    glutAddMenuEntry("Polygon Clipping", 1);
    glutAddMenuEntry("Region Filling", 2);
    glutAddMenuEntry("Window-to-Viewport Mapping", 3);
    
}
void init(){
    gluOrtho2D(0.0, 1000.0, 1000.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

int main(int argc, char ** argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("HW2");
    
    init();
    
    Line line;
    line.mx1 = 100;
    line.my1 = 100;
    line.mx2 = 100;
    line.my2 = 600;
    clipperWindowLines.push_back(line);//window left
    
    
    Line line1;
    line1.mx1 = 600;
    line1.my1 = 600;
    line1.mx2 = 600;
    line1.my2 = 100;
    clipperWindowLines.push_back(line1);//window right
    
    
    Line line2;
    line2.mx1 = 100;
    line2.my1 = 600;
    line2.mx2 = 600;
    line2.my2 = 600;
    clipperWindowLines.push_back(line2);//window bottom
    
    Line line3;
    line3.mx1 = 600;
    line3.my1 = 100;
    line3.mx2 = 100;
    line3.my2 = 100;
    clipperWindowLines.push_back(line3);//window top
    
    
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(motion);
    glutMotionFunc(motionForViewPortAndWindow);
    make_menu();
    glutMainLoop();
    
    return 0;
}

