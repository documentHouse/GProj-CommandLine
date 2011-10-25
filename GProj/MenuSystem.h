//
//  MenuSystem.h
//  GProj
//
//  Created by Andrew on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "Menu.h"

#ifndef GProj_MenuSystem_h
#define GProj_MenuSystem_h

class MenuSystem {
    
    // Holds global data that each menu can set and
    // refer to.
    // StateValue is for illustration purposes
    int _StateValue;
    
    // Holds the current menu on the screen
    Menu *currentMenu;

    static MenuSystem *menuSystem;
    
    MenuSystem();
    MenuSystem(const MenuSystem &);
    MenuSystem &operator=(const MenuSystem &);
public:

    static MenuSystem *sharedMenuSystem();
    // Allows Menu Subclass to access global data from MenuSystem
    friend class Menu;
};


#endif
