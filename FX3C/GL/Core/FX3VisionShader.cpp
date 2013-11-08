//
//  FX3VisionShader.cpp
//  FX3Ctest
//
//  Created by hassanvfx on 17/10/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//
    #include "FX3VisionShader.h"

FX3VisionShader::FX3VisionShader(){
    
    for (int i=0; i<256; i++) {
        _lut1D[i]=(GLint)(i);
      //  _lutTone[i]=(GLint)(i);
    }
    _lut1D[256]=0;
    _lut1D[257]=255;
    _lut1D[258]=128;
    
    _newHistogram=true;
        
}






char* FX3VisionShader:: builder(){
    return (char *)"FX3VisionShader";
}

void FX3VisionShader::linkUniforms(){
    
    
	FX3Shader::linkUniforms();
    FX3GLContext::shared()->queueGL(^{
        _lut1DUniform   =  program->uniformIndex(kKnobLut1D );
        //_lutToneUniform =  program->uniformIndex(kKnobLutTone );
        
        
    });
}
void    FX3VisionShader::updateShaderKnobs(){
    
    
    FX3Shader::updateShaderKnobs();
    
    FX3GLContext::shared()->queueGL(^{
        if(_newHistogram){
            glUniform1iv(_lut1DUniform, 259, _lut1D);
            _newHistogram=false;
        }
    });
}

void FX3VisionShader::copyEqualizedHistogram( UInt8* histogram){
    
    for (int i=0; i<259; i++) {
      //  FX3Log(@"histogram %d > %d ",i,histogram[i] );
        _lut1D[i]=histogram[i];
        _newHistogram =true;
    }
    
    
    
   
}