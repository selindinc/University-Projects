//
//  display.hpp
//  CS460-hw3
//
//  Created by Selin Dinc on 12.03.2020.
//  Copyright © 2020 Selin Dinc. All rights reserved.
//


#ifndef display_hpp
#define display_hpp

#define PI 3.1415926


void setup();
void reshape( int w, int h );
void display();
void projection(int width, int height, int perspectiveORortho);
void RenderGLScene(int base_raidus, int top_radius, int height);
void RenderGLScene2(int base_raidus, int top_radius, int height);
void DrawGround();

// setting the rotation.
void RollUp(float n);
void RollDown(float n);
void PitchUp(float n);
void PitchDown(float n);
void YawUp(float n);
void YawDown(float n);
void SlideUp(float n);
void SlideDown(float n );
void leverPlus (float n);
void leverMinus (float n);

#endif 
