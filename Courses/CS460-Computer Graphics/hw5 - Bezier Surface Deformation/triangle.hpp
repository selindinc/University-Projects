//
//  triangle.hpp
//  ass5
//
//  Created by Selin Dinc on 25.04.2020.
//  Copyright © 2020 Selin Dinc. All rights reserved.
//


#include <stdlib.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <array>
#include <vector>

#define EPS .0001
using namespace std;

struct Vec3f{
    float x=0, y=0, z=0;
    Vec3f() = default;
    Vec3f(float x, float y, float z){this->x=x;this->y=y;this->z=z;}
    
    Vec3f operator-(const Vec3f& o) const{return Vec3f(x-o.x, y-o.y, z-o.z);}
    bool operator==(const Vec3f& o) const{
        return abs(x-o.x)<EPS && abs(y-o.y)<EPS && abs(z-o.z)<EPS;}
    float len2() const {return x*x + y*y + z*z;}
    Vec3f normalize(){
        float l = sqrt(len2());
        if(l != 0) x/=l, y/=l, z/=l;
        return *this;
    }
};

struct Triangle{
    Vec3f normal, a, b, c;
    Triangle() = default;
    Triangle(Vec3f p1, Vec3f p2, Vec3f p3){a = p1;b = p2;c = p3;}
    bool contains(const Vec3f& p) const{return p == a || p == b || p == c;}
};


array<array<Vec3f, 4>, 4> controls;
array<array<Vec3f, 20>, 20> points;
vector<Triangle> triangles;
int camx = 25, camy = 25;



Vec3f normal(Triangle t){
    Vec3f ret;
    Vec3f u = t.b - t.a;
    Vec3f v = t.c - t.a;
    ret.x = u.y*v.z - u.z*v.y;
    ret.y = u.z*v.x - u.x*v.z;
    ret.z = u.x*v.y - u.y*v.x;
    return ret;
}

Vec3f normal_avg(Vec3f p){
    float count = 0;
    float x = 0, y = 0, z = 0;
    for(const auto& t: triangles){
        if(t.contains(p)){
            x += t.normal.x;
            y += t.normal.y;
            z += t.normal.z;
            count++;
        }
    }
    return Vec3f(x/count, y/count, z/count);
}

void calculate_normals(){
    for(Triangle& t: triangles){
        t.normal = normal(t);
    }
}

int dot(Vec3f p1, Vec3f p2){
    return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
}

void init_control_points(){
    
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            controls[i][j].x = (i*4+i);
            controls[i][j].z = (j*4+j);
        }
    }
}




