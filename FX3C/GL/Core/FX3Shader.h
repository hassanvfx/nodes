//
//  FX3Shader.h
//  FXLab2
//
//  Created by hassanvfx on 7/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef FXLab2_FX3Shader_h
#define FXLab2_FX3Shader_h

#include "FX3GLContext.h"
#include "FX3GLProgram.h"
#include "../FX3GL.h"
#include "../../PIPELINE/FX3INode.h"
#include "FX3GLKnob.h"
#include "FX3GeoUtils.h"

#if IS_IOS
//addition to support corevideo link
#import <CoreVideo/CoreVideo.h>

#endif

class FX3Shader : public FX3INode {

    
    
public:
	//GLKnob

	   //knob creation

	 virtual void* createKnobFactory( char * n, int t);

    // overrides
    
    static char* builder();
    virtual void linkOutputInput(FX3Node*, int);
    virtual void preRenderEngine();
    virtual void renderEngine();
    virtual void postRenderEngine();
    virtual int render();
    virtual void unlock();
    //builders
    
    FX3Shader();
    ~FX3Shader();
    
    
    // handle the output texture pointer
    GLuint outputTexture;        
    GLuint outputTexture2; // YUV EXTENSION
    
    // handle the current shader framebuffer
    GLuint shaderFramebuffer; 
    
    
    // define the shader clearColor
    GLfloat backgroundColorRed, backgroundColorGreen, backgroundColorBlue, backgroundColorAlpha;
    
    //shader program
    FX3GLProgram *program;

    
    //this dictionary handles the current input pixel morphology info
  
    bool        _outputTextureSizeOverriden;
    FX3Size     inputTextureSize;
    FX3Size     outputTextureSize;
    FX3Size     lastOutputTextureSize;
    
    char        *_fragmentShader;
    char        *_vertexShader;
    
    //FX3Dictionary *knobsToUpdate;
    
    FX3GLKnob *knobCurrentFrame;
    FX3GLKnob *knobNoiseContinuos;
    FX3GLKnob *knobNoise;
    FX3GLKnob *knobOrientation;
    FX3GLKnob *knobMix;
    
    virtual void compileShader();
    virtual void createFromVertexAndFragment(char *, char *);
    virtual char* vertexShader   ();
    virtual char* fragmentShader ();

    virtual void setVertexShader	( char *);
    virtual void setFragmentShader	( char *);

    //virtual void grabUniforms(char *);
    
    virtual void addAttributes();
    virtual void linkUniforms();
    virtual void linkTextures();
    virtual void enableAttributes();
    virtual void feedAttributes();
    
    
    virtual void validateContext();
    virtual void setOutputsInfo();
    virtual void setOutputTextureSize(float width,float  height);
    virtual void getInputsInfo();
    
    virtual void validateShader();
    virtual void validateOutputTexture();
    virtual void validateFrameBuffer();
    virtual void validateSize();
    
    virtual void createShader();
    virtual void createOutputTexture();
    virtual void createFrameBuffer();
    
    virtual void deleteShader();
    virtual void deleteOutputTexture();
    virtual void deleteFrameBuffer();
    
    virtual void prepareShaderKnobs();
    virtual void updateShaderKnobs();
    
    virtual void activateViewport();
    virtual void activateFrameBuffer();
    virtual void clear();
    virtual void activateShader();
    virtual void draw();
    virtual void tearDown();
    virtual void stop();
    
    FX3GLTimeline *_timeline;
    FX3GLTimeline *timeline();
    void setTimeline(FX3GLTimeline *);
    
    
    
    
    /* managing external buffer feeding */
    
    //virtual void renderFromBuffer(char *);
    //virtual void renderFromTexture(GLuint);
    virtual void flushNow();
   // virtual bool renderAllInputs();
    
#if IS_IOS
    
    //CVCache Magic
    
    CVOpenGLESTextureCacheRef   _coreVideoTextureCache;
    CVPixelBufferRef        _videoCVBuffer;
    CVOpenGLESTextureRef    _videoCVTexture;
    
    void createCVOutputTexture();
    void deleteCVOutputTexture();
    
    FX3Shader *_videoCVPoolLink;
    CVPixelBufferPoolRef _videoCVPool;
    void linkToCVPixelBufferPool( FX3Shader *);
    void unlinkToCVPixelBbufferPool();
    
    virtual CVPixelBufferPoolRef getCVPixelBufferPool();
    bool isLinkedToCVPool();
    bool _isLinkedToCVPool;
    
    bool _enableCVPixelBuffer;
    void setEnableCVPixelBuffer(BOOL value);
#endif
};


#endif
