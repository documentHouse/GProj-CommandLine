//
//  Menu.cpp
//  GProj
//
//  Created by Andrew on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "Menu.h"
//#include "MenuSystem.h"
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

void Menu::signalChange(MenuSystem::MenuType menuType)
{
    _menuSignal = CHANGE;
}

void Menu::signalKill()
{
    cout << "Killing Menu: " << description() << endl;
    _menuSignal = KILL;
}

bool Menu::validateInt(string intString, int *intValue)
{

    _stringStream.clear();
    _stringStream.str(intString);    
    
    _stringStream >> *intValue;
    
    if(_stringStream.fail())
        return false;
    else
        return true;
}

bool Menu::validateChar(string charString, char *charValue)
{
    // We are looking for one character so the string should have length 1
    if(charString.length() > 1)
        return false;
    
    _stringStream.clear();
    _stringStream.str(charString);

    _stringStream >> *charValue;
    
    if(_stringStream.fail())
       return false;
    else
       return true;
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