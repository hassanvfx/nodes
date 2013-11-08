//
//  FX3Object.cpp
//  FX3C
//
//  Created by hassanvfx on 7/28/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//



#include "FX3Object.h"


#include "FX3.h"


#define LOG_TAG "FX3Object"


FX3Object::~FX3Object(){
    if(this->_NAME!=NULL){
        free(this->_NAME);
    }
    this->__ID=NULL;
    this->_ID=NULL;
}


char * FX3Object::IDchar(){
    
    if(this->__ID == NULL){
        this->__ID = (char*)malloc(4); 

        sprintf(this->__ID , "%d",_ID);
    }
    
    return __ID ;

}

int FX3Object::ID(){
    
    return this->_ID;
}

FX3Object::FX3Object(){
    this->_NAME=NULL;
    this->_ID= FX3Context::shared()->createID();
    
}

void FX3Object::setCopyNAME( char *name){

     //ALLOC
    
    char* nextName = (char*)malloc(strlen(name)+1); 
    strcpy ( nextName, name);

    this->_NAME =nextName;
}

void FX3Object::failWithError( NSString*dadescription,NSError *daerror){
    
    NSError*error=daerror;
    NSString*description=dadescription;
    NSDictionary*userInfo;
    
    if(!description){
        description= FX3_UNKNOWN_ERROR;
    }
  
    userInfo= [NSDictionary dictionaryWithObjectsAndKeys:description, FX3_ERROR_DECRIPTION, nil];

    if(!error){
        error=[NSError errorWithDomain:@"FX3_ENGINE" code:NSURLErrorCancelled userInfo:userInfo];
    }
    
    
    
    [[NSNotificationCenter defaultCenter] postNotificationName:FX3_GENERIC_ERROR object:error userInfo:userInfo];
    
    
}