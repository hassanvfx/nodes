//
//  FX3Knob.h
//  FX3C
//
//  Created by hassan vfx on 26/07/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//

#ifndef FX3C_FX3Knob_h
#define FX3C_FX3Knob_h

#include "FX3Object.h"
#include "FX3Constants.h"

struct FX3Knob:public FX3Object
{
public:
    
    FX3KnobType  _type;
      
    char *_string1;
    
    float _float1;
    float _float2;
    float _float3;
    float _float4;
    
    int _int1;
    
    
    FX3Knob();
    ~FX3Knob();
    FX3Knob( char*); //initwithname
    FX3Knob( char*, int); //initwithname
    
    
    
};


#endif
