//
//  FX3Library.cpp
//  FX3C
//
//  Created by hassanvfx on 7/28/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//


#include "FX3Library.h"


#include "FX3.h"

#define LOG_TAG "FX3Library"

FX3Library *FX3Library::_shared=NULL; 

FX3Library * FX3Library::shared(){
    
    if(_shared == NULL){
        _shared= new FX3Library();
    }
    
    return _shared;
    
}

FX3Library::FX3Library(){
   
    
}

FX3Node* FX3Library::makeNode( char *className){

	// TODO:  replace this comparison with a strcmp or similar 
	// so won't crash for JSON serialization
    if(className == FX3Node::builder() ){
        return new FX3Node();
    }else  if(className == FX3INode::builder() ){
        return new FX3INode();
    }else{
       return new FX3Node();
    }

}
float FX3Library::version(){
    return 1.0;
}