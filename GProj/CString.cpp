//
//  CString.cpp
//  GProj
//
//  Created by Andrew on 10/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CString.h"

#define INITIAL_STRING_BUFFER_SIZE 1000

char *CString::stringBuf = new char[INITIAL_STRING_BUFFER_SIZE];
size_t CString::stringBufSize = INITIAL_STRING_BUFFER_SIZE;

CString::CString()
{
    
}

CString::CString(CString &cString)
{
    
}

CString::CString(CFStringRef foundationString)
{
    
}

const char *CString::createCString()
{
    
    return NULL;
}

const char *CString::createCString(CFStringRef foundationString)
{
    size_t foundationStringSize = CFStringGetLength(foundationString);
    if(foundationStringSize > stringBufSize)
    {
        delete []stringBuf;
        stringBuf = new char[foundationStringSize + INITIAL_STRING_BUFFER_SIZE];
        stringBufSize = foundationStringSize;
    }
    
    char *newCString = new char[found]
    
    return NULL;
}

CString::operator const char*() const
{
    
    return NULL;
}



