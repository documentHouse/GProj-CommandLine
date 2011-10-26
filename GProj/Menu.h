//
//  Menu.h
//  GProj
//
//  Created by Andrew on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GProj_Menu_h
#define GProj_Menu_h

#include <string>
#include <iostream>
#include "MenuSignal.h"
using namespace std;

class MenuSystem;

class Menu {
private:
    MenuSignal _menuSignal;
protected:
    MenuSystem *_menuSystem;
    
    void signalProcess();
    void signalKill();
    void signalChange();
public:
    Menu(MenuSystem *menuSystem);
    virtual ~Menu();
    virtual void startInterface();
    virtual string description();
    virtual void processInput(string inputString);
    MenuSignal signal();
};

#endif
