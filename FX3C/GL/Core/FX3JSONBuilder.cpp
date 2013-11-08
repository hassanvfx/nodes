//
//  FX3JSONBuilder.cpp
//
//  Created by Brent Rabowsky on 8/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//





#include "FX3JSONBuilder.h"



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FX3CoreUtilities.h"
#include "../Library/FX3Plugin.h"


#define LOG_TAG "FX3JSONBuilder"




FX3JSONBuilder::~FX3JSONBuilder()
{
    if ( _root != NULL )
        cJSON_Delete(_root);
        
   	if ( _shaderNames != NULL )
		free( _shaderNames );
		
   	if ( _fragString != NULL )
		free( _fragString );

   	if ( _vertString != NULL )
		free( _vertString );
}


FX3JSONBuilder::FX3JSONBuilder()
{
    _root = NULL;
    _shaderNames = NULL;
    _fragString = NULL;
    _vertString = NULL;
    _forPlugins = false;
}


void FX3JSONBuilder::createJSONObjectFromString( char * jsonString, bool forPlugins )
{
	_forPlugins = forPlugins;

    _root = cJSON_Parse( jsonString );
 
    getNodes();
}


void FX3JSONBuilder::createJSONObjectWithFile( char * fileName, bool forPlugins )
{
	_forPlugins = forPlugins;

    FILE *f = fopen(fileName,"r");
    fseek(f,0,SEEK_END);
    long len = ftell(f);
    fseek(f,0,SEEK_SET);
    
	char *data = (char*)malloc(len+1);
    fread(data,1,len,f);
    fclose(f);

    _root = cJSON_Parse(data);
    free(data);
    
    getNodes();
}

cJSON * FX3JSONBuilder::getNodes()
{
	if ( _forPlugins )
		_nodes = cJSON_GetObjectItem(_root,"plugins");
	else
    	_nodes = cJSON_GetObjectItem(_root,"__nodes");
    _numNodes =	cJSON_GetArraySize(_nodes);
    LOGE("Number of nodes = %d", _numNodes);
    
    return _nodes;
}


void FX3JSONBuilder::buildPluginLibrary()
{

	FX3GLLibrary * lib = FX3GLLibrary::shared();
	FX3Plugin * plugin = NULL;

	// loop to build each plugin and its default knobs
	cJSON * node = _nodes->child;
	while( node )
	{
		plugin = new FX3Plugin();
		
		// fill in alias, builder, vertexShader, fragmentShader
		
		// get alias 
        cJSON * aliasItem = cJSON_GetObjectItem( node,"alias");
        char * alias = aliasItem->valuestring;
        plugin->setAlias( strdup(alias) );
        //---LOGI("Alias for plugin = %s", alias);
       // FX3Log(@"Alias for plugin = %s", alias);
	
		// get builder 
        cJSON * builderItem = cJSON_GetObjectItem( node,"builder");
        char * builder = builderItem->valuestring;
        plugin->setBuilder( strdup(builder) );
        //---LOGI("Builder for plugin = %s", builder);
       // FX3Log(@"Builder for plugin = %s", builder);
 
 		// set its shader strings, if any 

        //---LOGI("checking shader overrides for %s",alias);
 		char *frag = NULL, *vert = NULL;
 		FX3JSONShaders s = checkForShaders( node, &frag, &vert );
 		switch( s ) {
 			case FX3_JSON_HAS_FRAG: {

 		        //---LOGI("setting fragment for %s",alias);
 				plugin->setFragmentShader( frag );
 		        //---LOGI("setted fragment for %s",alias);
 				break;
 			}
  			case FX3_JSON_HAS_VERTEX: {
 		        //---LOGI("setting vertex for %s",alias);
 				plugin->setVertexShader( vert );
 		        //---LOGI("setting vertex for %s",alias);
 				break;
 			}
 			case FX3_JSON_HAS_BOTH: {
 		        //---LOGI("setting vtx & fragment for %s",alias);
 				plugin->setFragmentShader( frag );
 				plugin->setVertexShader( vert );
 		        //---LOGI("setting vtx &  fragment for %s",alias);
 				break;
                
             
                
 			}
            default:break;
 		}

 		 //---LOGI("preparing to build knobs for %s",alias);
        // add default knobs to plugin
        buildKnobs( plugin, node );
        
        //---LOGI("inserting  %s",alias);
        // insert plugin in the plugins library object
       lib->plugins()->insert(plugin->alias(), plugin);
		
		node = node->next;
		
	} // end while

}




