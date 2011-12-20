//
//  Menu.cpp
//  GProj
//
//  Created by Andrew on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "Menu.h"
#include "MenuOption.h"
using namespace std;

Menu::Menu(MenuSystem *menuSystem) : _menuSystem(menuSystem), _menuSignal(WAITING)
{
    _menuSystem->_StateValue = 0;
}

Menu::~Menu()
{
    for(vector<MenuOption *>::iterator it = _options.begin(); it != _options.end(); it++)
        delete *it;
}

void Menu::signalProcess()
{
    _menuSignal = PROCESS;
}

void Menu::signalChange(MenuSystem::MenuType menuType)
{
    _menuSignal = CHANGE;
    _changeToMenuType = menuType;
}

void Menu::signalKill()
{
    _menuSignal = KILL;
}

void Menu::setOptions(vector<MenuOption *> options)
{
    for(vector<MenuOption *>::iterator it = _options.begin(); it != _options.end(); it++)
        delete *it;
    
    _options = options;
}

MenuOption *Menu::getOption(char optionChar)
{
    for(vector<MenuOption *>::iterator it = _options.begin(); it != _options.end(); it++)
        if((*it)->getChar() == optionChar)
            return *it;
    
    return NULL;
}

bool Menu::isOption(char optionChar)
{
    for(vector<MenuOption *>::iterator it = _options.begin(); it != _options.end(); it++)
        if((*it)->getChar() == optionChar)
            return true;
    
    return false;
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

void Menu::displayOptions()
{
    cout << "Options" << endl;
    cout << "=======" << endl;
    
    for(vector<MenuOption *>::iterator it = _options.begin(); it != _options.end(); it++)
        cout << (*it)->getChar() << ". " << (*it)->getString() << endl;
}

void Menu::clearScreen()
{
    static bool isSet = false;

    if(!isSet)
    {
        int result = 0;
        
        if((setupterm(NULL, STDOUT_FILENO, &result) == OK)&&(result == 1))
            isSet = true;
        else
            cout << "Error setting up the terminal" << endl;
    }

    if(isSet)
    {
        putp(clear_screen);
        cout << flush;
    }
}

void Menu::startInterface()
{
    _menuSignal = PROCESS;
    clearScreen();
}

void Menu::displayMenu()
{
    
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

MenuSystem::MenuType Menu::changeMenuType()
{
    return _changeToMenuType;
}
