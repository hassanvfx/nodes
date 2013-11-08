//
//  FX3GLTree.h
//  FXLab2
//
//  Created by hassan vfx on 05/08/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//

#ifndef FXLab2_FX3GLTree_h
#define FXLab2_FX3GLTree_h

#include "../FX3GL.h"
#include "../../PIPELINE/FX3Tree.h"
#include "FX3GLLibrary.h"

class FX3GLTree: public FX3Tree{
 
public:

	FX3Shader *_externalInput;
	FX3Shader *_externalOutput;
	FX3Shader *_externalCore;
	FX3Shader *_externalOverlay;

	FX3GLTree();
	~FX3GLTree();

    FX3Shader* createShader(char *className , char *fragment =NULL, char *vertex=NULL);
    FX3Shader* createShaderWithJSONName(char *className , char *fragment, char *vertex, char * jsonName );
    
    char * createNAMEfromJSONName(char * jsonName);

    void setExternalInput	(FX3Shader*);
    void setExternalOutput	(FX3Shader*);
    void setExternalCore	(FX3Shader*);
    void setExternalOverlay	(FX3Shader*);

    FX3Shader *externalInput();
    FX3Shader *externalOutput();
    FX3Shader *externalCore();
    FX3Shader *externalOverlay();
    
    void setTimeline ( FX3GLTimeline *);

};

#endif
