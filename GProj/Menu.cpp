//
//  Menu.cpp
//  GProj
//
//  Created by Andrew on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Menu.h"
#include "MenuSystem.h"

Menu::Menu(MenuSystem *menuSystem) : _menuSystem(menuSystem)
{
    _menuSystem->_StateValue = 0;
}