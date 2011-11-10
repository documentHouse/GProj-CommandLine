//
//  MenuSystem.cpp
//  GProj
//
//  Created by Andrew on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//


#include "MenuSystem.h"
#include "Menu.h"
#include "LocationsMenu.h"
#include "sys/stat.h"

const string MenuSystem::LOCATIONS_FILE_NAME = "Locations.gproj";
const string MenuSystem::CONFIGURATION_FILE_NAME = "Config.gproj";
MenuSystem *MenuSystem::menuSystem = NULL;

MenuSystem *MenuSystem::sharedMenuSystem()
{
    if(menuSystem != NULL)
        return menuSystem;
    
    menuSystem = new MenuSystem;
    return menuSystem;
}

/*
string line;
while (!locationsFileIn->eof()) {
    getline(*locationsFileIn, line);
    cout << line << endl;
    }
*/
 
MenuSystem::MenuSystem()
{
    
    // Setup the file we write locations to
    locationsFileOut = new ofstream(LOCATIONS_FILE_NAME.c_str(),ios::in);
    
    if(locationsFileOut->fail())
    {
        cout << "Failed to open the following file for writing: " << LOCATIONS_FILE_NAME << endl;
        //mkdir("/Users/andrew/Library/Application Support/GProj",S_IFDIR);
    }
    
    // Setup the file we read locations from
    locationsFileIn = new ifstream(LOCATIONS_FILE_NAME.c_str());
    
    if(locationsFileIn->fail())
    {
        cout << "Failed to open the following file for reading: " << LOCATIONS_FILE_NAME << endl;
    }
    
    
    // Setup the file we write configuration data to
    configurationFileOut = new ofstream(CONFIGURATION_FILE_NAME.c_str(),ios::in);
    
    if(configurationFileOut->fail())
    {
        cout << "Failed to open the following file for writing: " << CONFIGURATION_FILE_NAME << endl;
    }
    
    
    // Setup the file we write configuration data to
    configurationFileIn = new ifstream(CONFIGURATION_FILE_NAME.c_str());
    
    if(configurationFileIn->fail())
    {
        cout << "Failed to open the following file for writing: " << CONFIGURATION_FILE_NAME << endl;
    }
     
    
    
    // Set up the initial menu for the user
    LocationsMenu *locationsMenu = new LocationsMenu(this);
    currentMenu = locationsMenu;
    menus.push_back(locationsMenu);
}

MenuSystem::~MenuSystem()
{
    // Destroy all the menus
    for(vector<Menu *>::iterator it = menus.begin(); it != menus.end(); it++)
        delete *it;
    
    locationsFileOut->close();
    delete locationsFileOut;
    
    locationsFileIn->close();
    delete locationsFileIn;
    
    configurationFileOut->close();
    delete configurationFileOut;
    
    configurationFileIn->close();
    delete configurationFileIn;
}


void MenuSystem::processingLoop()
{

    string input;
    MenuSignal signal;
    
    do {

        cout << ">> ";

        getline(cin, input);
        
        currentMenu->processInput(input);

        signal = currentMenu->signal();
        
        if(signal == PROCESS)
            ;
        else if(signal == CHANGE)
            ;
        else if(signal == KILL)
            printf("Exiting GProj...\n");
        
    } while (signal != KILL);
}

void MenuSystem::start()
{
    currentMenu->startInterface();
    
    // Testing the auto_ptr concept
    //auto_ptr<Menu> autoMenu(new LocationsMenu(this));
    
    this->processingLoop();
}

vector<string> MenuSystem::updateLocations()
{
    vector<string> locationsVector;
    
    if(locationsFileIn->bad())
        return locationsVector;
    else
    {
        string location;
        while (locationsFileIn->good()){
            getline(*locationsFileIn, location);
            // A newline or eof defines a string of length zero. We ignore these since
            // they can not be a valid directory
            if(location.length() != 0)
                locationsVector.push_back(location);
        }
        
        locationsFileIn->clear();
        locationsFileIn->seekg(0,ios::beg);
        
        return locationsVector;
    }
}

bool MenuSystem::storeLocations(vector<string> locations)
{
    if(locationsFileOut->bad()){
        cout << "The locations file could not be updated..." << endl;
        return false;
    }
    else{
        for(vector<string>::iterator it = locations.begin(); it != locations.end(); it++)
        {
            if(locationsFileOut->good())
                *locationsFileOut << *it;
            else
                return false;
        }
        return true;
    }
}
