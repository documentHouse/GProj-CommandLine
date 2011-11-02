//
//  CString.h
//  GProj
//
//  Created by Andrew on 10/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GProj_CString_h
#define GProj_CString_h

#include <CoreFoundation/CoreFoundation.h>

class CString {
    
public:
    CString();
    CString(CString &cString);
    CString(CFStringRef foundationString);
    ~CString();
    static void show(CFStringRef foundationString);
    const char *createCString();
    static const char *createCString(CFStringRef foundationString);
    static const char *getCString(CFStringRef foundationString);
    operator const char *();
    
private:
    static void loadCStringBuf(CFStringRef foundationString);
    
    CFStringRef cfstring;
    static char *stringBuf;
    static size_t stringBufSize;

};


#endif
