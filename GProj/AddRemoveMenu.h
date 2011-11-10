//
//  AddRemoveMenu.h
//  GProj
//
//  Created by Andrew on 11/9/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GProj_AddRemoveMenu_h
#define GProj_AddRemoveMenu_h

class MenuSystem;
class Menu;

class AddRemoveMenu : public Menu {
    string _currentDirectory; 
    
public:
    AddRemoveMenu(MenuSystem *menuSystem, const string &currentDirectory = "");
    ~AddRemoveMenu();
    MenuSystem::MenuType menuType();
};

#endif
