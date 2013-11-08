//
//  FX3RenderBuffer.h
//  FXLab2
//
//  Created by hassan vfx on 05/08/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//

#ifndef FXLab2_FX3RenderBuffer_h
#define FXLab2_FX3RenderBuffer_h

#include "../FX3GL.h"
#include "FX3Generator.h"

class FX3RenderBuffer: public FX3Generator{
    
public:
    
    // overrides
    
    static char* builder();
    
    virtual void createOutputTexture();
    virtual int render(); // disable pipeline behavior
    virtual void renderBuffer(GLubyte *,
    								int width,
    								int height,
                              bool interpolate=false,
                              bool useMipmap=false,
                              GLint inFormat=GL_RGBA,
#if IS_ANDROID
                              GLint outFormat=GL_RGBA
#else
							  GLint outFormat=GL_BGRA
#endif
                              );
    
};;

#endif