void FX3JSONBuilder::buildShadersForTree( FX3GLTree * tree )
{
	_tree = tree;

	// create array of shader names/keys so can easily lookup which nodes were created
	if ( _shaderNames != NULL )
		free( _shaderNames );
	_shaderNames = (char**)malloc( sizeof(char*) * _numNodes );
	
	// loop to build each node and its knobs
	int i = 0;
	cJSON * node = _nodes->child;
	while( node )
	{
		// get builder 
        cJSON * builderItem = cJSON_GetObjectItem( node,"_builder");
        char * builder = builderItem->valuestring;
        //---LOGI("Builder for node = %s", builder);
        
        // get name of node, which includes its number, which will be used in overridden method of naming engine 
        cJSON * nameItem = cJSON_GetObjectItem( node,"_name");
        char * name = nameItem->valuestring;
        //---LOGI("Name for node = %s", name);
 
 		// actually create shader 
 		char *frag = NULL, *vert = NULL;
 		checkForShaders( node, &frag, &vert );
 		FX3Shader * shader =  (FX3Shader *)tree->createShaderWithJSONName( builder, frag, vert, name );   
        _shaderNames[i] = shader->_NAME;
        //---LOGI("Created new shader with name = %s", _shaderNames[i] );
        
        // add knobs to shader
        buildKnobs( shader, node );
		
		node = node->next;
		++i;
		
	} // end while

	
}


void FX3JSONBuilder::buildKnobs( FX3Shader * shader, cJSON * node )
{

	cJSON * knobsItem = cJSON_GetObjectItem( node,"knobs");

	if(knobsItem == NULL)
		return;

		cJSON * knobItem = knobsItem->child;  // array of knobs

		if ( knobItem == NULL )
			return;

		while ( knobItem )
		{
	
			// look inside knob: get name, type, and value
			char * kName;
			FX3KnobType kType;

			cJSON * knobNameItem = cJSON_GetObjectItem( knobItem,"knobName");
			kName = knobNameItem->valuestring;  // name in JSON corresponds to defined names exactly

			cJSON * knobTypeItem = cJSON_GetObjectItem( knobItem,"knobType");
			char * type = knobTypeItem->valuestring;
			kType = getKnobTypeEnum( type );
			//---LOGI("Knob name = %s, type = %s", kName, type);

			cJSON * knobValueItem = cJSON_GetObjectItem( knobItem,"knobValue");
			switch( kType )
			{
				case kKnobString:
				{
					char * value = "";
					if(knobValueItem!=NULL)
							value = knobValueItem->valuestring;
					//---LOGI("Knob name = %s, type = %s, value %s,", kName, type,value);
					shader->createKnob( kName, kType, strdup(value) );
					break;
				}
				case kKnobFloat1D:
				{
					double value = 0.0;

					if(knobValueItem!=NULL)
						value = knobValueItem->valuedouble;

					//---LOGI("Knob name = %s, type = %s, value %f,", kName, type,value);

					shader->createKnob( kName, kType, (float)value );
					break;
				}
                    default:
                    break;
			}

			knobItem = knobItem->next;
		}


}


