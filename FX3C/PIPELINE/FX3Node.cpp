//
//  FX3Node.cpp
//  FX3C
//
//  Created by hassan vfx on 26/07/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//



#include "FX3Node.h"


#include "FX3.h"


#define LOG_TAG "FX3Node"


char* FX3Node:: builder(){
    return (char *)"FX3Node";
}


FX3Node::FX3Node(){
   // _NAME=NULL;
    _requiredInputs =FX3_UNDEFINED;
    _useCache   =false;
    _wasBussy   =false;
    _isBussy    =false;;
    _flushASAP  =false;;
 
    
    for (int i=0; i<FX3_MAX_INPUTS; i++) {
         this->_inputs[i] =NULL ;
    }
    
}

FX3Node::FX3Node(int id){
    
   // _NAME=NULL;
    _requiredInputs =FX3_UNDEFINED;
    _useCache=false;
    
    
    for (int i=0; i<FX3_MAX_INPUTS; i++) {
        this->_inputs[i] =NULL ;
    }
}


FX3Node::~FX3Node(){
    
    //release knobs dictionary
    //_knobs
}

//rendering interface 

int FX3Node::render(){ 
    
    LOGI("FXLog: /\\  GOING UP STREAM %s\n",_NAME );
    
    this->doFinalOutput();
    
    LOGI("FXLog: \\/  RENDERING FINISHED %s\n",_NAME );
    
    this->lock();
    
    
    return _output;
}

//cache and engine management

void FX3Node::doFinalOutput(){
    
    LOGI("FXLog: /\\ doFinalOutput %s\n",_NAME );
    // cache enabled prevents to running rendering pipe
    
    if( ! this->_useCache ){
        
        LOGI("FXLog: /\\ will render new frame %s\n",_NAME );
        // call render in alll required inputs
        
        if ( this-> renderAllInputs() ) {
            
            
            LOGI("FXLog: \t[ ALL INPUTS READY ] %s\n",_NAME );
            LOGI("FXLog: \\/ RENDERING STARTED %s\n",_NAME );
            LOGI("FXLog:  \n\t\t { \n" );
        
            this->nowBussy();
            
            // run the rendering pipe
            this->preRenderEngine();

            this->linkAllInputs();
            this->renderEngine();
            this->postRenderEngine();
            
            this->notBussy();
            
            LOGI("FXLog:  \n\t\t } \n");
            LOGI("FXLog: \\/ ------ RENDERING FINISHED %s\n",_NAME );
            
           
            
            
            return;
        }
        
    } 
    
    LOGI("FXLog: \\/ nothing new to see in here reusing cache in %s\n",_NAME );
    
    return;
    
}


//linking

#if IS_ANDROID
bool FX3Node::renderAllInputs(){ 
    
    //users must define the required inputs to boost performance
    int max =_requiredInputs;
    
    //if not we will loop until max inputs
    if(_requiredInputs == FX3_UNDEFINED){
        max = FX3_MAX_INPUTS;
    }
    
    for (int i=0; i<max; i++) {
        FX3Node *input =  this->_inputs[i] ;
        
        if(input != NULL){
            
            LOGI("FXLog: /\\ request RENDER output from %s to -> %s\n",input->_NAME, this->_NAME );
            input->render();
            
        }
    }
    
    return true;
}
#else
bool FX3Node::renderAllInputs(){
    
    
    
    //users must define the required inputs to boost performance
    int max =_requiredInputs;
    
    //if not we will loop until max inputs
    if(_requiredInputs == FX3_UNDEFINED){
        max = FX3_MAX_INPUTS;
    }
    
    for (int i=0; i<max; i++) {
        FX3Node *input =  this->_inputs[i] ;
        
        if(!this){
            return 0;
        }
        
        if(input != NULL){
            
            LOGI("FXLog: /\\ request RENDER output from %s to -> %s\n",input->_NAME, this->_NAME );
            input->render();
            
        }
    }
    
    return true;
    
    
    /*
    
    //users must define the required inputs to boost performance
    int max =_requiredInputs;
    
    //if not we will loop until max inputs
    if(_requiredInputs == FX3_UNDEFINED){
        max = FX3_MAX_INPUTS;
    }
    //dispatch_queue_t queue =dispatch_queue_create(NULL, DISPATCH_QUEUE_CONCURRENT);
     dispatch_queue_t queue =dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0);
    
    dispatch_apply(max, queue, ^(size_t i) {
        
        FX3Node *input =  this->_inputs[i] ;
        
        if(input != NULL){
            
            LOGI("FXLog: /\\ request RENDER output from %s to -> %s\n",input->_NAME, this->_NAME );
            input->render();
            
        }
        
        
    });
    
    
    
    
    return true;*/
}

