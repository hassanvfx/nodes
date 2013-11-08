//
//  FX3Object.h
//  FX3C
//
//  Created by hassanvfx on 7/28/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//

#ifndef FX3C_FX3Object_h
#define FX3C_FX3Object_h


#include "FX3Context.h"

class FX3Object{
    public:
    char *_NAME;
    int _ID;
    char*__ID;
    
    virtual void setCopyNAME( char *);   
    
    char * IDchar();
    int ID();
    
    
    ~FX3Object();
    FX3Object();
    
    void failWithError(NSString*dadescription,NSError *daerror);
};

#endif
