#define GL_SILENCE_DEPRECATION
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<math.h>
#include<GLUT/glut.h>
#include<vector>
#include<assert.h>
#include"triangle.hpp"

using namespace std;


bool flat = false;
bool smooth = false;
bool DiffusePlus = false;
bool DiffuseMinus = false;
bool SpecularPlus = false;
bool SpecularMinus = false;
bool ShininessPlus = false;
bool ShininessMinus = false;


bool render_type = true;

bool cp1=false;bool cp2=false;bool cp3=false;bool cp4=false;bool cp5=false;bool cp6=false;bool cp7=false;bool cp8=false;bool cp9=false;bool cp10=false;
bool cp11=false;bool cp12=false;bool cp13=false;bool cp14=false;bool cp15=false;bool cp16=false;


int WIDTH_WINDOWS;
int HEIGHT_WINDOWS;

double m_slide=100;

bool bezierSurface = true;


// lighting parameters.
bool flatShading = false;
bool bezierSurfaceMapping = false;
bool bezierSurfaceLighting = false;
float lightx = 10, lighty = 15, lightz = 10;
// data for the lighting
//
// for x-y-z axis
GLfloat redSurface[]   = {1.0, 0.0, 0.0, 1.0};
GLfloat greenSurface[]   = {0.0, 1.0, 0.0, 1.0};
GLfloat blueSurface[]   = {0.0, 0.0, 1.0, 1.0};
GLfloat darkSurface[]   = {1.0, 0.0, 0.0, 1.0};
GLfloat whiteSurface[]= {1.0, 1.0, 1.0, 1.0};
//for lighting
GLfloat lightAmbient[] =  {0.1, 0.1, 0.1, 1.0};
GLfloat lightDiffuse[] =  {0.7, 0.7, 0.7, 1.0};
GLfloat lightSpecular[] = {0.4, 0.4, 0.4, 1.0};
GLfloat lightPosition[] = {-lightx, -lighty, -lightz, 0.0}; //{100.0, 100.0, 100.0, 0.0};
GLfloat lightDirection[] ={0.0, 0.0, -1.0};
GLfloat shininess[] = {50.0};
// for the materials
GLfloat matAmbient [] = {0.0, 1.0, 0.0, 1.0};
GLfloat matDiffuse [] = {0.0, 1.0, 0.0, 1.0};
GLfloat matSpecular[] = {1.0, 1.0, 1.0, 1.0};

