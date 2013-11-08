//
//  FX3Tree.cpp
//  FX3C
//
//  Created by hassanvfx on 7/28/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//


#include "FX3Tree.h"


#include "FX3.h"


#define LOG_TAG "FX3Tree"


FX3Tree::FX3Tree(){
    _nextNode=0;   

    _nodes=NULL;


}

FX3Tree::~FX3Tree(){
    _nextNode=0;
    if(this->_nodes != NULL){
        this->_nodes->releaseAll();
    }

    _nodes=NULL;
}


FX3Dictionary<char *,FX3Node*> *FX3Tree::nodes(){
    if (this->_nodes==NULL) {
        this->_nodes = new FX3Dictionary<char *,FX3Node*>(FX_KEYTYPE_CHARPTR);
    }
    return this->_nodes;
    
}



char * FX3Tree::createNAME(char *className){
    
    char* nextName = (char*)malloc(strlen(className)+2); 
    sprintf(nextName, "%s%d", className,_nextNode);
    
    return nextName;
    
}

FX3Node* FX3Tree::createNode(char *className){
    if(_nextNode>=FX3_MAX_DICTIONARY_ITEMS){
        LOGI("FXLog: Error cannot create FX3 reached max nodes");
        return NULL;
    }
    //ALLOC
    
    //allocate fresh memory for the new keys
    char    *nextName = this->createNAME(className);
    FX3Node *next   = this->makeNode(className);
    
    next->setCopyNAME(nextName);
    
    free(nextName);
    
    this->nodes()->insert( next->_NAME,next);
    _nextNode+=1;
    
    LOGI("FXLog: Created node type %s name %s \n",className,nextName);
    
    return next;
    
}

FX3Node* FX3Tree::makeNode( char* className){
    return FX3Library::shared()->makeNode(className);;
}

void FX3Tree::prepareAllNodes(){
    
    FX3TableEntry< char *, FX3Node*> **entries = this->nodes()->getEntries();
    
    for (int i = 0; i <  this->nodes()->getCount() ; ++i) {
        
        FX3TableEntry< char *, FX3Node*> *item = entries[i];
        FX3Node * node = (FX3Node *)item->value;
        
        node->prepare();
        
    }
    
    delete [] entries;
}

void FX3Tree::restartAllNodes(){
    
}

void FX3Tree::cancelAllNodes(){
    
}
void FX3Tree::flushAllNodes(){
    
    if(this->_nodes==NULL)
        return;
    
    FX3TableEntry< char *, FX3Node*> **entries = this->nodes()->getEntries();
    
    for (int i = 0; i <  this->nodes()->getCount() ; ++i) {
        
        FX3TableEntry< char *, FX3Node*> *item = entries[i];
        FX3Node * node = (FX3Node *)item->value;
        
        node->flush();
        
    }
    
    delete [] entries;
}
void FX3Tree::cleanUpAllNodes(){
    
}

void FX3Tree::unlockAllNodes(){
    
   
    FX3TableEntry< char *, FX3Node*> **entries = this->nodes()->getEntries();
    
    for (int i = 0; i <  this->nodes()->getCount() ; ++i) {
        
        FX3TableEntry< char *, FX3Node*> *item = entries[i];
        FX3Node * node = (FX3Node *)item->value;
        if(node!=NULL)
        node->unlock();
        
    }
    
    delete [] entries;
}

void FX3Tree::getProcessTimeAllNodes(){
    
}
