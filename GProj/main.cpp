//
//  main.cpp
//  GProj
//
//  Created by Andrew on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//


//: C15:Early.cpp
// Early binding & virtual functions
#include <iostream>
#include <string>
using namespace std;


/*
class Pet {
public:
    virtual string speak() const { return ""; }
};

class Dog : public Pet {
public:
    string speak() const { return "Bark!"; }
};

int main() {
    Dog ralph;
    Pet* p1 = &ralph;
    Pet& p2 = ralph;
    Pet p3;
    
    Pet *p;
    Dog *d = new Dog;
    p = d;
    p->speak();
    // Late binding for both:
    cout << "p1->speak() = " << p1->speak() <<endl;
    cout << "p2.speak() = " << p2.speak() << endl;
    // Early binding (probably):
    cout << "p3.speak() = " << p3.speak() << endl;
} ///:~
*/


#include <iostream>
#include <string>
#include "MenuSystem.h"
using namespace std;

void usageStatement();
int main (int argc, const char * argv[])
{

    if(argc == 1)
    {
        cout << "Executing command line gproj" << endl;
        MenuSystem *menuSystem = MenuSystem::sharedMenuSystem();
        menuSystem->start();
    
    }
    else if (argc == 2)
    {
        const char *guiString = "gui";
        if(strncmp(argv[1], guiString, strlen(guiString)) == 0)
            cout << "Executing gui gproj" << endl;
        else
            usageStatement();
    }
    else
        usageStatement();
    
    return 0;
}

void usageStatement()
{
    cout << "Usage: gproj [gui]" << endl;
}
