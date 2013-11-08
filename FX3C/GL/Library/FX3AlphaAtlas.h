//
//  FX3AlphaAtlas.h
//  FXLab2
//
//  Created by hassanvfx on 7/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef FXLab2_FX3AlphaAtlas_h
#define FXLab2_FX3AlphaAtlas_h

#include "../FX3GL.h"
#include "../Core/FX3Shader.h"
#include "../Core/FX3GeoUtils.h"

class FX3AlphaAtlas: public FX3Shader{

public:

	FX3Size originalSize;
    //FX3GLKnob *_width();
    //FX3GLKnob *_height();

    // overrides

    static char* builder();
    virtual void  setOutputsInfo();
   virtual char* vertexShader ();
  //  virtual void setOutputsInfo();


};;

#endif
