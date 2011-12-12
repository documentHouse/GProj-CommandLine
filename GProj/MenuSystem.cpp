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
#include "AddRemoveMenu.h"
#include "AddNew.h"
#include "AddCurrent.h"
#include "Remove.h"
#include "sys/stat.h"

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
    // Setup the file we read locations from
    locationsFileIn = new ifstream(LOCATIONS_FILE_NAME.c_str());
    
    if(locationsFileIn->fail())
    {
        cout << "Failed to open the following file for reading: " << LOCATIONS_FILE_NAME << endl;
    }
    
    // Setup the file we write configuration data to
    configurationFileIn = new ifstream(CONFIGURATION_FILE_NAME.c_str());
    
    if(configurationFileIn->fail())
    {
        cout << "Failed to open the following file for writing: " << CONFIGURATION_FILE_NAME << endl;
    }

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
        
    locationsFileIn->close();
    delete locationsFileIn;
    
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

void MenuSystem::loadLocations()
{
    if(locationsFileIn->good())
    {
        string location;
        while (locationsFileIn->good()){
            getline(*locationsFileIn, location);
            // A newline or eof defines a string of length zero. We ignore these since
            // they can not be a valid directory
            //cout << "Location: " << location << endl;
            if(location.length() != 0)
                _locations.push_back(location);
        }
        
        locationsFileIn->clear();
        locationsFileIn->seekg(0,ios::beg);
    }
    
}

void MenuSystem::loadConfigurations()
{    
    if(configurationFileIn->good())
    {
        string configString;
        unsigned long position;
        string key;
        string value;
        while(configurationFileIn->good())
        {
            getline(*configurationFileIn, configString);
            
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
        
        configurationFileIn->clear();
        configurationFileIn->seekg(0,ios::beg);
        
        // Print the key-values parsed from the file
        for(map<string,string>::iterator it = _configurations.begin(); it != _configurations.end(); it++)
            cout << "Key: " << it->first << " -- Value: " << it->second << endl;
    }

}


vector<string> MenuSystem::updateLocations()
{
    shouldUpdateLocations[currentMenu->menuType()] = false;
    return _locations;
}

map<string, string> MenuSystem::updateConfigurations()
{
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
                cout << "We need to create and start the Add Current Directory menu and start it" << endl;
                Remove *remove = new Remove(this);
                newMenuType = remove;
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
    cout << "changePreviousLocation" << endl;
    cout << "previousLocation: " << previousLocation << endl;    
}

bool MenuSystem::storeLocations()
{
    
    // Setup the file we write locations to
    locationsFileOut = new ofstream(LOCATIONS_FILE_NAME.c_str());
    
    if(locationsFileOut->fail())
    {
        locationsFileOut->close();
        delete locationsFileOut;
        cout << "Failed to open the following file for writing: " << LOCATIONS_FILE_NAME << endl;
        return false;
    }
    
    for(vector<string>::iterator it = _locations.begin(); it != _locations.end(); it++)
        *locationsFileOut << *it << endl;
    
    locationsFileOut->close();
    delete locationsFileOut;
    
    return true;
    
}


bool MenuSystem::storeConfigurations()
{
    cout << "storeConfigurations" << endl;
    // Setup the file we write configuration data to
    configurationFileOut = new ofstream(CONFIGURATION_FILE_NAME.c_str());
    
    if(configurationFileOut->fail())
    {
        configurationFileOut->close();
        delete configurationFileOut;
        cout << "Failed to open the following file for writing: " << CONFIGURATION_FILE_NAME << endl;
        return false;
    }
    //else
    //    cout << "The file: " << CONFIGURATION_FILE_NAME << " is open for writing"  << endl;
    
    for(map<string, string>::iterator it = _configurations.begin(); it != _configurations.end(); it++)
    {
        cout << "Writing key: " << it->first << "  value: " << it->second << endl;
        //*configurationFileOut << it->first << "=" << it->second << endl;
        if(configurationFileOut->good())
            *configurationFileOut << "previous=/Users/andrew/Documents" << endl;
        else
            cout << "There was a problem writing to the configuration file." << endl;
    }
    
    configurationFileOut->close();
    delete configurationFileOut;
    
    return true;
}
