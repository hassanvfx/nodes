//
//  FX3Tree.h
//  FX3C
//
//  Created by hassanvfx on 7/28/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//

#ifndef FX3C_FX3Tree_h
#define FX3C_FX3Tree_h

#include "FX3Constants.h"
#include "FX3Node.h"
#include "FX3Library.h"
#include "FX3Dictionary.h"

class FX3Tree
{
    
public:
    

    FX3Dictionary<char*, FX3Node*> *_nodes;
    FX3Dictionary<char*, FX3Node*>   *nodes();
    
    int     _nextNode;
    
    FX3Tree();
    FX3Tree(char *name,float libver);
    ~FX3Tree();
    
    FX3Node* createNode(char *className);
  
    virtual FX3Node* makeNode(char *className);
    
    char * createNAME(char *className);
    
    void prepareAllNodes();
    void restartAllNodes();
 
    void cancelAllNodes();
    void flushAllNodes();
    void cleanUpAllNodes();
    
    void unlockAllNodes();
   
    void getProcessTimeAllNodes();
};

#endif
