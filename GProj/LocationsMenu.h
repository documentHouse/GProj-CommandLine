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
#include <vector>

class MenuSystem;
class Menu;

using namespace std;

class LocationsMenu : public Menu {
    vector<string> _locations;
public:
    LocationsMenu(MenuSystem *menuSystem);
    ~LocationsMenu();
    void startInterface();
    string description();
    void processInput(string inputString);
};

#endif
