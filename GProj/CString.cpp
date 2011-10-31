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

CString::CString() : cfstring(NULL)
{
    
}

CString::CString(CString &cString) : cfstring(cString.cfstring)
{
    CFRetain(cfstring);
}

CString::CString(CFStringRef foundationString) : cfstring(foundationString)
{
    CFRetain(cfstring);
}

CString::~CString()
{
    CFRelease(cfstring);
}

const char *CString::createCString()
{
    return CString::createCString(cfstring);
}

const char *CString::createCString(CFStringRef foundationString)
{
    size_t foundationStringSize = CFStringGetLength(foundationString);
    if(foundationStringSize > stringBufSize)
    {
        delete []stringBuf;
        stringBuf = new char[foundationStringSize + INITIAL_STRING_BUFFER_SIZE];
        stringBufSize = foundationStringSize + INITIAL_STRING_BUFFER_SIZE;
    }
    
    
    CFStringGetCString(foundationString, stringBuf, stringBufSize, kCFStringEncodingUTF8);
    
    size_t newCStringSize = strlen(stringBuf);
    
    char *newCString = new char[newCStringSize+1];
    
    strcpy(newCString, stringBuf);
    
    return newCString;
}

CString::operator const char*() const
{
    
    return NULL;
}



