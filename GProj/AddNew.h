//
//  AddNew.h
//  GProj
//
//  Created by Andy on 11/20/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GProj_AddNew_h
#define GProj_AddNew_h

#include "Menu.h"

class MenuSystem;

class AddNew : public Menu{
public:
    AddNew(MenuSystem *menuSystem);
    ~AddNew();
    
    void startInterface();
    void displayMenu();
    MenuSystem::MenuType menuType();
    void processInput(string inputString);

private:
    bool isOption(int optionInt);
    void setActions();
    void setOptions();
    void displayActions();
    vector<string> _actions;
};

#endif
