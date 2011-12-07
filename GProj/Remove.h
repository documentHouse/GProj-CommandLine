//
//  Remove.h
//  GProj
//
//  Created by Andy on 12/6/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GProj_Remove_h
#define GProj_Remove_h

#include <vector>
#include "Menu.h"

class MenuSystem;

class Remove : public Menu{
public:
    Remove(MenuSystem *menuSystem);
    ~Remove();
    
    void startInterface();
    void displayMenu();
    MenuSystem::MenuType menuType();
    void processInput(string inputString);
    
private:
    vector<string> _locations;
    
    bool isOption(int optionInt);
    
    void setOptions();
    void displayLocations();    
};

#endif
