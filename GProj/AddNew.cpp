//
//  AddNew.cpp
//  GProj
//
//  Created by Andy on 11/20/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MenuSystem.h"
//#include "Menu.h"
#include "MenuOption.h"
#include "AddNew.h"


AddNew::AddNew(MenuSystem *menuSystem) : Menu(menuSystem)
{
    setActions();
    setOptions();
}

AddNew::~AddNew()
{
    
}


bool AddNew::isOption(int optionInt)
{
    if((_actions.size() >= optionInt)&&(optionInt != 0))
        return true;
    else
        return false;
}

void AddNew::setActions()
{
    string searchDir = "Search for git directories";
    _actions.push_back(searchDir);
    string enterDir = "Enter git directory";
    _actions.push_back(enterDir);
}

void AddNew::setOptions()
{
    vector<MenuOption *> options;
    MenuOption *viewLocationOption = new MenuOption('r',"Return to the location options",MenuSystem::ADDREMOVE);
    options.push_back(viewLocationOption);
    MenuOption *exitOption = new MenuOption('e',"Exit the program.",MenuSystem::EXIT);
    options.push_back(exitOption); 
    
    Menu::setOptions(options);
}

void AddNew::displayActions()
{
    
    cout << "Actions" << endl;
    cout << "=======" << endl;
    
    int i = 0;
    for(vector<string>::iterator it = _actions.begin(); it != _actions.end(); it++)
        cout << ++i << ". " << *it << endl;
    cout << endl;
    
}

void AddNew::startInterface()
{
    Menu::startInterface();
    displayActions();
    displayOptions();
}

void AddNew::displayMenu()
{
    clearScreen();
    displayOptions();
}

MenuSystem::MenuType AddNew::menuType()
{
    return MenuSystem::ADDNEWDIR;
}

void AddNew::processInput(string inputString)
{
    // Holds the value entered by the user for this menu
    static int menuChoiceInt;
    static char menuChoiceChar;
    
    // Holds whether the entered value is valid
    static bool isValidInt; 
    static bool isValidChar;
    
    isValidInt = validateInt(inputString, &menuChoiceInt);
    isValidChar = validateChar(inputString, &menuChoiceChar);
    
    if(isValidInt)
    {
        if(isOption(menuChoiceInt))
        {
            // You need to find a way to associate values with menu selections
            // This more general than assuming the order that is setup in setActions()
            
            //process();
            if(menuChoiceInt == 1)
            {
                //change(MenuSystem::ENTERDIR);
                kill();
            }
            else if(menuChoiceInt == 2)
            {
                cout << "trying to switch to enter dir..." << endl;
                change(MenuSystem::ENTERDIR);
                //kill();
            }
            else if(menuChoiceInt == 3)
            {
                //change(MenuSystem::REMOVEDIR);
                kill();
            }
            else
            {
                process();
            }
        }
    }
    else if(isValidChar)
    {
        if(Menu::isOption(menuChoiceChar))
        {
            MenuSystem::MenuType menuType = getOption(menuChoiceChar)->getValue();
            if(menuType == MenuSystem::EXIT)
            {
                kill();
            }
            else if(menuType == MenuSystem::ADDREMOVE)
            {                
                // Assuming there are no more menus for now
                change(MenuSystem::ADDREMOVE);
            }
        }
        else
        {
            printInvalidAndProcess();
        }
    }
    else
    {
        printInvalidAndProcess();
    }

}