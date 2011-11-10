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

AddRemoveMenu::AddRemoveMenu(MenuSystem *menuSystem) : Menu(menuSystem)
{
    
}

AddRemoveMenu::~AddRemoveMenu()
{
    std::cout << "Deleting Add-Remove Menu" << endl;
}
