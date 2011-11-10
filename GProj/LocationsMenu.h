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
#include <unistd.h>
#include <term.h>
#include "MenuOption.h"

class MenuSystem;
class Menu;

using namespace std;

class LocationsMenu : public Menu {
    vector<string> _locations;
    vector<MenuOption *> _options;
    
    bool isOption(char optionChar);
    MenuOption *getOption(char optionChar);
    void updateOptions();
    void displayOptions();
    void displayLocations();
    bool openShell(const char *directory);
public:
    LocationsMenu(MenuSystem *menuSystem);
    ~LocationsMenu();
    void startInterface();
    void displayMenu();
    string description();
    void processInput(string inputString);
};

#endif
