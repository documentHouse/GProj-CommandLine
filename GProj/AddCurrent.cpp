//
//  AddCurrent.cpp
//  GProj
//
//  Created by Andy on 11/20/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MenuOption.h"
#include "AddCurrent.h"
using namespace std;

extern char **environ;

AddCurrent::AddCurrent(MenuSystem *menuSystem) : Menu(menuSystem)
{
    currentDir = string(getenv("PWD"));
    setOptions();
}

AddCurrent::~AddCurrent()
{
    
}

void AddCurrent::setOptions()
{
    vector<MenuOption *> options;
    
    string addDir = " add ";
    addDir.append(currentDir);
    
    string yesString = "Yes";
    string noString = "No";
    
    MenuOption *yesOption = new MenuOption('y',yesString.append(addDir).c_str(),MenuSystem::ADDREMOVE);
    options.push_back(yesOption);
    MenuOption *noOption = new MenuOption('n',noString.append(addDir).c_str(),MenuSystem::ADDREMOVE);
    options.push_back(noOption);    
    MenuOption *exitOption = new MenuOption('e',"Exit the program.",MenuSystem::EXIT);
    options.push_back(exitOption); 
    
    Menu::setOptions(options);
}

void AddCurrent::startInterface()
{
    Menu::startInterface();
    displayOptions();
}

void AddCurrent::displayMenu()
{
    clearScreen();
    displayOptions();
}

MenuSystem::MenuType AddCurrent::menuType()
{
    return MenuSystem::ADDCURRENTDIR;
}

void AddCurrent::processInput(string inputString)
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
                if(menuChoiceChar == 'y')
                    _menuSystem->addLocation(currentDir);
                //else if(menuChoiceChar == 'n')
                    //cout << "You said no." << endl;
                    
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