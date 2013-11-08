//
//  FX3JSONBuilder.h
//
//  Created by Brent Rabowsky on 8/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef FX3JSONBuilder_h
#define FX3JSONBuilder_h


extern "C" {
	#include "../../Extern_Utils/cJSON.h"
}


#include "../../PIPELINE/FX3.h"
#include "FX3GLTree.h"
#include "FX3Shader.h"
#include "FX3GLLibrary.h"


typedef enum {

    FX3_JSON_HAS_NONE,
    FX3_JSON_HAS_VERTEX,
    FX3_JSON_HAS_FRAG,
    FX3_JSON_HAS_BOTH

} FX3JSONShaders;



class FX3JSONBuilder {

    
  private:
    
    cJSON * _root;
    cJSON * _nodes;
    int _numNodes;

	FX3GLTree * _tree;    
    char ** _shaderNames;
    
    char * _fragString;
    char * _vertString;
    
    bool _forPlugins;
    

  public:

    ~FX3JSONBuilder();
    FX3JSONBuilder();
 
 	// creation   
    void createJSONObjectFromString( char * jsonString, bool forPlugins );
    void createJSONObjectWithFile( char * fileName, bool forPlugins );
    cJSON * getNodes();
    
 	// builder types   
    void buildShadersForTree( FX3GLTree * tree );
    void buildPluginLibrary();
    
    // general methods
    void buildKnobs( FX3Shader * shader, cJSON * node );
    void buildKnobsOldSchema( FX3Shader * shader, cJSON * node );
    void linkInputs();
    void setExternalInput();
    void setExternalOutput();
    
    // helpers
    FX3JSONShaders checkForShaders( cJSON * node, char ** frag, char ** vert );
    FX3KnobType getKnobTypeEnum( char * type );
    
    
};



#endif
