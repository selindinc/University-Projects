//
//  menu.hpp
//  CS460-hw3
//
//  Created by Selin Dinc on 12.03.2020.
//  Copyright © 2020 Selin Dinc. All rights reserved.
//

#ifndef menu_hpp
#define menu_hpp


#include <stdio.h>


void mouse(int button, int state, int x, int y);// call when left/right/middle click.
void motion( int x, int y );// call when mouse motion
void CreateMenu(void);  // creat menu
void MenuItemClicked(int Value); // creat menu
void SubMenuItemClicked(int Value);// creat sub-menu
void specialKey(int key, int x, int y);


#endif /* menu_hpp */
