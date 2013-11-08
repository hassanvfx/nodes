//
//  FX3GLKnob.h
//  FXLab2
//
//  Created by hassanvfx on 7/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef FXLab2_FX3GLKnob_h
#define FXLab2_FX3GLKnob_h

#include "../FX3GL.h"
#include "../../PIPELINE/FX3Knob.h"



#if IS_ANDROID

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#if IS_IOS

#include <GLKit/GLKit.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#endif


class FX3GLKnob :public FX3Knob {
  
public:
   
    
    GLint uniformIndex;
    GLint attribIndex;
    float _lastFloat1;
    bool  _animate;
    float _animatedVal;
    
    static GLfloat data[];
   
    FX3GLKnob( char* _a , int bb)
    :FX3Knob( _a, bb)
    {
        uniformIndex=FX3_UNDEFINED;
        _lastFloat1=FX3_UNDEFINED;
        _animatedVal=FX3_UNDEFINED;
        
        _animate=false;
    };
};


#endif
