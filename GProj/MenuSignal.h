//
//  MenuSignal.h
//  GProj
//
//  Created by Andy on 10/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GProj_MenuSignal_h
#define GProj_MenuSignal_h

enum MenuSignal {
     WAITING, // A default state for menus when they aren't active
     PROCESS,
     CHANGE,
     KILL
};

typedef enum MenuSignal MenuSignal;

#endif
