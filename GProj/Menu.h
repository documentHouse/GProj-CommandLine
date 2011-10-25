//
//  Menu.h
//  GProj
//
//  Created by Andrew on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

class MenuSystem;

#ifndef GProj_Menu_h
#define GProj_Menu_h

class Menu {

private:
    MenuSystem *_menuSystem;
    
public:
    Menu(MenuSystem *menuSystem);
};

#endif
