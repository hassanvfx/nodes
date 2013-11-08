//
//  FX3Plugin.h
//  FX3C
//
//  Created by hassan vfx on 26/07/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//

#ifndef FX3C_FX3Plugin_h
#define FX3C_FX3Plugin_h

#include "../Core/FX3Shader.h"
#include "../../PIPELINE/FX3Dictionary.h"



class FX3Plugin :public FX3Shader
{

  private:
  
    char * _alias;
    char * _builder;
  

public:

    //FX3PluginType  _type;

    FX3Plugin();
    ~FX3Plugin();
    
    // accessors
    char * alias();
    char * builder();
    void setAlias( char * a );
    void setBuilder( char * b );


};


#endif
