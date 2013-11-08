//
//  FX3Library.h
//  FX3C
//
//  Created by hassanvfx on 7/28/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//

#ifndef FX3C_FX3Library_h
#define FX3C_FX3Library_h

#include "FX3Node.h"
#include "FX3INode.h"
#include "FX3Constants.h"



class FX3Library{


    
public:
  
    
    static FX3Library *_shared;
    static FX3Library* shared();
    
    
    virtual FX3Node*  makeNode(char *className);  
    virtual float version(); 
    
    
    FX3Library();
    ~FX3Library();
};


#endif
