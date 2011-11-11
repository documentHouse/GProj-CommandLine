//
//  AddRemoveMenu.h
//  GProj
//
//  Created by Andrew on 11/9/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GProj_AddRemoveMenu_h
#define GProj_AddRemoveMenu_h

#include <vector>

class MenuSystem;
class Menu;
class MenuOption;

class AddRemoveMenu : public Menu {
    
public:
    AddRemoveMenu(MenuSystem *menuSystem);
    ~AddRemoveMenu();
    void startInterface();
    void displayMenu();
    MenuSystem::MenuType menuType();
    void processInput(string inputString);
    
private:
    bool isOption(int optionInt);
    bool isOption(char optionChar);
    MenuOption *getOption(char optionChar);
    void updateActions();
    void updateOptions();
    void displayActions();
    void displayOptions();
    
    vector<string> _actions;
    vector<MenuOption *> _options;
};

#endif
