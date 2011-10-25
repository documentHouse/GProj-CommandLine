//
//  MenuSystem.h
//  GProj
//
//  Created by Andrew on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//



#ifndef GProj_MenuSystem_h
#define GProj_MenuSystem_h

#include <iostream>
#include <fstream>
#include <vector>
#include "CoreFoundation/CFBundle.h"
#include "Menu.h"
#include "LocationsMenu.h"
using namespace std;

class MenuSystem {
    
    // Holds global data that each menu can set and
    // refer to.
    // StateValue is for illustration purposes
    int _StateValue;
    
    // Holds the current menu on the screen
    Menu *currentMenu;

    // Holds all of the menus that were initialized
    vector<Menu *> menus;
    
    static MenuSystem *menuSystem;

    CFBundleRef bundleRef;
    CFStringRef locationsURLString;
    
    // The only access to the singleton is through the sharedMenuSystem()
    // factory method.
    MenuSystem();
    MenuSystem(const MenuSystem &);
    MenuSystem &operator=(const MenuSystem &);
public:

    static MenuSystem *sharedMenuSystem();
    
    ~MenuSystem();
    
    // Load the initial interface through the first menu
    void start();
    
    // Allows Menu Subclass to access global data from MenuSystem
    friend class Menu;
};


#endif
