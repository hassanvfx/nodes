//
//  FX3ShaderDemo.h
//  FX3Ctest
//
//  Created by hassanvfx on 04/10/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//

#ifndef __FX3Ctest__FX3ShaderDemo__
#define __FX3Ctest__FX3ShaderDemo__

#include "../Core/FX3Shader.h"

class FX3ShaderDemo: public FX3Shader{
    
public:
    virtual char* vertexShader   ();
    virtual char* fragmentShader ();
    static char *fragmentSoho();
    static char *fragmentNone();
    static char *fragmentCine();
    static char *fragmentRGBtoHSV();
    static char *fragmentMagic();
    static char *vertexScaleCenter();
    static char *fragmentRGBtoYUV();
    static char *fragmentRGBtoRGBY();
    static char *vertexDenoiser();
    static char *fragmentDenoiser();
    
    
    static char *vertexSharpener();
    static char *fragmentSharpener();
    
    static char * fragmentOverExposed();
    static char *fragmentSoftElegance();
    static char *fragmentHolga();
};

#endif /* defined(__FX3Ctest__FX3ShaderDemo__) */
