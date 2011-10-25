//
//  Menu.h
//  GProj
//
//  Created by Andrew on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GProj_Menu_h
#define GProj_Menu_h

#include <iostream>
#include <string>
class MenuSystem;

class Menu {
    
    MenuSystem *_menuSystem;
public:
    Menu(MenuSystem *menuSystem);
    virtual void startInterface();
    virtual int description();
};

#endif
