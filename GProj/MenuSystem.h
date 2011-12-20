//
//  MenuSystem.h
//  GProj
//
//  Created by Andrew on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//



#ifndef GProj_MenuSystem_h
#define GProj_MenuSystem_h

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

class Menu;

using namespace std;

class MenuSystem {
    
public:
    
    typedef enum MenuType{
        EXIT,
        LOCATION,
        ADDREMOVE,
        ADDNEWDIR,
        ADDCURRENTDIR,
        REMOVEDIR
    }MenuType;
    
    // Keys for Accessing the configuration file
    static const string CONFIGKEY_PREVIOUS;
    
    static MenuSystem *sharedMenuSystem();
    ~MenuSystem();
    
    // Load the initial interface through the first menu
    void start();
    
    // Get the locations from the locations file
    vector<string> updateLocations();
    map<string, string> updateConfigurations();
    
    // Store the updated set of locations
    bool storeLocations();
    
    // Store the updated configuration 
    bool storeConfigurations();
    
    // Handles add and deleting from the locations store in memory
    void addLocation(string newLocation);
    bool removeLocation(string location);
    bool shouldDoLocationUpdate();
    
    // Handles changing the configuration data
    void changePreviousLocation(string previousLocation);
    
    // Allows Menu Subclass to access global data from MenuSystem
    friend class Menu;

    
private:
    void changeMenu(MenuSystem::MenuType newMenu);
    
    // The only access to the singleton is through the sharedMenuSystem()
    // factory method.
    MenuSystem();
    MenuSystem(const MenuSystem &);
    MenuSystem &operator=(const MenuSystem &);
    
    void processingLoop();
    
    // Names a files which store the location and configuration
    // information for running the program
    static const string LOCATIONS_FILE_NAME;
    static const string CONFIGURATION_FILE_NAME;
    
    static const string STORAGE_PATH;
    
    // Get the initial set of locations from the file
    void loadLocations();
    
    // Get the set of configurations from the file
    void loadConfigurations();
    
    // Holds global data that each menu can set and
    // refer to.
    // StateValue is for illustration purposes
    int _StateValue;
    
    // Holds the current menu on the screen
    Menu *currentMenu;

    // Holds all of the menus that were initialized
    vector<Menu *> menus;
    
    static MenuSystem *menuSystem;

    // Handle whether we read or wrote from the file containing the locations of the
    // git projects
    bool isLocationsChanged;
    
    // Handle whether we read or wrote from the file containing the configuration data
    // for this application
    bool isConfigurationsChanged;
    
    map<int, bool> shouldUpdateLocations;
    
    vector<string> _locations;
    map<string, string> _configurations;
};


#endif
