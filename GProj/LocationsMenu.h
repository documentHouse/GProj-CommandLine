//
//  LocationsMenu.h
//  GProj
//
//  Created by Andy on 10/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//



#ifndef GProj_LocationsMenu_h
#define GProj_LocationsMenu_h

#include <iostream>
#include <string>
#include "Menu.h"
using namespace std;

class LocationsMenu : public Menu {
    
public:
    LocationsMenu(MenuSystem *menuSystem);
    
    void startInterface();
    int description();
};

#endif
