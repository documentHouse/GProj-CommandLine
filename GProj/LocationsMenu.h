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
#include "MenuSystem.h"
class Menu;

using namespace std;

class LocationsMenu : public Menu {
public:
    LocationsMenu(MenuSystem *menuSystem);
    ~LocationsMenu();
    void startInterface();
    void displayMenu();
    MenuSystem::MenuType menuType();
    void processInput(string inputString);
    
private:
    vector<string> _locations;
    
    bool isOption(int optionInt);
    bool isOption(char optionChar);
    
    void setOptions();
    void displayLocations();
    bool openShell(const char *directory);    
};

#endif
