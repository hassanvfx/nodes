//
//  FX3Solid.h
//  FXLab2
//
//  Created by hassanvfx on 7/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef FXLab2_FX3Solid_h
#define FXLab2_FX3Solid_h

#include "../FX3GL.h"
#include "FX3Generator.h"

class FX3Solid: public FX3Generator{
    
public:
    
    //FX3GLKnob *_width();
    //FX3GLKnob *_height();
    
    // overrides
    
    static char* builder();
    
    virtual char* fragmentShader ();
  //  virtual void setOutputsInfo();

    
};;

#endif