#endif

void FX3Node::linkAllInputs(){ 
    
    LOGI("FXLog:<> -> <> LINKING ALL REQUIRED INPUTS for %s\n", this->_NAME );
    
    
    //users must define the required inputs to boost performance
    int max =_requiredInputs;
    
    //if not we will loop until max inputs
    if(_requiredInputs == FX3_UNDEFINED){
        max = FX3_MAX_INPUTS;
    }
    
    for (int i=0; i<max; i++) {
        FX3Node *input =  this->_inputs[i] ;
        
        if(input != NULL){
            
             this->linkOutputInput(input, i);
            LOGI("FXLog:<%s> -> <%s> linked output\n",input->_NAME, this->_NAME );
            
        }
    }
    
}



void FX3Node::linkOutputInput(FX3Node*, int){
    
    
}

// RENDERING 


void FX3Node::preRenderEngine(){
     LOGI("FXLog: preRenderEngine > %s\n", _NAME );
    // buffer and memory setup check
    // display space clearing
    // viewportsetup
}
void FX3Node::renderEngine(){
    LOGI("FXLog: renderEngine > %s\n", _NAME );
   
    
}
void FX3Node::postRenderEngine(){
    LOGI("FXLog: postRenderEngine > %s\n", _NAME );
    
}


// CACHE MANAGEMENT


void FX3Node::unlock(){
    this->_useCache=false;
    
}
void FX3Node::lock(){
    this->_useCache=true;  
}

void FX3Node::nowBussy(){
    LOGI("FXLog:  bussy ignoring flush messages for now > %s\n",this->_NAME);
    
    this->_wasBussy  =this->_isBussy;
    this->_isBussy   =true;
    
    
}
void FX3Node::notBussy(){
    LOGI("FXLog:  not bussy and ready to flush messages > %s\n",this->_NAME);
    
 
    this->_isBussy   = this->_wasBussy;
  
    if( this->_flushASAP){
        LOGI("FXLog: \\/ ------ %s and in fact needs flush !! \n",_NAME ); 
        this->flushNow();  
        this->_flushASAP=false;
    }
    
}


void FX3Node::flushNow(){
    
    LOGI("FXLog:  < <<<  FLUSHING NOW signal to %s >>> > \n",_NAME );
    
}

// RESOURCES MANAGEMENT

void FX3Node::flush(){
    
    
    //RELEASE OUTPUT AND INTERNAL RESOURCES
 
    LOGI("FXLog:  < <<<  sending flush signal to %s >>> > \n",_NAME );
    
    if( !this->_isBussy){
        
        LOGI("FXLog:  <<<<  flush NOW  %s  >>>>\n",_NAME );
        
        
        this->flushNow();
        
    } else{
        //flush later
        //FXInode will call flush after current pipe is completed

        LOGI("FXLog:  <<<<  flush ASAP %s  >>>> \n",_NAME );
        this->_flushASAP=true;
    }
    
    //invalidate cache
    this->unlock();
    
}


//FX3Size FX3Node::getOutputSize(){ 
//    return FX3Size(0,0);
//}


void FX3Node::prepare(){
    
}



