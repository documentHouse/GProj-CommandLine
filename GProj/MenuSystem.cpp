//
//  MenuSystem.cpp
//  GProj
//
//  Created by Andrew on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MenuSystem.h"

MenuSystem *MenuSystem::menuSystem = NULL;

MenuSystem *MenuSystem::sharedMenuSystem()
{
    if(menuSystem != NULL)
        return menuSystem;
    
    menuSystem = new MenuSystem;
    return menuSystem;
}

MenuSystem::MenuSystem()
{
    
}

