//
//  main.cpp
//  cs460-ass4
//
//  Created by Selin Dinc on 1.04.2020.
//  Copyright © 2020 Selin Dinc. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<math.h>
#include<GLUT/glut.h>
#include<vector>
#include<assert.h>
#include <time.h>


using namespace std;
#define ANGLE 30

bool leftFlag = false;
bool image = false, Rotate = false, object = false,object_rotate=false;

float m_xtheta = 0, m_ytheta = 0,m_ztheta=0;
float zoom=1;


struct vec4{
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat w;
};

struct vec3{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct vecs3{
    GLint x;
    GLint y;
    GLint z;
};

struct Position{
    Position() : x(0), y(0), u(0), v(0) {}
    Position(float m, float n){
        x=m; y=n;
    }
    Position(float m, float n, float i, float j){
        x = m; y =n; u = i; v = j;
    }
    float x;
    float y;
    float u;
    float v;
};

struct Color{
    float r, g, b;
};


#define PI 3.1415926
#define header 54
int WIDTH_IMG;
int HEIGHT_IMG;
std::vector<unsigned char> data; //texels
std::vector<std::vector<Color> > topLeft, topRight,downLeft,downRight;
std::vector<Color> colors;

static GLuint texName;
Position center;
Position minRec,maxRec;
#define R 3
//teapot
vector<vec3> vertices;
vector<vec3> normals;
vector<vecs3> elements;
int WIDTH_WINDOWS;
int HEIGHT_WINDOWS;

// load BMP image.
void readBMP(char * filename){
    Color col;
    FILE * fd;
    if((fd=fopen(filename,"rb")) == NULL){
        perror("Error happens\n");
    }else{
        printf("file opened\n");
    }
    unsigned char info[header];
    fread(info,sizeof(unsigned char), header, fd); //read the header-byte header
    //extract the  heght and width of the image from the header info.
    
    WIDTH_IMG = *(int *)&info[18];
    HEIGHT_IMG = *(int *)&info[22];
    int size=3 * WIDTH_IMG * HEIGHT_IMG;
    printf("%d, %d\n", WIDTH_IMG, HEIGHT_IMG );
    
    unsigned char * pixel = (unsigned char *)malloc(sizeof(unsigned char)*size);
    fread(pixel, sizeof(unsigned char), size, fd);// read the data
    fclose(fd);
    
    //restore pixel from BGR to RGB.
    //
    for (int i = 0; i < size; i += 3){
        unsigned char temp=pixel[i];
        pixel[i] = pixel[i+2];
        pixel[i+2] = temp;
    }
    
    for(int i = 0; i < size; i++){
        data.push_back(pixel[i]);
    }
    
    for(int i = 0; i<WIDTH_IMG;i++){
        for(int j = 0; j<HEIGHT_IMG;j++){
            col.r = data.at(3*(j*WIDTH_IMG+ i));
            col.g = data.at(3*(j*WIDTH_IMG+ i)+1);
            col.b = data.at(3*(j*WIDTH_IMG+ i)+2);
            colors.push_back(col);
        }
    }
    

    for(int i = 0; i<WIDTH_IMG/2;i++){
        downLeft.push_back(std::vector<Color>());
        for(int j = 0; j<HEIGHT_IMG/2;j++){
            col = colors.at(j+HEIGHT_IMG*i);
            downLeft[i].push_back(col);
            
        }
    }
    
    for(int i = WIDTH_IMG/2; i<WIDTH_IMG;i++){
        downRight.push_back(std::vector<Color>());
        for(int j = 0; j<HEIGHT_IMG/2;j++){
            col = colors.at(j+HEIGHT_IMG*i);
            downRight[i-WIDTH_IMG/2].push_back(col);
        }
    }
    
    for(int i = 0; i<WIDTH_IMG/2;i++){
        topLeft.push_back(std::vector<Color>());
        for(int j = HEIGHT_IMG/2; j<HEIGHT_IMG;j++){
            col = colors.at(j+HEIGHT_IMG*i);
            topLeft[i].push_back(col);
        }
    }
    
    for(int i=WIDTH_IMG/2;i<WIDTH_IMG;i++){
        topRight.push_back(std::vector<Color>());
        for(int j = HEIGHT_IMG/2; j<HEIGHT_IMG;j++){
            col = colors.at(j+HEIGHT_IMG*i);
            topRight[i-WIDTH_IMG/2].push_back(col);
        }
    }
    
    
    
    //printf("%d\n", data.size() );
    
}

// Load OBJ file.
void loadOBJ(char * filename, vector<vec3> *vertices, vector<vec3> *normals, vector<vecs3> *elements){
    FILE *fd=fopen(filename, "rb");
    assert(fd != NULL);
    
    while( 1 ){
        char line[128];
        int res = fscanf(fd, "%s", line);
        if(res == EOF)
            break;  // EOF = end of the file, and quit the loop.
        //else, parse the line.
        if( strcmp(line, "v") == 0){
            //read vertices
            vec3 vertex;
            fscanf(fd, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            vertices->push_back(vertex);
        }else if( strcmp(line, "vt") == 0){
            //read vertices texture
        }else if(strcmp(line, "vn") == 0){
            
        }else if(strcmp(line, "f") == 0){
            vecs3 temp;
            fscanf(fd, "%d %d %d\n", &temp.x, &temp.y, &temp.z);
            elements->push_back(temp);
        }else{
            //ignore
        }
        
    }
    fclose(fd);
}

void setup()
{
    glClearColor(0, 0, 0, 1.0); // *should* display black background
    // setting for the texture
    // load image
    readBMP("flower.bmp"); //WIDTH HEIGHT data are avaiable now!
    printf("load BMP image\n");
    minRec.x = 500; minRec.y = 50;
    maxRec.x = 500 + WIDTH_IMG; maxRec.y = 50 + HEIGHT_IMG;
    center.x = (minRec.x + maxRec.x) / 2;
    center.y = (minRec.y + maxRec.y) / 2;
    
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH_IMG, HEIGHT_IMG, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
    
    printf("start to load Teapot\n");
    //load teapot
    loadOBJ("teapot.obj", &vertices, &normals, &elements);
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

Color BilinearInterpolation(float x, float y, int x1, int y1, Color Q11, Color Q21, Color Q12, Color Q22){
    int x2 = x1+1;
    int y2 = y1+1;
    
    float denom = (float)(x2-x1) * (y2-y1);
    
    Color a,b,c,d,total;
    a.r = Q11.r * (x2 - x) * (y2 - y)/denom;
    a.g = Q11.g * (x2 - x) * (y2 - y)/denom;
    a.b = Q11.b * (x2 - x) * (y2 - y)/denom;
    
    b.r = Q21.r * (x - x1) * (y2 - y)/denom;
    b.g = Q21.g * (x - x1) * (y2 - y)/denom;
    b.b = Q21.b * (x - x1) * (y2 - y)/denom;
    
    c.r = Q12.r * (x2 - x) * (y - y1)/denom;
    c.g = Q12.g * (x2 - x) * (y - y1)/denom;
    c.b = Q12.b * (x2 - x) * (y - y1)/denom;
    
    d.r = Q22.r * (x - x1) * (y - y1)/denom;
    d.g = Q22.g * (x - x1) * (y - y1)/denom;
    d.b = Q22.b * (x - x1) * (y - y1)/denom;
    
    total.r = a.r + b.r + c.r + d.r;
    total.g = a.g + b.g + c.g + d.g;
    total.b = a.b + b.b + c.b + d.b;
    
    return total;
}

void textureInterpolation(int beginx, int endx, int beginy, int endy, vector<vector<Color> > vec){
    float gridSizeX = endx - beginx, gridSizeY = endy - beginy;
    Color Q11, Q21, Q12, Q22;
    
    int i,j;
    for(i=0; i<gridSizeX; i++){
        for(j=gridSizeY-1;j>=0;j--){
            float gx = i * float(WIDTH_IMG/2) / gridSizeX;
            float gy = j * float(HEIGHT_IMG/2) / gridSizeY;
            
            if(gx != 0){
                gx --;
            }
            if(gy != 0){
                gy--;
            }
            
            int gxi = int(gx);
            int gyi = int(gy);
            
            
            Q11 = vec.at(gxi).at(gyi);
            Q21 = vec.at(gxi+1).at(gyi);
            Q12 = vec.at(gxi).at(gyi+1);;
            Q22 = vec.at(gxi+1).at(gyi+1);;
            
            Color z = BilinearInterpolation(gxi, gyi, gx, gy, Q11, Q21, Q12, Q22);
            glBegin(GL_POINTS);
            glColor3ub(z.r,z.g,z.b);
            glVertex2i(i+50+beginx, j+50+beginy);
            glEnd();
        }
    }
    
    glutSwapBuffers();
    
}

void draw(){
    textureInterpolation(0,center.x,0,center.y,downLeft);
    textureInterpolation(center.x,WIDTH_IMG,0,center.y,downRight);
    textureInterpolation(0,center.x,center.y,HEIGHT_IMG,topLeft);
    textureInterpolation(center.x,WIDTH_IMG,center.y,HEIGHT_IMG,topRight);
    
}

void display(){
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT );
    glEnable(GL_DEPTH_TEST);
    
    glLoadIdentity();
    
    // show the Image.
    if(Rotate || image){
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho( 0, WIDTH_WINDOWS, HEIGHT_WINDOWS, 0, -1, 1 );
        
        // draw the image using
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(WIDTH_IMG/2 + 50,HEIGHT_IMG/2 + 50,0.0);
        glRotatef(m_ztheta, 0,0,1);
        glTranslatef(-WIDTH_IMG/2 - 50,-HEIGHT_IMG/2 - 50,0.0);
        
        
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_DECAL);
        glBindTexture(GL_TEXTURE_2D,texName); //active the texture.
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);    glVertex3f(50,      50,       0);
        glTexCoord2f(1.0, 1.0);    glVertex3f(50+WIDTH_IMG,50,       0);
        glTexCoord2f(1.0, 0.0);    glVertex3f(50+WIDTH_IMG,50+HEIGHT_IMG,0);
        glTexCoord2f(0.0, 0.0);    glVertex3f(50,      50+HEIGHT_IMG,0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }
    
    // draw the Mesh model.
    if(object || object_rotate){
        // render the mesh model
        
        glColor3f(1,1,1);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60, 1, 1, 500000);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0,0,10,0,0,0,0,1,0);
        
