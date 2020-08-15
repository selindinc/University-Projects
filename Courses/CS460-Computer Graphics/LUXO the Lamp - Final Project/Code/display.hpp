//
//  display.hpp
//  luxo_demo_2
//
//  Created by Selin Dinc on 8.05.2020.
//  Copyright © 2020 Selin Dinc. All rights reserved.
//

#ifndef display_hpp
#define display_hpp

#include <stdio.h>

#define PI 3.1415926
#include "util.hpp"


void setup();
void reshape( int w, int h );
void display();
void basePlate(int base_radius, int top_radius, int height);
void firstHalf(double rStand, int hStand, int rJoint, int hJoint, int fsAngle);
void secondHalf(double rStand, int hStand, int rJoint, int hJoint, int fsAngle);
void lamp(double rStand, int hStand, int rJoint, int hJoint, int fsAngle);
void forward();
void in();
void lampMove();
void drawPixar();


#endif /* display_hpp */



