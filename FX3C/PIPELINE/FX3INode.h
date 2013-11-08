//
//  FX3INode.h
//  FX3C
//
//  Created by hassan vfx on 26/07/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//

#ifndef FX3C_FX3INode_h
#define FX3C_FX3INode_h

#include "FX3Constants.h"
#include "FX3Node.h"
#include "FX3Dictionary.h"
#include "FX3Knob.h"

class FX3INode: public FX3Node 
{
    
    private:
    
  
    FX3Dictionary<char*, FX3Knob*> *_knobs;
public:
    
    // overrides
    
    static char* builder();
    
     // body
    
    void addInputAtIndex( FX3Node *, int );
    void addInput0( FX3Node * );
    void addInput1( FX3Node * );
    void addInput2( FX3Node * );
    
    //knob creation

    virtual void* createKnobFactory( char * n, int t);
    FX3Knob* createKnob( char *, int);
    void createKnob( char *, int, char *);
    void createKnob( char *, int, float);
    void createKnob( char *, int, float, float);
    void createKnob( char *, int, float, float, float);
    void createKnob( char *, int, float, float, float, float);
    
    // knob lookup
    
    FX3Knob *knob( char *);
    
    // knobs SETTERS
    void setKnobToStringValue( char *, char * ); 
    
    void setKnobToFloat1Value( char *, float ); 
    void setKnobToFloat2Value( char *, float ); 
    void setKnobToFloat3Value( char *, float ); 
    void setKnobToFloat4Value( char *, float ); 
        
    void setKnobToFloat2DValue( char *, float, float ); 
    void setKnobToFloat3DValue( char *, float, float, float ); 
    void setKnobToFloat4DValue( char *, float, float, float, float ); 
 
    void setKnobToStringValue( FX3Knob*, char * ); 
    
    void setKnobToFloat1Value( FX3Knob*, float ); 
    void setKnobToFloat2Value( FX3Knob*, float ); 
    void setKnobToFloat3Value( FX3Knob*, float ); 
    void setKnobToFloat4Value( FX3Knob*, float ); 
  
    void setKnobToFloat2DValue( FX3Knob*, float, float ); 
    void setKnobToFloat3DValue( FX3Knob*, float, float, float ); 
    void setKnobToFloat4DValue( FX3Knob*, float, float, float, float ); 
    
    // knobs GETTERS
    
    FX3Dictionary<char*, FX3Knob*>   *knobs();
    
    FX3Knob* getKnobNamed( char *);
    
    FX3INode ();
    FX3INode(int);
    ~FX3INode ();
    
 
};


#endif
