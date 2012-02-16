//
//  MenuSystem.cpp
//  GProj
//
//  Created by Andrew on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <sys/stat.h>
#include <errno.h>
#include "MenuSystem.h"
#include "Menu.h"
#include "LocationsMenu.h"
#include "AddRemoveMenu.h"
#include "AddNew.h"
#include "AddCurrent.h"
#include "Remove.h"
#include "EnterDirectory.h"
#include "AddEnteredDirectory.h"

// Note: the mkdir call below failed because /Users/andrew/ didn't exist,
// You should check for the existence of a path to /Library/Application\ Support before
// you try to write, if it doesn't exist then you
//const string MenuSystem::STORAGE_PATH = "/Users/andrew/gprojFiles";
const string MenuSystem::STORAGE_PATH = "/Users/andy/gprojFiles";
const string MenuSystem::LOCATIONS_FILE_NAME = "Locations.gproj";
const string MenuSystem::CONFIGURATION_FILE_NAME = "Config.gproj";
const string MenuSystem::CONFIGKEY_PREVIOUS = "previous";
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

    shouldUpdateLocations[LOCATION] = true;
    shouldUpdateLocations[REMOVEDIR] = true;
    
    isLocationsChanged = false;
    loadLocations();
    
    isConfigurationsChanged = false;
    loadConfigurations();
    
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
            changeMenu(currentMenu->changeMenuType());
        else// if(signal == KILL)
            ;
        
    } while (signal != KILL);
    
    if(isLocationsChanged)
        storeLocations();
    
    if(isConfigurationsChanged)
        storeConfigurations();
}

void MenuSystem::start()
{
    updateConfigurations();
    
    currentMenu->startInterface();
    
    // Testing the auto_ptr concept
    //auto_ptr<Menu> autoMenu(new LocationsMenu(this));
    
    this->processingLoop();
}

bool MenuSystem::setupDirectory(string directoryLocation)
{
    struct stat sb;
    
    if ( (stat(directoryLocation.c_str(), &sb) == 0) && (S_ISDIR(sb.st_mode)) )
        return true;
    else
    {
        if(mkdir(directoryLocation.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) == 0)
            return true;
        else
        {
            cout << "Directory could not be created..." << endl;
            cout << "Error: " << strerror(errno) << endl;
            return false;
        }
    }
}

void MenuSystem::loadLocations()
{
    
    string storePath(STORAGE_PATH);
    string locationDirectory = storePath.append("/").append(LOCATIONS_FILE_NAME);
    if(setupDirectory(STORAGE_PATH))
    {
        ifstream locationsFileIn(locationDirectory.c_str());
        if(locationsFileIn.good())
        {
            string location;
            while (locationsFileIn.good()){
                getline(locationsFileIn, location);
                // A newline or eof defines a string of length zero. We ignore these since
                // they can not be a valid directory
                if(location.length() != 0)
                    _locations.push_back(location);
            }
            
            locationsFileIn.clear();
            locationsFileIn.close();
        }
        else
            locationsFileIn.close();
    }
    else
    {
        cout << "Couldn't do shit..." << endl;
    }
}

void MenuSystem::loadConfigurations()
{    

    string storePath = STORAGE_PATH;
    string configurationDirectory = storePath.append("/").append(CONFIGURATION_FILE_NAME);
    if(setupDirectory(STORAGE_PATH))
    {
        ifstream configurationFileIn(configurationDirectory.c_str());
        if(configurationFileIn.good())
        {
            cout << "configurationFileIn" << endl;
            string configString;
            unsigned long position;
            string key;
            string value;
            while(configurationFileIn.good())
            {
                getline(configurationFileIn, configString);
                
                if(configString.length() != 0)
                {
                    // key and value pairs are seperated by an equal sign
                    // like the following "previous=/Users/andrew"
                    position = configString.find("=");
                    
                    key = configString.substr(0,position);
                    value = configString.substr(position+1);
                    
                    _configurations[key] = value;
                }
            }
            
            configurationFileIn.clear();
            configurationFileIn.close();

        }
        else
            configurationFileIn.close();
    }
    else
    {
        cout << "Still couldn't do shit..." << endl;
    }
    
}


vector<string> MenuSystem::updateLocations()
{
    shouldUpdateLocations[currentMenu->menuType()] = false;
    return _locations;
}

map<string, string> MenuSystem::updateConfigurations()
{
    isConfigurationsChanged = false;
    return _configurations;
}