        glRotatef(m_xtheta, 0, 1, 0);
        glScalef(zoom, zoom, zoom);
        glPushMatrix();
        
        for(vecs3 f: elements){
            glBegin(GL_LINE_LOOP);
            glVertex3f(vertices[f.x-1].x, vertices[f.x-1].y, vertices[f.x-1].z);
            glVertex3f(vertices[f.y-1].x, vertices[f.y-1].y, vertices[f.y-1].z);
            glVertex3f(vertices[f.z-1].x, vertices[f.z-1].y, vertices[f.z-1].z);
            glEnd();
        }
        glPopMatrix();
        
    }
    
    
    glutSwapBuffers(); // display newly drawn image in window
    
}
void mouse(int btn,int state,int x,int y){
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        leftFlag = true;
    }
    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        leftFlag = false;
    }
}

void motion(int x,int y){
    if(leftFlag && image){
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0,0.0,0.0,0.0);
        center.x = x;
        center.y = y;
        draw();
    }
    
}

void RollUp(float n){
    m_ztheta+=n;
    if(m_ztheta > 360) m_ztheta=-360;
}

void RollDown(float n){
    m_ztheta-=n;
    if(m_ztheta < -360) m_ztheta=360;
}

void ZoomIn(float n){
    zoom+=n;
    
}