void projection(int width, int height, int perspectiveORortho){
    float ratio = (float)width/height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (perspectiveORortho)
        gluPerspective(60, ratio, 1, 1000);
    else
        glOrtho(-ratio, ratio, -ratio, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void reshape( int w, int h ){
    glViewport( 0, 0, (GLsizei)w, (GLsizei)h ); // set to size of window
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    
    glOrtho( 0, w, h, 0, -1, 1 );
    WIDTH_WINDOWS = w;  // records width globally
    HEIGHT_WINDOWS = h; // records height globally
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void draw_axis(){
    glColor3f(1,1,1);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex3f(-100, 0, 0);
    glVertex3f(100, 0, 0);
    glVertex3f(0, -100, 0);
    glVertex3f(0, 100, 0);
    glVertex3f(0, 0, -100);
    glVertex3f(0, 0, 100);
    glEnd();
}

void draw_controls(){
    glPointSize(20);
    glBegin(GL_POINTS);
    glColor3f(35, 0, 200);
    for (int i = 0; i < controls.size(); ++i) {
        for (int j = 0; j < controls[0].size(); ++j) {
            
            
            glVertex3f(controls[i][j].x, controls[i][j].y+1, controls[i][j].z);
        }
    }
    glEnd();
    glPointSize(1);
}


void make_triangles(){
    for(int i = 0; i < points.size()-1; i++){
        for(int j = 0; j < points[0].size()-1; j++){
            triangles.push_back(Triangle(points[i][j], points[i][j+1], points[i+1][j]));
            triangles.push_back(Triangle(points[i+1][j], points[i][j+1], points[i+1][j+1]));
        }
    }
    calculate_normals();
}

void draw_triangles(){
    Vec3f v = Vec3f(camx, camy, 25);
    
    for(auto t: triangles){
        if(!render_type)
            glBegin(GL_TRIANGLES);
        else{
            glBegin(GL_LINE_LOOP);
            glColor3f(1,1,1);
        }
        Vec3f n = normal(t);
        if(dot(v, n) > 0 && render_type == 0)
            continue;
        Vec3f p1 = normal_avg(t.a);
        Vec3f p2 = normal_avg(t.b);
        Vec3f p3 = normal_avg(t.c);
        glNormal3f(p1.x, p1.y, p1.z);
        glVertex3f(t.a.x, t.a.y, t.a.z);
        
        glNormal3f(p2.x, p2.y, p2.z);
        glVertex3f(t.b.x, t.b.y, t.b.z);
        
        glNormal3f(p3.x, p3.y, p3.z);
        glVertex3f(t.c.x, t.c.y, t.c.z);
        glEnd();
    }
}

Vec3f BezierCurve(array<Vec3f, 4> p, float u){
    Vec3f ret;
    float b1 = pow(1-u, 3);
    float b2 = 3*u*pow(1-u, 2);
    float b3 = 3*pow(u, 2)*(1-u);
    float b4 = pow(u, 3);
    ret.x += b1*p[0].x + b2*p[1].x + b3*p[2].x + b4*p[3].x;
    ret.y += b1*p[0].y + b2*p[1].y + b3*p[2].y + b4*p[3].y;
    ret.z += b1*p[0].z + b2*p[1].z + b3*p[2].z + b4*p[3].z;
    return ret;
}

Vec3f DrawBezierSurface(float u, float v){
    array<Vec3f, 4> curves;
    for(int i = 0; i < 4; i++){
        curves[i] = BezierCurve(controls[i], u);
    }
    return BezierCurve(curves, v);
}

void CalculateBezier(){
    for (int i = 0; i < points.size(); ++i) {
        for (int j = 0; j < points[0].size(); ++j) {
            float div = (points.size()-1);
            points[i][j] =
            DrawBezierSurface((float)i/div, (float)j/div);
        }
    }
}

void display(){
    // glClear(GL_COLOR_BUFFER_BIT); // clear window
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f );
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT );
    glEnable(GL_DEPTH_TEST);
    
    glLoadIdentity();
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 500000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    
    if(bezierSurface){
        //set gluLookAt and gluPerspective
        projection(WIDTH_WINDOWS, HEIGHT_WINDOWS, 1); // set projection.
        gluLookAt(camx,camy,25,0,0,0,0,1,0);
        
        if(bezierSurfaceMapping || bezierSurfaceLighting){
            // lighting
            
            glMaterialfv(GL_FRONT, GL_AMBIENT, greenSurface);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, greenSurface);
            glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSurface);
            glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
            
            
            if(flatShading){
                glShadeModel(GL_FLAT);
            }
            else {
                glShadeModel(GL_SMOOTH);
            }
            
            glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
            glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
            glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
            glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDirection);
            
            
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            glEnable(GL_DEPTH_TEST);
            //flat shading or smooth shading
        }
        
        CalculateBezier();
        triangles.clear();
        make_triangles();
        draw_triangles();
        glDisable(GL_LIGHTING);
        glColor3f(1,1,1);
        draw_axis();
        draw_controls();
    }
    glutSwapBuffers(); // display newly drawn image in window
}

