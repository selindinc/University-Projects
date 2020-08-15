//
//  menu.cpp
//  CS460-hw3
//
//  Created by Selin Dinc on 12.03.2020.
//  Copyright © 2020 Selin Dinc. All rights reserved.
//
#define GL_SILENCE_DEPRECATION
#include "menu.hpp"
#include"display.hpp"
#include<stdio.h>
#include<iostream>
#include<math.h>
#include<GLUT/GLUT.h>
#include<vector>
#include<assert.h>


#define ANGLE 10

bool YawBool=false;
bool PitchBool=false;
bool RollBool=false;
bool SlideBool=false;
bool RotLeverPlus=false;
bool RotLeverMinus=false;


void mouse(int button, int state, int x, int y){
    switch(button)
    {
        case GLUT_LEFT_BUTTON:
            if(state==GLUT_DOWN){
                //do something when left mouse button is down
            }
            
            break;
        case GLUT_RIGHT_BUTTON:
            break;
        case GLUT_MIDDLE_BUTTON:
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void motion( int x, int y ){
    // record the position of the mouse.
    glutPostRedisplay();
}

//creat menu
void CreateMenu(void){
    
    int sub_menu;
    
    sub_menu=glutCreateMenu(SubMenuItemClicked);
    glutAddMenuEntry("+", 1);
    glutAddMenuEntry("-", 2);
    
    glutCreateMenu(MenuItemClicked);
    glutAddMenuEntry("Roll+",  1);
    glutAddMenuEntry("Roll-",  2);
    glutAddMenuEntry("Pitch+", 3);
    glutAddMenuEntry("Pitch-", 4);
    glutAddMenuEntry("Yaw+",   5);
    glutAddMenuEntry("Yaw-",   6);
    glutAddMenuEntry("Slide+", 7);
    glutAddMenuEntry("Slide-", 8);
    glutAddSubMenu("levers rotation", sub_menu);
    //Attach Menu to RightClick
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void MenuItemClicked(int Value){
    switch(Value)
    {
        case 1:
            YawBool=false;
            PitchBool=false;
            RollBool=true;
            SlideBool=false;
            RollUp(ANGLE);
            break;
        case 2:
            YawBool=false;
            PitchBool=false;
            RollBool=true;
            SlideBool=false;
            RollDown(ANGLE);
            break;
        case 3:
            YawBool=false;
            PitchBool=true;
            RollBool=false;
            SlideBool=false;
            PitchUp(ANGLE);
            break;
        case 4:
            YawBool=false;
            PitchBool=true;
            RollBool=false;
            SlideBool=false;
            PitchDown(ANGLE);
            break;
        case 5:
            YawBool=true;
            PitchBool=false;
            RollBool=false;
            SlideBool=false;
            YawUp(ANGLE);
            break;
        case 6:
            YawBool=true;
            PitchBool=false;
            RollBool=false;
            SlideBool=false;
            
            YawDown(ANGLE);
            break;
        case 7:
            YawBool=false;
            PitchBool=false;
            RollBool=false;
            SlideBool=true;
            
            SlideUp(ANGLE);
            break;
        case 8:
            YawBool=false;
            PitchBool=false;
            RollBool=false;
            SlideBool=true;
            SlideDown(ANGLE);
            break;
    }
    //glutPostRedisplay();
}




void SubMenuItemClicked(int Value){
    
    switch(Value) {
            
        case 1:
            YawBool=false;
            PitchBool=false;
            RollBool=false;
            SlideBool=false;
            RotLeverPlus=true;
            RotLeverMinus=false;
            leverPlus(ANGLE);
            break;
            
        case 2:
            YawBool=false;
            PitchBool=false;
            RollBool=false;
            SlideBool=false;
            RotLeverPlus=false;
            RotLeverMinus=true;
            leverMinus(ANGLE);
            break;
            
    }
    //glutPostRedisplay();
}


void specialKey(int key, int x, int y){
    switch(key){
        case GLUT_KEY_UP:
            if(YawBool)   YawUp(ANGLE);
            if(PitchBool) PitchUp(ANGLE);
            if(RollBool)  RollUp(ANGLE);
            if(SlideBool) SlideUp(ANGLE);
            if(RotLeverPlus) leverPlus(ANGLE);
            
            break;
        case GLUT_KEY_DOWN:
            if(YawBool)   YawDown(ANGLE);
            if(PitchBool) PitchDown(ANGLE);
            if(RollBool)  RollDown(ANGLE);
            if(SlideBool) SlideDown(ANGLE);
            if(RotLeverMinus) leverMinus(ANGLE);
            break;
    }
    glutPostRedisplay();
}
