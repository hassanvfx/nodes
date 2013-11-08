//
//  FX3Context.cpp
//  FXLab2
//
//  Created by hassanvfx on 8/7/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//



#include "FX3Context.h"


#include "FX3.h"

#define LOG_TAG "FX3Context"


FX3Context *FX3Context::_shared=NULL; 

FX3Context * FX3Context::shared(){
    
    if(_shared == NULL){
        _shared= new FX3Context();
    }
    
    return _shared;
    
}


FX3Context::FX3Context(){
    _objectsCount=0;
}

int FX3Context::createID(){
    
    ++_objectsCount;
    
    return _objectsCount;

}