void SubMenuItemClicked(int Value){
    
    switch(Value) {
            
        case 1:
            cp1=true; cp2=false;cp3=false;cp4=false;cp5=false;cp6=false;cp7=false;cp8=false;cp9=false;cp10=false;cp11=false;
            cp12=false;cp13=false;cp14=false;cp15=false;cp16=false;
            break;
            
        case 2:
            cp1=false; cp2=true;cp3=false;cp4=false;cp5=false;cp6=false;cp7=false;cp8=false;cp9=false;cp10=false;cp11=false;
            cp12=false;cp13=false;cp14=false;cp15=false;cp16=false;
            break;
        case 3:
            cp1=false; cp2=false;cp3=true;cp4=false;cp5=false;cp6=false;cp7=false;cp8=false;cp9=false;cp10=false;cp11=false;
            cp12=false;cp13=false;cp14=false;cp15=false;cp16=false;
            break;
        case 4:
            cp1=false; cp2=false;cp3=false;cp4=true;cp5=false;cp6=false;cp7=false;cp8=false;cp9=false;cp10=false;cp11=false;
            cp12=false;cp13=false;cp14=false;cp15=false;cp16=false;
            break;
        case 5:
            cp1=false; cp2=false;cp3=false;cp4=false;cp5=true;cp6=false;cp7=false;cp8=false;cp9=false;cp10=false;cp11=false;
            cp12=false;cp13=false;cp14=false;cp15=false;cp16=false;
            break;
        case 6:
            cp1=false; cp2=false;cp3=false;cp4=false;cp5=false;cp6=true;cp7=false;cp8=false;cp9=false;cp10=false;cp11=false;
            cp12=false;cp13=false;cp14=false;cp15=false;cp16=false;
            break;
        case 7:
            cp1=false; cp2=false;cp3=false;cp4=false;cp5=false;cp6=false;cp7=true;cp8=false;cp9=false;cp10=false;cp11=false;
            cp12=false;cp13=false;cp14=false;cp15=false;cp16=false;
            break;
        case 8:
            cp1=false; cp2=false;cp3=false;cp4=false;cp5=false;cp6=false;cp7=false;cp8=true;cp9=false;cp10=false;cp11=false;
            cp12=false;cp13=false;cp14=false;cp15=false;cp16=false;
            break;
        case 9:
            cp1=false; cp2=false;cp3=false;cp4=false;cp5=false;cp6=false;cp7=false;cp8=false;cp9=true;cp10=false;cp11=false;
            cp12=false;cp13=false;cp14=false;cp15=false;cp16=false;
            break;
        case 10:
            cp1=false; cp2=false;cp3=false;cp4=false;cp5=false;cp6=false;cp7=false;cp8=false;cp9=false;cp10=true;cp11=false;
            cp12=false;cp13=false;cp14=false;cp15=false;cp16=false;
            break;
        case 11:
            cp1=false; cp2=false;cp3=false;cp4=false;cp5=false;cp6=false;cp7=false;cp8=false;cp9=false;cp10=false;cp11=true;
            cp12=false;cp13=false;cp14=false;cp15=false;cp16=false;
            break;
        case 12:
            cp1=false; cp2=false;cp3=false;cp4=false;cp5=false;cp6=false;cp7=false;cp8=false;cp9=false;cp10=false;cp11=false;
            cp12=true;cp13=false;cp14=false;cp15=false;cp16=false;
            break;
        case 13:
            cp1=false; cp2=false;cp3=false;cp4=false;cp5=false;cp6=false;cp7=false;cp8=false;cp9=false;cp10=false;cp11=false;
            cp12=false;cp13=true;cp14=false;cp15=false;cp16=false;
            break;
        case 14:
            cp1=false; cp2=false;cp3=false;cp4=false;cp5=false;cp6=false;cp7=false;cp8=false;cp9=false;cp10=false;cp11=false;
            cp12=false;cp13=false;cp14=true;cp15=false;cp16=false;
            break;
        case 15:
            cp1=false; cp2=false;cp3=false;cp4=false;cp5=false;cp6=false;cp7=false;cp8=false;cp9=false;cp10=false;cp11=false;
            cp12=false;cp13=false;cp14=false;cp15=true;cp16=false;
            break;
        case 16:
            cp1=false; cp2=false;cp3=false;cp4=false;cp5=false;cp6=false;cp7=false;cp8=false;cp9=false;cp10=false;cp11=false;
            cp12=false;cp13=false;cp14=false;cp15=false;cp16=true;
            break;
            
    }
    //glutPostRedisplay();
}

