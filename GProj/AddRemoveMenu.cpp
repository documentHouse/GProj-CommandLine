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
    updateActions();
    updateOptions();
}

AddRemoveMenu::~AddRemoveMenu()
{
    for(vector<MenuOption *>::iterator it = _options.begin(); it != _options.end(); it++)
        delete *it;
}


bool AddRemoveMenu::isOption(int optionInt)
{
    if((_actions.size() >= optionInt)&&(optionInt != 0))
        return true;
    else
        return false;
}

bool AddRemoveMenu::isOption(char optionChar)
{
    for(vector<MenuOption *>::iterator it = _options.begin(); it != _options.end(); it++)
        if((*it)->getChar() == optionChar)
            return true;
    
    return false;
}

MenuOption *AddRemoveMenu::getOption(char optionChar)
{
    for(vector<MenuOption *>::iterator it = _options.begin(); it != _options.end(); it++)
        if((*it)->getChar() == optionChar)
            return *it;
    
    return NULL;
}

void AddRemoveMenu::updateActions()
{
    string addNewDir = "Add a new directory";
    _actions.push_back(addNewDir);
    string addCurrentDir = "Add the current directory";
    _actions.push_back(addCurrentDir);
    string removeDir = "Remove a directory";
    _actions.push_back(removeDir);
}

void AddRemoveMenu::updateOptions()
{
    MenuOption *viewLocationOption = new MenuOption('l',"Choose a location",MenuSystem::LOCATION);
    _options.push_back(viewLocationOption);
    MenuOption *exitOption = new MenuOption('e',"Exit the program.",MenuSystem::EXIT);
    _options.push_back(exitOption);   
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

void AddRemoveMenu::displayOptions()
{
    cout << "Options" << endl;
    cout << "=======" << endl;
    
    for(vector<MenuOption *>::iterator it = _options.begin(); it != _options.end(); it++)
        cout << (*it)->getChar() << ". " << (*it)->getString() << endl;
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
    int menuChoiceInt;
    char menuChoiceChar;
    
    bool isValidInt = validateInt(inputString, &menuChoiceInt);
    bool isValidChar = validateChar(inputString, &menuChoiceChar);
    
    if(isValidInt)
    {
        //if((_locations.size() >= menuChoiceInt)&&(menuChoiceInt != 0))
        if(isOption(menuChoiceInt))
        {
            // You need to find a way to associate values with menu selections
            // This more general than assuming the order that is setup in updateActions()
            cout << "Option chosen: " << menuChoiceInt << endl;
            process();
        }
        else
        {
            printInvalidAndProcess();
        }
        
    }
    else if(isValidChar)
    {
        if(isOption(menuChoiceChar))
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