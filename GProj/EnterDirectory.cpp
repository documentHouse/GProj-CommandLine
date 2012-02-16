//
//  EnterDirectory.cpp
//  GProj
//
//  Created by Andrew Rickert on 2/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <sys/stat.h>
#include "MenuOption.h"
#include "EnterDirectory.h"

extern char **environ;
static const string prompt = "Enter an option or a directory path: ";

EnterDirectory::EnterDirectory(MenuSystem *menuSystem) : Menu(menuSystem)
{
    setOptions();
}

EnterDirectory::~EnterDirectory()
{
    
}

void EnterDirectory::setOptions()
{
    vector<MenuOption *> options;
    MenuOption *addRemoveOption = new MenuOption('a',"Add or Remove directories from locations",MenuSystem::ADDREMOVE);
    options.push_back(addRemoveOption);
    MenuOption *viewLocationOption = new MenuOption('l',"Choose a location",MenuSystem::LOCATION);
    options.push_back(viewLocationOption);
    MenuOption *returnAddNewOption = new MenuOption('r',"Return to actions for adding a new directory",MenuSystem::ADDNEWDIR);
    options.push_back(returnAddNewOption);
    MenuOption *exitOption = new MenuOption('e',"Exit the program.",MenuSystem::EXIT);
    options.push_back(exitOption); 
    
    Menu::setOptions(options);
}

bool EnterDirectory::setupDirectory(string directory)
{
    cout << endl << "Initialize the following directory for git: " << directory << endl;
    cout << "(y or n): ";
    
    string response;
    while (true)
    {
        getline(cin,response);
        if(response.length() != 1)
        {
            cout << "Invalid response. Please enter 'y' for yes or 'n' for no." << endl;
            cout << ">> ";
        }
        else
        {
            if (response[0] == 'y') {

                const char *currentDir = getenv("PWD");
                cout << "Setting up the git directory..." << endl;
                
                chdir(directory.c_str());
                
                system("git init");
                
                chdir(currentDir);
                
                return true;
            }
            else if(response[0] == 'n')
                return false;
            else
            {
                cout << "Invalid response. Please enter 'y' for yes or 'n' for no." << endl;
                cout << ">> ";
            }
        }
    }
}

void EnterDirectory::startInterface()
{
    Menu::startInterface();
    displayOptions();
    cout << endl << prompt << endl;
}

void EnterDirectory::displayMenu()
{
    clearScreen();
    displayOptions();
    cout << endl << prompt << endl;    
}

MenuSystem::MenuType EnterDirectory::menuType()
{
    return MenuSystem::ENTERDIR;
}

void EnterDirectory::processInput(string inputString)
{

    if(inputString.length() == 1)
    {
        // Holds the value entered by the user for this menu
        static char menuChoiceChar;
        
        // Holds whether the entered value is valid
        static bool isValidChar;
        
        isValidChar = validateChar(inputString, &menuChoiceChar);
        
        if(isValidChar)
        {
            if(Menu::isOption(menuChoiceChar))
            {
                MenuSystem::MenuType menuType = getOption(menuChoiceChar)->getValue();
                if(menuType == MenuSystem::EXIT)
                {
                    kill();
                }
                else
                {            
                    change(menuType);
                }
            }
            else
            {
                printInvalidAndProcess();
            }
        }
        else
        {
            printInvalidAndProcess();
        }

    }
    else{
            
        struct stat sb;
        if ( (stat(inputString.c_str(), &sb) == 0) && (S_ISDIR(sb.st_mode)) )
        {
            string directory(inputString);
            string gitDirectory;
            if(inputString[inputString.length()-1] == '/')
                gitDirectory = inputString.append(".git");
            else
                gitDirectory = inputString.append("/.git");

            // The .git directory exists so we have a valid git directory
            if ( (stat(gitDirectory.c_str(), &sb) == 0) && (S_ISDIR(sb.st_mode)) )
            {
                _menuSystem->addLocation(directory);
                cout << endl << "The following git directory has been added: " << directory << endl;
                cout << prompt << endl;
                process();
            }
            // The .git directory doesn't exist or isn't setup so ask the user
            else
            {
                
                if(setupDirectory(directory))
                    _menuSystem->addLocation(directory);
                
                displayMenu();
                
                process();
            }
        }
        else
        {
            cout << "The following directory is not valid: " << inputString << endl;
            process();
        }
    }
}