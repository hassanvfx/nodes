//
//  FX3Knob.cpp
//  FX3C
//
//  Created by hassan vfx on 26/07/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//


#include "FX3Knob.h"


#include "FX3.h"


#define LOG_TAG "FX3Knob"



FX3Knob::FX3Knob( char *name){  
    
   
    this->setCopyNAME(name);
   
    _string1 =NULL;
    _float1 = 0.0;
    _float2 = 0.0;
    _float3 = 0.0;
    _float4 = 0.0;

    _int1 = 0.0;
}

FX3Knob::~FX3Knob( ){
    if(_string1!=NULL){
        free(_string1);
    }
}


FX3Knob::FX3Knob( char *name, int type){  
    
    //ALLOC

    char* nextName = (char*)malloc(FX3_NAME_SIZE);
    strcpy(nextName,name);
    
    this->setCopyNAME(name);
    _type=(FX3KnobType)type;

    free(nextName);
    
}
