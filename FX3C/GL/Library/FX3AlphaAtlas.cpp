    //
//  FX3AlphaAtlas.cpp
//  FXLab2
//
//  Created by hassanvfx on 7/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include "FX3AlphaAtlas.h"



#define LOG_TAG "FX3AlphaAtlas"



char* FX3AlphaAtlas:: builder(){
    return (char *)"FX3AlphaAtlas";
}


/*

 EXTERNALSHADERS

 */

/*

 EXTERNALSHADERS

 */



char* FX3AlphaAtlas::vertexShader()
{

	return SHADER_STRING
	(

			attribute vec4 vertexPosition;
			attribute vec4 vertexUV;
			uniform mediump float knobIntensity;
			varying vec2 textureCoordinate;
			void main() {
				gl_Position = vertexPosition;
				textureCoordinate = vertexUV.xy;
				textureCoordinate.x = vertexUV.x*0.5;
				if(knobIntensity >= 0.5) {
					textureCoordinate.x = 0.5 + vertexUV.x*0.5;
				}

			}
	);

}


void  FX3AlphaAtlas::setOutputsInfo(){

	if ( this->_inputs[0] != NULL ) {

	    FX3Shader * input0 = (FX3Shader*)this->_inputs[0];
	    outputTextureSize = FX3Size(input0->outputTextureSize.width /2.0,input0->outputTextureSize.height);


	}


}

