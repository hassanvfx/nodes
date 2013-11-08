    //
//  FX3Solid.cpp
//  FXLab2
//
//  Created by hassanvfx on 7/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include "FX3Solid.h"

char* FX3Solid:: builder(){
    return (char *)"FX3Solid";
}


/*
 
 EXTERNALSHADERS 
 
 */




char* FX3Solid::fragmentShader()
{
    
    return SHADER_STRING
    (
     
     varying mediump vec2 textureCoordinate;
 		uniform mediump float knobRed;
 		uniform mediump float knobGreen;
 		uniform mediump float knobBlue;
     
     void main()
     {
         
         
          gl_FragColor = vec4(knobRed,knobGreen,knobBlue,1.0);
         
     }
     );
    
}

/*
void  FX3Solid::setOutputsInfo(){
    
    this->outputTextureSize = FX3Size(300,300);
    
}*/

