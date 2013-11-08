//
//  FX3CIFilter.h
//  FX3Ctest
//
//  Created by hassanvfx on 11/10/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//

#ifndef __FX3Ctest__FX3CIFilter__
#define __FX3Ctest__FX3CIFilter__

#include "FX3Shader.h"

#include <CoreImage/CoreImage.h>
#include <ImageIO/ImageIO.h>

class FX3CIFilter:public FX3Shader {
    
    
public:
    
    virtual int render();
    static char* builder();
    
    
    bool _linkToOutputTexture;
    bool linkToInputTexture();
    
    void renderCoreImage();
};

#endif /* defined(__FX3Ctest__FX3CIFilter__) */
