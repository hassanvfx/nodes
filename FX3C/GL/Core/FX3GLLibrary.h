//
//  FX3GLLibrary.h
//  FXLab2
//
//  Created by hassan vfx on 05/08/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//

#ifndef FXLab2_FX3GLLibrary_h
#define FXLab2_FX3GLLibrary_h

#include "../FX3ShadersLibrary.h"
#include "../../PIPELINE/FX3Library.h"
#include "../../PIPELINE/FX3Dictionary.h"
#include "../Library/FX3Plugin.h"



class FX3GLLibrary : public FX3Library   {
public:
    
    
    static FX3GLLibrary *_shared;
    static FX3GLLibrary* shared();

    FX3Dictionary<char*, FX3Plugin*> *_plugins;
    FX3Dictionary<char*, FX3Plugin*> * plugins();
    virtual FX3Node*  makeNodeFactory(char *className);
    FX3Shader*  makeShader( char *className, char *fragment=NULL, char *vertex=NULL);
    FX3Shader*  makeShaderWithJSONName( char *className, char *fragment=NULL, char *vertex=NULL, char *jsonName=NULL);

    bool _libraryRegistered;
    void registerJSONLibrary( char * json );
};


#endif
