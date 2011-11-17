//
//  Menu.h
//  GProj
//
//  Created by Andrew on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GProj_Menu_h
#define GProj_Menu_h

#include <curses.h>
#include <term.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "MenuSystem.h"
#include "MenuSignal.h"
using namespace std;

class MenuOption;

// Convenience macros for use in the processInput(string) method
#define kill() signalKill();return;
#define change(TYPE) signalChange(TYPE);return;
#define process() signalProcess();return;
#define printInvalidAndProcess() cout << "Your entry was invalid" << endl;process();

class Menu {
private:
    MenuSystem::MenuType _changeToMenuType;
    MenuSignal _menuSignal;
    stringstream _stringStream;
    vector<MenuOption *> _options;
protected:
    MenuSystem *_menuSystem;
    
    void signalProcess();
    void signalKill();
    void signalChange(MenuSystem::MenuType menuType);
    
    void setOptions(vector<MenuOption *> options);
    MenuOption *getOption(char optionChar);
    bool isOption(char optionChar);
    bool validateInt(string intString, int *intValue);
    bool validateChar(string charString, char *charValue);
    
    void displayOptions();
public:
    Menu(MenuSystem *menuSystem);
    virtual ~Menu();
    
    static void clearScreen();

    virtual void startInterface() = 0;
    virtual void displayMenu() = 0;
    virtual MenuSystem::MenuType menuType() = 0;
    virtual void processInput(string inputString) = 0;
    MenuSignal signal();
    MenuSystem::MenuType changeMenuType();
};

#endif
