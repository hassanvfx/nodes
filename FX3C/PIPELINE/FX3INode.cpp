//
//  FX3INode.cpp
//  FX3C
//
//  Created by hassan vfx on 26/07/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//

#include "FX3INode.h"


#include "FX3.h"

#define LOG_TAG "FX3INode"

char* FX3INode:: builder(){
    return (char *)"FX3INode";
}

FX3INode::FX3INode() : FX3Node() {
    _knobs=NULL;
}

FX3INode::~FX3INode (){
   // if(this->_knobs != NULL){
      //  this->_knobs->releaseAll();
    //}
}

FX3Dictionary<char*, FX3Knob*> *FX3INode::knobs(){
    
    if(!this){
        return new FX3Dictionary<char*, FX3Knob*>( FX_KEYTYPE_CHARPTR );
    }
    
    if (this->_knobs==NULL) {
        this->_knobs = new FX3Dictionary<char*, FX3Knob*>( FX_KEYTYPE_CHARPTR );
    }
    return this->_knobs;
    
}


// INPUT HANDLING

void FX3INode:: addInputAtIndex(FX3Node *newNode,int index ){
    
    if(index < FX3_MAX_INPUTS ){
    
        //FX3Node *oldNode = this->_inputs[index];
        //decide what to do with the old node
        
        //assign new node
        this->_inputs[index] = newNode;
    
    } else{
        
        LOGI("error: addInputAtIndex beyond max inputs %d", FX3_MAX_INPUTS);
        
    }
}

void FX3INode:: addInput0( FX3Node * newNode){
    if(!this){
        return ;
    }
    this->addInputAtIndex( newNode, 0);
}
void FX3INode:: addInput1( FX3Node * newNode){
    if(!this){
        return ;
    }
    this->addInputAtIndex( newNode, 1);
}
void FX3INode:: addInput2( FX3Node * newNode){
    if(!this){
        return ;
    }
    this->addInputAtIndex( newNode, 2);
}

// KNOBS CREATION


FX3Knob *FX3INode::createKnob( char * n, int t){
  
	FX3Knob *knob = this->knobs()->lookup(n);

	if(knob == NULL ){
		knob = (FX3Knob *) this->createKnobFactory(n,t);
		 this->knobs()->insert(knob->_NAME, knob);
	} else{
		LOGE("reusing knob %s in %s", n , this->_NAME);
	}
	return knob;
}
void FX3INode::createKnob( char * n, int t, char * s){

	FX3Knob *knob = this->createKnob(n,t);
    knob->_string1=strdup( s);

}
void FX3INode::createKnob( char * n, int t, float v){

	FX3Knob *knob = this->createKnob(n,t);
    knob->_float1=v;
}
void FX3INode::createKnob( char * n, int t, float v1, float v2){

	FX3Knob *knob = this->createKnob(n,t);
    knob->_float1=v1;
    knob->_float2=v2;
}
void FX3INode::createKnob( char * n, int t, float v1, float v2, float v3){

	FX3Knob *knob = this->createKnob(n,t);
    knob->_float1=v1;
    knob->_float2=v2;
    knob->_float3=v3;
}
void FX3INode::createKnob( char * n, int t, float v1, float v2, float v3, float v4){

	FX3Knob *knob = this->createKnob(n,t);
    knob->_float1=v1;
    knob->_float2=v2;
    knob->_float3=v3;
    knob->_float4=v4;

}

void* FX3INode::createKnobFactory( char * n, int t){
	return new FX3Knob(n,t);
}

// KNOBS LOOKUP

FX3Knob *FX3INode::knob( char *n){
    
    return (FX3Knob *)this->knobs()->lookup(n);
}

// KNOBS MANAGING

void  FX3INode::setKnobToStringValue( char *name, char *s ){
    FX3Knob *knob=(FX3Knob *)this->knobs()->lookup(name);
    if(knob!=NULL)
    knob->_string1 = strdup(s);
}

void  FX3INode::setKnobToFloat1Value( char *name, float v){
    FX3Knob *knob=(FX3Knob *)this->knobs()->lookup(name);
    if(knob!=NULL)
    		knob->_float1 = v;
} 
void  FX3INode::setKnobToFloat2Value( char *name, float v){
    FX3Knob *knob=(FX3Knob *)this->knobs()->lookup(name);
    if(knob!=NULL)
    knob->_float2 = v;
} 
void  FX3INode::setKnobToFloat3Value( char *name, float v){
    FX3Knob *knob=(FX3Knob *)this->knobs()->lookup(name);
    if(knob!=NULL)
    knob->_float3 = v;
} 
void  FX3INode::setKnobToFloat4Value( char *name, float v){
    FX3Knob *knob=(FX3Knob *)this->knobs()->lookup(name);
    if(knob!=NULL)
    knob->_float4 = v;
} 

void  FX3INode::setKnobToFloat2DValue( char *name, float v1, float v2){
    FX3Knob *knob=(FX3Knob *)this->knobs()->lookup(name);
    if(knob!=NULL){
    knob->_float1 = v1;
    knob->_float2 = v2;}
}  
void  FX3INode::setKnobToFloat3DValue( char *name, float v1, float v2, float v3){
    FX3Knob *knob=(FX3Knob *)this->knobs()->lookup(name);
    if(knob!=NULL){
    knob->_float1 = v1;
    knob->_float2 = v2;
    knob->_float3 = v3;}
}  
void  FX3INode::setKnobToFloat4DValue( char *name, float v1, float v2, float v3, float v4){
    FX3Knob *knob=(FX3Knob *)this->knobs()->lookup(name);
    if(knob!=NULL){
    knob->_float1 = v1;
    knob->_float2 = v2;
    knob->_float3 = v3;
    knob->_float4 = v4;}
}  

void  FX3INode::setKnobToStringValue( FX3Knob* knob, char * s){  
    this->setKnobToStringValue( knob->_NAME, s);
}
void  FX3INode::setKnobToFloat1Value( FX3Knob* knob, float v){  
    this->setKnobToFloat1Value( knob->_NAME, v);
} 
void  FX3INode::setKnobToFloat2Value( FX3Knob* knob, float v){  
    this->setKnobToFloat2Value( knob->_NAME, v);
} 
void  FX3INode::setKnobToFloat3Value( FX3Knob* knob, float v){  
    this->setKnobToFloat3Value( knob->_NAME, v);
}  
void  FX3INode::setKnobToFloat4Value( FX3Knob* knob, float v){  
    this->setKnobToFloat4Value( knob->_NAME, v);
} 

void  FX3INode::setKnobToFloat2DValue( FX3Knob* knob, float v1, float v2){  
    
    this->setKnobToFloat1Value( knob->_NAME, v1);
    this->setKnobToFloat2Value( knob->_NAME, v2);
} 
 
void  FX3INode::setKnobToFloat3DValue( FX3Knob* knob, float v1, float v2, float v3){  
    
    this->setKnobToFloat1Value( knob->_NAME, v1);
    this->setKnobToFloat2Value( knob->_NAME, v2);
    this->setKnobToFloat3Value( knob->_NAME, v3);
} 
 
void  FX3INode::setKnobToFloat4DValue( FX3Knob* knob, float v1, float v2, float v3, float v4){ 
    
    this->setKnobToFloat1Value( knob->_NAME, v1);
    this->setKnobToFloat2Value( knob->_NAME, v2);
    this->setKnobToFloat3Value( knob->_NAME, v3);
    this->setKnobToFloat4Value( knob->_NAME, v4);
    
} 
 

