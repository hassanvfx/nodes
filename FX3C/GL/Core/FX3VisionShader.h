//
//  FX3VisionShader.h
//  FX3Ctest
//
//  Created by hassanvfx on 17/10/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//

#ifndef __FX3Ctest__FX3VisionShader__
#define __FX3Ctest__FX3VisionShader__

#include "FX3Shader.h"

class FX3VisionShader: public FX3Shader{
    
    GLint _lut1DUniform;
    GLint _lut1D[259];
    bool _newHistogram;
    
   // GLint _lutToneUniform;
   // GLint _lutTone[256];
    
public:
    FX3VisionShader();
    
    static char* builder();
    //virtual char*vertexShader ();
    //virtual char* fragmentShader ();
    virtual void linkUniforms();
    virtual void  updateShaderKnobs();
    void copyEqualizedHistogram( UInt8*);
    
};

#endif /* defined(__FX3Ctest__FX3VisionShader__) */
