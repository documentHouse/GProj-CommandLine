//
//  MenuOption.cpp
//  GProj
//
//  Created by Andy on 11/9/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MenuOption.h"

MenuOption::MenuOption(char optionChar,string optionString,MenuSystem::MenuType optionValue)
{
    _optionChar = optionChar;
    _optionString = optionString;
    _optionValue = optionValue;
    //std::cout << "Creating menuOption: " << _optionChar << std::endl;
}

MenuOption::~MenuOption()
{
    //std::cout << "Destroying menuOption: " << _optionChar << std::endl;    
}

char MenuOption::getChar()
{
    return _optionChar;
}

string MenuOption::getString()
{
    return _optionString;
}

MenuSystem::MenuType MenuOption::getValue()
{
    return _optionValue;
}