void ZoomOut(float n){
    zoom-=n;
    
}

void YawUp(float n){
    m_xtheta+=n;
    if(m_xtheta > 360) m_xtheta=-360;
}

void YawDown(float n){
    m_xtheta-=n;
    if(m_xtheta < -360) m_xtheta=360;
}

void MenuItemClicked(int Value){
    
    switch(Value)
    {
        case 1:
            image = true;
            Rotate = false;
            object = false;
            object_rotate=false;
            break;
        case 2:
            image = false;
            Rotate = true;
            object = false;
            RollUp(ANGLE);
            object_rotate=false;
            break;
        case 3:
            image = false;
            Rotate = false;
            object = true;
            object_rotate=false;
            break;
        case 4:
            image=false;
            Rotate=false;
            object=false;
            object_rotate=true;
            break;
    }
    glutPostRedisplay();
}

//creat menu
void CreateMenu(void){
    
    glutCreateMenu(MenuItemClicked);
    glutAddMenuEntry("Image Warping",  1);
    glutAddMenuEntry("Image Rotate",  2);
    glutAddMenuEntry("Object Zoom", 3);
    glutAddMenuEntry("Object Rotate", 4);
    //Attach Menu to RightClick
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void specialKey(int key, int x, int y){
    switch(key){
        case GLUT_KEY_UP:
            if(Rotate){
                RollUp(ANGLE);
            }
            if(object){
                ZoomIn(0.1);
            }
            if(object_rotate){
                YawUp(ANGLE);
            }
            break;
            
        case GLUT_KEY_DOWN:
            if(Rotate){
                RollDown(ANGLE);
            }
            if(object){
                ZoomOut(0.1);
            }
            if(object_rotate){
                YawDown(ANGLE);
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
    glutCreateWindow("HW-4");
    setup();
    
    // initializing callbacks
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);  // define your own mouse event.
    glutMotionFunc(motion);  // define your own motion event, e.g., rotate OBJ model.
    
    //Creates Menu on Right Click
    CreateMenu();
    
    glutSpecialFunc(specialKey); //register a special keyboard function.
    
    glutMainLoop();
    return 0;
    
}
