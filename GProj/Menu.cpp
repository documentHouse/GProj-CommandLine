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

void Menu::startInterface()
{
    cout << "Initial Interface." << endl;
}

string Menu::description()
{
    return string("Menu");
}

void Menu::processInput(string inputString)
{
    
}

MenuSignal Menu::signal()
{
    return _menuSignal;
}