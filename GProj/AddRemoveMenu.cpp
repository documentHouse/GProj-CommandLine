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
#include "AddRemoveMenu.h"
using namespace std;

AddRemoveMenu::AddRemoveMenu(MenuSystem *menuSystem, const string &currentDirectory) : Menu(menuSystem), _currentDirectory(currentDirectory)
{
    if(_currentDirectory.empty())
        cout << "No directory given" << endl; 
    else
        cout << "Directory specified: " << currentDirectory << endl;
}

AddRemoveMenu::~AddRemoveMenu()
{
    std::cout << "Deleting Add-Remove Menu" << endl;
}

MenuSystem::MenuType AddRemoveMenu::menuType()
{
    return MenuSystem::ADDREMOVE;
}
