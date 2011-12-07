//
//  AddRemoveMenu.cpp
//  GProj
//
//  Created by Andrew on 11/9/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MenuSystem.h"
#include "Menu.h"
#include "MenuOption.h"
#include "AddRemoveMenu.h"
using namespace std;

extern char **environ;

AddRemoveMenu::AddRemoveMenu(MenuSystem *menuSystem) : Menu(menuSystem)
{
    setActions();
    setOptions();
}

AddRemoveMenu::~AddRemoveMenu()
{

}


bool AddRemoveMenu::isOption(int optionInt)
{
    if((_actions.size() >= optionInt)&&(optionInt != 0))
        return true;
    else
        return false;
}

void AddRemoveMenu::setActions()
{
    string addNewDir = "Add a new directory";
    _actions.push_back(addNewDir);
    string addCurrentDir = "Add the current directory";
    _actions.push_back(addCurrentDir);
    string removeDir = "Remove a directory";
    _actions.push_back(removeDir);
}

void AddRemoveMenu::setOptions()
{

    vector<MenuOption *> options;
    MenuOption *viewLocationOption = new MenuOption('l',"Choose a location",MenuSystem::LOCATION);
    options.push_back(viewLocationOption);
    MenuOption *exitOption = new MenuOption('e',"Exit the program.",MenuSystem::EXIT);
    options.push_back(exitOption);   

    Menu::setOptions(options);
}

void AddRemoveMenu::displayActions()
{
    
    cout << "Actions" << endl;
    cout << "=======" << endl;
    
    int i = 0;
    for(vector<string>::iterator it = _actions.begin(); it != _actions.end(); it++)
        cout << ++i << ". " << *it << endl;
    cout << endl;

}

void AddRemoveMenu::startInterface()
{
    Menu::startInterface();
    displayActions();
    displayOptions();
}

void AddRemoveMenu::displayMenu()
{
    clearScreen();
    displayActions();
    displayOptions();
}

MenuSystem::MenuType AddRemoveMenu::menuType()
{
    return MenuSystem::ADDREMOVE;
}

void AddRemoveMenu::processInput(string inputString)
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
                change(MenuSystem::ADDNEWDIR);
            }
            else if(menuChoiceInt == 2)
            {
                change(MenuSystem::ADDCURRENTDIR);
            }
            else if(menuChoiceInt == 3)
            {
                change(MenuSystem::REMOVEDIR);
            }
            else
            {
                process();
            }
        }
        else
        {
            printInvalidAndProcess();
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
            else
            {
                cout << "The PWD: " << getenv("PWD") << endl;
                
                // Assuming there are no more menus for now
                change(MenuSystem::LOCATION);
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