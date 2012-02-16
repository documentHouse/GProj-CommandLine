//
//  EnterDirectory.h
//  GProj
//
//  Created by Andrew Rickert on 2/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef GProj_EnterDirectory_h
#define GProj_EnterDirectory_h

#include "Menu.h"

class MenuSystem;

class EnterDirectory : public Menu{

public:
    EnterDirectory(MenuSystem *menuSystem);
    ~EnterDirectory();
    
    void startInterface();
    void displayMenu();
    MenuSystem::MenuType menuType();
    void processInput(string inputString);
    
private:
    bool setupDirectory(string directory);
    void setOptions();
};


#endif