void FX3JSONBuilder::buildKnobsOldSchema( FX3Shader * shader, cJSON * node )
{

	cJSON * knobsItem = cJSON_GetObjectItem( node,"knobs");
	cJSON * knobItem = knobsItem->child;  // "float" or "string" etc.
	
	while ( knobItem )
	{
		// first check if empty
		if ( knobItem->child == NULL ) {
			knobItem = knobItem->next;
			continue;
		}

		// look inside knob: get name, type, and value		
		char * kName;
		FX3KnobType kType;
		cJSON * knobActual = knobItem->child; // top level "knobIntensity" or "knobDuration" etc.
		
		cJSON * knobNameItem = cJSON_GetObjectItem( knobActual,"knobName");
        kName = knobNameItem->valuestring;  // name in JSON corresponds to defined names exactly
        
        cJSON * knobTypeItem = cJSON_GetObjectItem( knobActual,"knobType");
        char * type = knobTypeItem->valuestring;
        kType = getKnobTypeEnum( type );
        //---LOGI("Knob name = %s, type = %s", kName, type);
               
        cJSON * knobValueItem = cJSON_GetObjectItem( knobActual,"knobValue");
        switch( kType )
        {
        	case kKnobString:
        	{
        		char * value = knobValueItem->valuestring;
        		shader->createKnob( kName, kType, strdup(value) );
        		break;
        	}	
        	case kKnobFloat1D:
        	{
        		double value = knobValueItem->valuedouble;
        		shader->createKnob( kName, kType, value );
        		break;
        	}
                default:
                break;
        }
        	
		knobItem = knobItem->next;
	}

}


void FX3JSONBuilder::linkInputs()
{
	// loop to link each node to its inputs, if any
	cJSON * node = _nodes->child;
	int i = 0;
	while( node )
	{
		// get a reference to the current shader
		FX3Shader * current = (FX3Shader*)_tree->nodes()->lookup(_shaderNames[i]);
		
		// get inputs
        cJSON * inputItem = cJSON_GetObjectItem( node,"inputs");
        cJSON * input0Item = cJSON_GetObjectItem( inputItem,"input0");
        if ( !input0Item ) {  // no inputs for this node
        	node = node->next;
        	++i;
        	continue;
        }
        else {
        	char * inputName = input0Item->valuestring;
        	//---LOGI("Input 0 for node %s = %s", _shaderNames[i], inputName );
        	FX3Shader * input0 = (FX3Shader*)_tree->nodes()->lookup(inputName);
        	current->addInputAtIndex( input0, 0 );
        }
        
        // check for second input
        cJSON * input1Item = cJSON_GetObjectItem( inputItem,"input1");
        if ( input1Item ) {
        	char * inputName = input1Item->valuestring;
        	//---LOGI("Input 1 for node %s = %s", _shaderNames[i], inputName );
        	FX3Shader * input1 = (FX3Shader*)_tree->nodes()->lookup(inputName);
        	current->addInputAtIndex( input1, 1 );        
        }
        else {  // no inputs for this node
        	node = node->next;
        	++i;
        	continue;
        }
        
        // check for third input
        cJSON * input2Item = cJSON_GetObjectItem( inputItem,"input2");
        if ( input2Item ) {
        	char * inputName = input2Item->valuestring;
        	//---LOGI("Input 2 for node %s = %s", _shaderNames[i], inputName );
        	FX3Shader * input2 = (FX3Shader*)_tree->nodes()->lookup(inputName);
        	current->addInputAtIndex( input2, 2 );        
        }
        else {  // no inputs for this node
        	node = node->next;
        	++i;
        	continue;
        }
        
        // check for fourth input
        cJSON * input3Item = cJSON_GetObjectItem( inputItem,"input3");
        if ( input3Item ) {
        	char * inputName = input3Item->valuestring;
        	//---LOGI("Input 3 for node %s = %s", _shaderNames[i], inputName );
        	FX3Shader * input3 = (FX3Shader*)_tree->nodes()->lookup(inputName);
        	current->addInputAtIndex( input3, 3 );        
        }
        else {  // no inputs for this node
        	node = node->next;
        	++i;
        	continue;
        }
        
        // check for fifth input
        cJSON * input4Item = cJSON_GetObjectItem( inputItem,"input4");
        if ( input4Item ) {
        	char * inputName = input4Item->valuestring;
        	//---LOGI("Input 4 for node %s = %s", _shaderNames[i], inputName );
        	FX3Shader * input4 = (FX3Shader*)_tree->nodes()->lookup(inputName);
        	current->addInputAtIndex( input4, 4 );        
        }
		
		node = node->next;
		++i;
		
	} // end while
	 
}


