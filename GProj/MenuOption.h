//
//  MenuOption.h
//  GProj
//
//  Created by Andy on 11/9/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GProj_MenuOption_h
#define GProj_MenuOption_h

#include <string>
#include "MenuSystem.h"

class MenuOption {
    
    char _optionChar;
    string _optionString;
    MenuSystem::MenuType _optionValue;
public:
    MenuOption(char optionChar,string optionString,MenuSystem::MenuType optionValue);
    ~MenuOption();
    char getChar();
    string getString();
    MenuSystem::MenuType getValue();
};

#endif
