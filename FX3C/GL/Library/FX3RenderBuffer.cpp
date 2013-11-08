//
//  FX3RenderBuffer.cpp
//  FXLab2
//
//  Created by hassan vfx on 05/08/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//



#include "FX3RenderBuffer.h"


#define LOG_TAG "FX3RenderBuffer"


char* FX3RenderBuffer:: builder(){
    return (char *)"FX3RenderBuffer";
}


int FX3RenderBuffer::render(){
    // disable pipelined behavior
    LOGI("FXLog: This shader overrides rendering pipe by external render buffer feed");
    return 0;
}


void FX3RenderBuffer::renderBuffer(GLubyte *bytes, 
                                   int width,
                                   int height,
                                   bool interpolate,
                                   bool useMipmap,
                                   GLint inFormat,
                                   GLint outFormat
                                   ){
    
	 
	 LOGI("FXLog: renderingToTexture from node = %s with size %d %d ", this->_NAME, width, height);



	 //verify if we have a top level smooth defition
	 FX3GLKnob *knobSmooth = 	( FX3GLKnob *)this->knobs()->lookup( kKnobSmooth );
	 if(knobSmooth != NULL){

		 float smooth =knobSmooth->_float1;
		 if(smooth >0.0){
			 LOGI("FXLog: overriding smooth mode for ", this->_NAME);
			 interpolate =true;
			 useMipmap = true;
		 }
	 }

    // prevent flush mesages
    this->nowBussy();
    // IMPLEMENT CUSTOM FEEDING IN HERE
    
    this->validateContext();
    // create an outputtexture
    this->outputTextureSize     = FX3Size(width,height);
    
    this->validateOutputTexture();
    
    this->lastOutputTextureSize = FX3Size(width,height);
    
  	if ( bytes == NULL ) {
  		LOGE("No further bytes in node = %s", this->_NAME );
  		this->notBussy();
    	this->lock();
  		return;
  	}
    
    // feed the pixelbuffer in the outputtexure
    GLubyte *imageData =  bytes;
    FX3GLContext::shared()->queueGL(^{
        
   
    glBindTexture(GL_TEXTURE_2D, outputTexture);
     
        
    if(! interpolate){
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
    } else {
        
        if (useMipmap)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            
        } else{
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            
        }
        
       // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    
  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    
    // download image bytes
    glTexImage2D(GL_TEXTURE_2D, 
                 0, 
                 inFormat, //GL_RGBA,  i.e.
                 (int)outputTextureSize.width,
                 (int)outputTextureSize.height,
                 0, 
                 outFormat, //GL_BGRA but GL_RGBA for Android
                 GL_UNSIGNED_BYTE, 
                 imageData
                 );
    
    if (useMipmap)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    
    //--glBindTexture(GL_TEXTURE_2D, 0);

     });
    // activate flush mesages
    this->notBussy();
    this->lock();
}


void FX3RenderBuffer::createOutputTexture(){
    //LOGI(@"recreating texture %s",this->_NAME );
#if IS_IOS
    //CVCache extension
   // this->createCVOutputTexture();
   // return;
#endif
    
   // this->deleteOutputTexture();
    
    //get the alias for outputtexture
    
    FX3GLContext::shared()->queueGL(^{
        FX3GLContext::shared()->genTexture( this->_NAME, &outputTexture);
        
        
        //link outputtexture alis to the last slot
        // glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, outputTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // This is necessary for non-power-of-two textures
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        
        //disable further parameter linking
        glBindTexture(GL_TEXTURE_2D, 0);
        
    });
    
}