void FX3JSONBuilder::setExternalInput()
{
	cJSON * inputItem = cJSON_GetObjectItem(_root,"__externalInput");
	char * input = inputItem->valuestring;
	//---LOGI("External input node = %s", input);
	FX3Shader * externalInput = (FX3Shader*)_tree->nodes()->lookup(input);
	if ( !externalInput ) {
		LOGE("External input node not found!");
		return;
	}
	_tree->setExternalInput(externalInput);
}


void FX3JSONBuilder::setExternalOutput()
{
	cJSON * outputItem = cJSON_GetObjectItem(_root,"__externalOutput");
	char * output = outputItem->valuestring;
	//---LOGI("External output node = %s", output);
	FX3Shader * externalOutput = (FX3Shader*)_tree->nodes()->lookup(output);
	if ( !externalOutput ) {
		LOGE("External output node not found!");
		return;
	}
	_tree->setExternalOutput(externalOutput);
}




// helpers ==================================================================


FX3JSONShaders FX3JSONBuilder::checkForShaders( cJSON * node, char ** frag, char ** vert )
{
    bool hasFrag = false;
    bool hasVert = false;
    char * jFrag = NULL;
    char * jVert = NULL;
    int shaderLen = 0;
    
	// get frag shader 
    cJSON * fragItem = cJSON_GetObjectItem( node,"fragment");
    if ( fragItem != NULL )
    {
	    jFrag = fragItem->valuestring;
	    if ( jFrag ) {
		    if ( _fragString != NULL )
		    	free( _fragString );
		    hasFrag = true;
		    shaderLen = strlen( jFrag ) * 3;
		    _fragString = (char *)malloc( sizeof(char) * shaderLen );
		    FX3CoreUtilities::URLDecode( _fragString, shaderLen, jFrag );
	    }
    }

	// get vertex shader 
    cJSON * vertItem = cJSON_GetObjectItem( node,"vertex");
    if ( vertItem != NULL )
    {
	    jVert = vertItem->valuestring;
	    if ( jVert ) {
		    if ( _vertString != NULL )
		    	free( _vertString );
		    hasVert = true;
		    shaderLen = strlen( jVert ) * 3;
		    _vertString = (char *)malloc( sizeof(char) * shaderLen );
		    FX3CoreUtilities::URLDecode( _vertString, shaderLen, jVert );
		}
	}
    
    // set output parameters    
    *frag = hasFrag ? strdup(_fragString) : NULL;
    *vert = hasVert ? strdup(_vertString) : NULL;
    
    // set return value
    if ( !hasFrag && !hasVert )
        return FX3_JSON_HAS_NONE;
    else if ( hasFrag && hasVert )
        return FX3_JSON_HAS_BOTH;
    else if ( hasFrag && !hasVert )
        return FX3_JSON_HAS_FRAG;
    else if ( !hasFrag && hasVert )
        return FX3_JSON_HAS_VERTEX;
    
    return FX3_JSON_HAS_NONE;
}


FX3KnobType FX3JSONBuilder::getKnobTypeEnum( char * type )
{
	if ( strcmp( type, "string" ) == 0 )
		return kKnobString;
	else if ( strcmp( type, "float" ) == 0 )
		return kKnobFloat1D;
    
    return kKnobString;
}