void MenuSystem::changeMenu(MenuSystem::MenuType newMenu)
{
    if(newMenu != currentMenu->menuType())
    {
        bool foundMenuType = false;
        
        // Look for the menu we want to change to, if it exists then start it
        for(vector<Menu *>::iterator it = menus.begin(); it != menus.end(); it++)
            if( (*it)->menuType() == newMenu )
            {
                foundMenuType = true;
                currentMenu = *it;
                currentMenu->startInterface();
            }

        // This menu does not currently exist. Create it, add it to the menu list and start it
        if(!foundMenuType)
        {
            Menu *newMenuType;
            if(newMenu == ADDREMOVE)
            {
                cout << "We need to create and start the Add-Remove menu and start it" << endl;
                AddRemoveMenu *addremoveMenu = new AddRemoveMenu(this);
                newMenuType = addremoveMenu;
            }
            else if(newMenu == ADDNEWDIR)
            {
                cout << "We need to create and start the Add New Directory menu and start it" << endl;
                AddNew *addnew = new AddNew(this);
                newMenuType = addnew;
            }
            else if(newMenu == ADDCURRENTDIR)
            {
                cout << "We need to create and start the Add Current Directory menu and start it" << endl;
                AddCurrent *addcurrent = new AddCurrent(this);
                newMenuType = addcurrent;
            }
            else if(newMenu == REMOVEDIR)
            {
                cout << "We need to create and start the Remove Directory menu and start it" << endl;
                Remove *remove = new Remove(this);
                newMenuType = remove;
            }
            else if(newMenu == ENTERDIR)
            {
                cout << "We need to create and start the Remove Directory menu and start it" << endl;
                EnterDirectory *enterDirectory = new EnterDirectory(this);
                newMenuType = enterDirectory;
            }
            else if(newMenu == ADDENTERED)
            {
                cout << "We need to create and start the Remove Directory menu and start it" << endl;
                AddEnteredDirectory *enteredDirectory = new AddEnteredDirectory(this," ");
                newMenuType = enteredDirectory;
            }

            
            menus.push_back(newMenuType);
            currentMenu = newMenuType;
            currentMenu->startInterface();
        }
    }
    else
        cout << "This menu is currently running..." << endl;
    
}

void MenuSystem::addLocation(string newLocation)
{
    _locations.push_back(newLocation);
    isLocationsChanged = true;

    for(map<int, bool>::iterator it = shouldUpdateLocations.begin(); it != shouldUpdateLocations.end(); it++)
        it->second = true;
}

bool MenuSystem::removeLocation(string location)
{
    for(vector<string>::iterator it = _locations.begin(); it != _locations.end(); it++)
        if(location.compare(*it) == 0)
        {
            _locations.erase(it);
            isLocationsChanged = true;

            for(map<int, bool>::iterator it = shouldUpdateLocations.begin(); it != shouldUpdateLocations.end(); it++)
                it->second = true;

            return true;
        }
    
    return false;
}

bool MenuSystem::shouldDoLocationUpdate()
{
    return shouldUpdateLocations[currentMenu->menuType()];
}


void MenuSystem::changePreviousLocation(string previousLocation)
{
    isConfigurationsChanged = true;
    _configurations[CONFIGKEY_PREVIOUS] = previousLocation;
}

bool MenuSystem::storeLocations()
{
    // Setup the file we write locations to
    string storePath = STORAGE_PATH;
    string locationFile = storePath.append("/").append(LOCATIONS_FILE_NAME);
    ofstream locationsFileOut(locationFile.c_str());
    
    if(locationsFileOut.fail())
    {
        locationsFileOut.close();
        cout << "Failed to open the following file for writing: " << LOCATIONS_FILE_NAME << endl;
        return false;
    }
    
    for(vector<string>::iterator it = _locations.begin(); it != _locations.end(); it++)
        locationsFileOut << *it << endl;    
    
    locationsFileOut.close();
    
    return true;
}


bool MenuSystem::storeConfigurations()
{
    // Setup the file we write configuration data to
    string storePath = STORAGE_PATH;
    string configurationFile = storePath.append("/").append(CONFIGURATION_FILE_NAME);
    ofstream configurationFileOut(configurationFile.c_str());

    if(configurationFileOut.fail())
    {

        configurationFileOut.close();
        cout << "Failed to open the following file for writing: " << CONFIGURATION_FILE_NAME << endl;
        return false;
    }
    
    for(map<string, string>::iterator it = _configurations.begin(); it != _configurations.end(); it++)
        configurationFileOut << it->first << "=" << it->second << endl;
    
    configurationFileOut.close();
    
    return true;
}