void SubMenuItemClicked2(int Value){
    
    switch(Value) {
         case 1:
            DiffusePlus = true;
            DiffuseMinus = false;
            SpecularPlus = false;
            SpecularMinus = false;
            ShininessPlus = false;
            ShininessMinus = false;
            break;
            
        case 2:
            DiffusePlus = false;
            DiffuseMinus = true;
            SpecularPlus = false;
            SpecularMinus = false;
            ShininessPlus = false;
            ShininessMinus = false;
            break;
        case 3:
            DiffusePlus = false;
            DiffuseMinus = false;
            SpecularPlus = true;
            SpecularMinus = false;
            ShininessPlus = false;
            ShininessMinus = false;
            break;
        case 4:
            DiffusePlus = false;
            DiffuseMinus = false;
            SpecularPlus = false;
            SpecularMinus = true;
            ShininessPlus = false;
            ShininessMinus = false;
            break;
        case 5:
            DiffusePlus = false;
            DiffuseMinus = false;
            SpecularPlus = false;
            SpecularMinus = false;
            ShininessPlus = true;
            ShininessMinus = false;
            break;
        case 6:
            DiffusePlus = false;
            DiffuseMinus = false;
            SpecularPlus = false;
            SpecularMinus = false;
            ShininessPlus = false;
            ShininessMinus = true;
            break;
            
    }
    
    
    
    
}
void MenuItemClicked(int Value){
    switch(Value)
    {
        case 1:
            bezierSurface=true;
            bezierSurfaceMapping=true;
            bezierSurfaceLighting=true;
            flatShading = false;
            DiffusePlus = false;
            DiffuseMinus = false;
            SpecularPlus = false;
            SpecularMinus = false;
            ShininessPlus = false;
            ShininessMinus = false;
            render_type=false;
            break;
        case 2:
            flatShading=false;
            bezierSurface=true;
            bezierSurfaceMapping=true;
            bezierSurfaceLighting=true;
            DiffusePlus = false;
            DiffuseMinus = false;
            SpecularPlus = false;
            SpecularMinus = false;
            ShininessPlus = false;
            ShininessMinus = false;
            render_type=false;
            break;
    }
    glutPostRedisplay();
}

