//
//  Menu.cpp
//  GProj
//
//  Created by Andrew on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "Menu.h"
#include "MenuSystem.h"
using namespace std;

Menu::Menu(MenuSystem *menuSystem) : _menuSystem(menuSystem), _menuSignal(PROCESS)
{
    _menuSystem->_StateValue = 0;
}

Menu::~Menu()
{
    cout << "Deleting Menu: " << description() << endl;
}

void Menu::signalProcess()
{
    _menuSignal = PROCESS;
}

void Menu::signalChange()
{
    _menuSignal = CHANGE;
}

void Menu::signalKill()
{
    cout << "Killing Menu: " << description() << endl;
    _menuSignal = KILL;
}

void Menu::startInterface()
{
    _menuSignal = PROCESS;
    cout << "Base Menu Interface" << endl;
}

string Menu::description()
{
    return string("Menu");
}

void Menu::processInput(string inputString)
{
    ;
}

MenuSignal Menu::signal()
{
    // The menu is still alive so we put the menu in the 
    // waiting state and tell the MenuSystem to change
    if(_menuSignal == CHANGE)
    {
        _menuSignal = WAITING;
        return CHANGE;
    }
    else
        return _menuSignal;
}