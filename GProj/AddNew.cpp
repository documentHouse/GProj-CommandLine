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
    setOptions();
}

AddNew::~AddNew()
{
    
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

void AddNew::startInterface()
{
    Menu::startInterface();
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
    static char menuChoiceChar;
    
    // Holds whether the entered value is valid
    static bool isValidChar;
    
    isValidChar = validateChar(inputString, &menuChoiceChar);

    if(isValidChar)
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