void CreateMenu(){
    int sub_menu1;
    
    sub_menu1=glutCreateMenu(SubMenuItemClicked);
    glutAddMenuEntry("Control Point 1",  1);
    glutAddMenuEntry("Control Point 2",  2);
    glutAddMenuEntry("Control Point 3", 3);
    glutAddMenuEntry("Control Point 4", 4);
    glutAddMenuEntry("Control Point 5", 5);
    glutAddMenuEntry("Control Point 6", 6);
    glutAddMenuEntry("Control Point 7", 7);
    glutAddMenuEntry("Control Point 8", 8);
    glutAddMenuEntry("Control Point 9", 9);
    glutAddMenuEntry("Control Point 10", 10);
    glutAddMenuEntry("Control Point 11", 11);
    glutAddMenuEntry("Control Point 12", 12);
    glutAddMenuEntry("Control Point 13", 13);
    glutAddMenuEntry("Control Point 14", 14);
    glutAddMenuEntry("Control Point 15", 15);
    glutAddMenuEntry("Control Point 16", 16);
    
    int sub_menu2 = glutCreateMenu(SubMenuItemClicked2);
    glutAddMenuEntry("Diffuse+,Press T", 1);
    glutAddMenuEntry("Diffuse-,Press G", 2);
    glutAddMenuEntry("Specular+,Press F", 3);
    glutAddMenuEntry("Specular-,Press H", 4);
    glutAddMenuEntry("Shininess+,Press Z", 5);
    glutAddMenuEntry("Shininess-,Press X", 6);
    
    glutCreateMenu(MenuItemClicked);
    glutAddSubMenu("Bezier Patch-Select Control Point then Use Up-Down-Left-Right-W-S Keys to Move", sub_menu1);
    glutAddMenuEntry("Flat",  1);
    glutAddMenuEntry("Smooth",  2);
    glutAddSubMenu("Adjust", sub_menu2);
    
    //Attach Menu to RightClick
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void specialKey(int key, int x, int y){
    switch(key){
        case GLUT_KEY_UP:
            
            if(cp1){
                controls[0][0].y +=0.3;
            }
            else if(cp2){
                controls[0][1].y +=0.3;
            }
            else if(cp3){
                controls[0][2].y +=0.3;
            }
            else if(cp4){
                controls[0][3].y +=0.3;
            }
            else if(cp5){
                controls[1][0].y +=0.3;
            }
            else if(cp6){
                controls[1][1].y +=0.3;
            }
            else if(cp7){
                controls[1][2].y +=0.3;
            }
            else if(cp8){
                controls[1][3].y +=0.3;
            }
            else if(cp9){
                controls[2][0].y +=0.3;
            }
            else if(cp10){
                controls[2][1].y +=0.3;
            }
            else if(cp11){
                controls[2][2].y +=0.3;
            }
            else if(cp12){
                controls[2][3].y +=0.3;
            }
            else if(cp13){
                controls[3][0].y +=0.3;
            }
            else if(cp14){
                controls[3][1].y +=0.3;
            }
            else if(cp15){
                controls[3][2].y +=0.3;
            }
            else if(cp16){
                controls[3][3].y +=0.3;
            }
            
            break;
        case GLUT_KEY_DOWN:
            if(cp1){
                controls[0][0].y -=0.3;
            }
            else if(cp2){
                controls[0][1].y -=0.3;
            }
            else if(cp3){
                controls[0][2].y -=0.3;
            }
            else if(cp4){
                controls[0][3].y -=0.3;
            }
            else if(cp5){
                controls[1][0].y -=0.3;
            }
            else if(cp6){
                controls[1][1].y -=0.3;
            }
            else if(cp7){
                controls[1][2].y -=0.3;
            }
            else if(cp8){
                controls[1][3].y -=0.3;
            }
            else if(cp9){
                controls[2][0].y -=0.3;
            }
            else if(cp10){
                controls[2][1].y -=0.3;
            }
            else if(cp11){
                controls[2][2].y -=0.3;
            }
            else if(cp12){
                controls[2][3].y -=0.3;
            }
            else if(cp13){
                controls[3][0].y -=0.3;
            }
            else if(cp14){
                controls[3][1].y -=0.3;
            }
            else if(cp15){
                controls[3][2].y -=0.3;
            }
            else if(cp16){
                controls[3][3].y -=0.3;
            }
            
            break;
        case GLUT_KEY_RIGHT:
            if(cp1){
                controls[0][0].x +=0.3;
            }
            else if(cp2){
                controls[0][1].x +=0.3;
            }
            else if(cp3){
                controls[0][2].x +=0.3;
            }
            else if(cp4){
                controls[0][3].x +=0.3;
            }
            else if(cp5){
                controls[1][0].x +=0.3;
            }
            else if(cp6){
                controls[1][1].x +=0.3;
            }
            else if(cp7){
                controls[1][2].x +=0.3;
            }
            else if(cp8){
                controls[1][3].x +=0.3;
            }
            else if(cp9){
                controls[2][0].x +=0.3;
            }
            else if(cp10){
                controls[2][1].x +=0.3;
            }
            else if(cp11){
                controls[2][2].x +=0.3;
            }
            else if(cp12){
                controls[2][3].x +=0.3;
            }
            else if(cp13){
                controls[3][0].x +=0.3;
            }
            else if(cp14){
                controls[3][1].x +=0.3;
            }
            else if(cp15){
                controls[3][2].x +=0.3;
            }
            else if(cp16){
                controls[3][3].x +=0.3;
            }
            
            break;
        case GLUT_KEY_LEFT:
            
            if(cp1){
                controls[0][0].x -=0.3;
            }
            else if(cp2){
                controls[0][1].x -=0.3;
            }
            else if(cp3){
                controls[0][2].x -=0.3;
            }
            else if(cp4){
                controls[0][3].x -=0.3;
            }
            else if(cp5){
                controls[1][0].x -=0.3;
            }
            else if(cp6){
                controls[1][1].x -=0.3;
            }
            else if(cp7){
                controls[1][2].x -=0.3;
            }
            else if(cp8){
                controls[1][3].x -=0.3;
            }
            else if(cp9){
                controls[2][0].x -=0.3;
            }
            else if(cp10){
                controls[2][1].x -=0.3;
            }
            else if(cp11){
                controls[2][2].x -=0.3;
            }
            else if(cp12){
                controls[2][3].x -=0.3;
            }
            else if(cp13){
                controls[3][0].x -=0.3;
            }
            else if(cp14){
                controls[3][1].x -=0.3;
            }
            else if(cp15){
                controls[3][2].x -=0.3;
            }
            else if(cp16){
                controls[3][3].x -=0.3;
            }
            
            break;

    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
    tolower(key);
    switch(key){
        case 's':
            
            if(cp1){
                controls[0][0].z +=0.3;
            }
            else if(cp2){
                controls[0][1].z +=0.3;
            }
            else if(cp3){
                controls[0][2].z +=0.3;
            }
            else if(cp4){
                controls[0][3].z +=0.3;
            }
            else if(cp5){
                controls[1][0].z +=0.3;
            }
            else if(cp6){
                controls[1][1].z +=0.3;
            }
            else if(cp7){
                controls[1][2].z +=0.3;
            }
            else if(cp8){
                controls[1][3].z +=0.3;
            }
            else if(cp9){
                controls[2][0].z +=0.3;
            }
            else if(cp10){
                controls[2][1].z +=0.3;
            }
            else if(cp11){
                controls[2][2].z +=0.3;
            }
            else if(cp12){
                controls[2][3].z +=0.3;
            }
            else if(cp13){
                controls[3][0].z +=0.3;
            }
            else if(cp14){
                controls[3][1].z +=0.3;
            }
            else if(cp15){
                controls[3][2].z +=0.3;
            }
            else if(cp16){
                controls[3][3].z +=0.3;
            }
            break;
        case 'w':
            if(cp1){
                controls[0][0].z -=0.3;
            }
            else if(cp2){
                controls[0][1].z-=0.3;
            }
            else if(cp3){
                controls[0][2].z -=0.3;
            }
            else if(cp4){
                controls[0][3].z -=0.3;
            }
            else if(cp5){
                controls[1][0].z -=0.3;
            }
            else if(cp6){
                controls[1][1].z -=0.3;
            }
            else if(cp7){
                controls[1][2].z -=0.3;
            }
            else if(cp8){
                controls[1][3].z -=0.3;
            }
            else if(cp9){
                controls[2][0].z -=0.3;
            }
            else if(cp10){
                controls[2][1].z -=0.3;
            }
            else if(cp11){
                controls[2][2].z -=0.3;
            }
            else if(cp12){
                controls[2][3].z -=0.3;
            }
            else if(cp13){
                controls[3][0].z -=0.3;
            }
            else if(cp14){
                controls[3][1].z -=0.3;
            }
            else if(cp15){
                controls[3][2].z -=0.3;
            }
            else if(cp16){
                controls[3][3].z -=0.3;
            }
            break;
            
        case 'i':
            camx += 5;
            break;
        case 'k':
            camx -= 5;
            break;
        case 'j':
            camy += 5;
            break;
        case 'l':
            camy -= 5;
            break;
            
        case 't':
            if(DiffusePlus){
                lightDiffuse[0]+=.1;lightDiffuse[1]+=.1;lightDiffuse[2]+=.1;
            }
            break;
        case 'g':
            if(DiffuseMinus){
                lightDiffuse[0]-=.1;lightDiffuse[1]-=.1;lightDiffuse[2]-=.1;
            }
            break;
        case 'f':
            if(SpecularPlus){
                lightSpecular[0]+=.1;lightSpecular[1]+=.1;lightSpecular[2]+=.1;
            }
            break;
        case 'h':
            if(SpecularMinus){
                lightSpecular[0]-=.1;lightSpecular[1]-=.1;lightSpecular[2]-=.1;
            }
            break;
        case 'z':
            if(ShininessPlus){
                shininess[0]+=5;
            }
            break;
        case 'x':
            if(ShininessMinus){
                shininess[0]-=5;
            }
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(1000,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Spline and Surface");
    
    
    // initializing callbacks
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    
    init_control_points();
    make_triangles();
    //Creates Menu on Right Click
    CreateMenu();
    glutSpecialFunc(specialKey);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
    
}
