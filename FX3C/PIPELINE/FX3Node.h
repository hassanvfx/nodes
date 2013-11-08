//
//  FX3Node.h
//  FX3C
//
//  Created by hassan vfx on 26/07/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//

#ifndef FX3C_FX3Node_h
#define FX3C_FX3Node_h

#include "FX3Object.h"
#include "FX3Constants.h"

class FX3Node:public FX3Object
{
    
public:  
    bool renderAllInputs();
    
    virtual void linkAllInputs();
    virtual void linkOutputInput(FX3Node*, int);
    
    virtual void doFinalOutput();
    virtual void preRenderEngine();
    virtual void renderEngine();
    virtual void postRenderEngine();
    
    
    
  
    int         _requiredInputs;
    
    FX3Node     *_inputs   [FX3_MAX_INPUTS];
 
    
    
    int         _output;
    bool        _useCache;
    
    //state
    bool _wasBussy;
    bool _isBussy;
    bool _flushASAP;
    
    //FX3Size     *_displaySize;
   //FX3Size     getOutputSize();
    
    
    FX3Node();
    FX3Node(int);
    ~FX3Node();
    
    
    static char* builder();
    
    virtual void flush();
    virtual void flushNow();
    
    virtual void unlock();
    virtual void lock();
   
    virtual int render();
    
    virtual void nowBussy();
    virtual void notBussy();
    
    virtual void prepare();

};


#endif
