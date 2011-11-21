//
//  AddCurrent.h
//  GProj
//
//  Created by Andy on 11/20/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GProj_AddCurrent_h
#define GProj_AddCurrent_h

#include "Menu.h"

class MenuSystem;

class AddCurrent : public Menu{
public:
    AddCurrent(MenuSystem *menuSystem);
    ~AddCurrent();
    
    void startInterface();
    void displayMenu();
    MenuSystem::MenuType menuType();
    void processInput(string inputString);
    
private:
    void setOptions();
    string currentDir;
};

#endif
