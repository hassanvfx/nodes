//
//  FX3GLTree.cpp
//  FXLab2
//
//  Created by hassan vfx on 05/08/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//



#include "FX3GLTree.h"

FX3GLTree::FX3GLTree(){

	this->_externalInput  = NULL;
	this->_externalOutput = NULL;
    this->_externalCore   = NULL;

}

FX3GLTree::~FX3GLTree(){


    //this ensures to call dealloc method at the fx3shader level
    // by forcing the typecasting
    
    if (this->_nodes!=NULL) {
        
   
    
    int total = this->_nodes->getCount();

    FX3TableEntry< char *, FX3Node*> **entries = this->_nodes->getEntries();

    for (int i = 0; i <  total; ++i) {

        FX3TableEntry< char *, FX3Node*> *item = entries[i];
        FX3Shader * resource = (FX3Shader *)item->value;

        LOGI("FXLog: deleting node %s", resource->_NAME );

        delete resource;

    }

    delete entries;
    delete this->_nodes;
    _nodes=NULL;
        
         }


}



FX3Shader* FX3GLTree::createShader(char *className , char *fragment, char *vertex){

	if(_nextNode>=FX3_MAX_DICTIONARY_ITEMS){
	        LOGI("FXLog: Error cannot create FX3 reached max nodes");
	        return new FX3Shader(); //TODO handle error;
	    }
	    //ALLOC

	    //allocate fresh memory for the new keys
	    char    *nextName 	= this->createNAME(className);
	    FX3Shader *next   	= FX3GLLibrary::shared()->makeShader(className, fragment, vertex);

	    next->setCopyNAME(nextName);

	    this->nodes()->insert( next->_NAME,next);
	    _nextNode += 1;

	    LOGI("FXLog: Created node type %s name %s \n",className,nextName);
	        
	    free(nextName);

	    return next;

}


FX3Shader* FX3GLTree::createShaderWithJSONName(char *className , char *fragment, char *vertex, char * jsonName ){

	if(_nextNode>=FX3_MAX_DICTIONARY_ITEMS){
	        LOGI("FXLog: Error cannot create FX3 reached max nodes");
	        return new FX3Shader(); //TODO handle error;
	    }
	    //ALLOC

	    //allocate fresh memory for the new keys
	    char    *nextName 	= this->createNAMEfromJSONName( jsonName );
	    FX3Shader *next   	= FX3GLLibrary::shared()->makeShaderWithJSONName(className, fragment, vertex, jsonName);

	    next->setCopyNAME(nextName);

	    this->nodes()->insert( next->_NAME,next);
	    _nextNode += 1;

	    LOGI("FXLog: Created node type %s name %s \n",className,nextName);
	    
	    free(nextName);

	    return next;

}


char * FX3GLTree::createNAMEfromJSONName( char * jsonName)
{
    char * nextName = strdup( jsonName ); 

    return nextName;
}



void FX3GLTree::setExternalInput(FX3Shader*shader){

	this->_externalInput = shader;

}

void FX3GLTree::setExternalOutput(FX3Shader*shader){

	this->_externalOutput = shader;

}
void FX3GLTree::setExternalCore(FX3Shader*shader){
    
	this->_externalCore= shader;
    
}

void FX3GLTree::setExternalOverlay	(FX3Shader*shader){
    this->_externalOverlay= shader;
}

FX3Shader *FX3GLTree::externalInput(){
	return this->_externalInput;
}
FX3Shader *FX3GLTree::externalOutput(){
	return this->_externalOutput;

}

FX3Shader *FX3GLTree::externalCore(){
	return this->_externalCore;
    
}
FX3Shader *FX3GLTree::externalOverlay(){
	return this->_externalOverlay;
    
}
//


void FX3GLTree::setTimeline ( FX3GLTimeline *newContext) {
   
        
        FX3TableEntry< char *, FX3Node*> **entries = this->nodes()->getEntries();
        
        for (int i = 0; i <  this->nodes()->getCount() ; ++i) {
            
            FX3TableEntry< char *, FX3Node*> *item = entries[i];
            FX3Shader * node = (FX3Shader *)item->value;
            
            node->setTimeline(newContext);
            
        }
        
        delete [] entries;

    
}

