//
//  FX3GLContext.h
//  FXLab2
//
//  Created by hassanvfx on 7/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef FXLab2_FX3GLContext_h
#define FXLab2_FX3GLContext_h


#include "../FX3GL.h"
#include "../../PIPELINE/FX3Dictionary.h"
#include <math.h>

#if IS_ANDROID
#include "FX3EGLSurface.h"
#else
#include <CoreMedia/CoreMedia.h>
#include "FX3GLTimeline.h"
#endif
class FX3GLResource {
    
public:
    GLuint *_name;
    char *_owner;
    char *_ID;
    
    FX3GLResource(  char *, GLuint *, char* ID);
    ~FX3GLResource();
};


class FX3GLContext {
    
    public:
    
    static FX3GLContext *_shared;
    static FX3GLContext *shared();
    
    
    static GLfloat vertexPosition[];
    static GLfloat vertexUV[];
    
    FX3GLContext();
    ~FX3GLContext();
   
    
    void activateContext();
    

    /*
     *
     *  GLOBAL KNOBS ACCESSORS AND STUFF
     *
     *
     */
/*
	FX3Dictionary<char *, FX3GLKnob*> *_globalKnobs;
	FX3Dictionary<char *, FX3GLKnob*> *globalKnobs();
	void updateGlobalKnobMix( float value );
	void makeGlobalKnobs();

	int _currentFrame;
	int getCurrentFrame();
	int nextFrame();
	int firstFrame();*/
    
    int getMediaOrientation();
    void setMediaOrientation(int);
    int _mediaOrientation;
    
	/*
	 *
	 * STATUS
	 *
	 */
/*
	bool isCanceled();
	bool _isCanceled;
	void cancel();*/
    
//resources management    
    
    FX3Dictionary<char *, FX3GLResource*> *_textures;
    FX3Dictionary<char *, FX3GLResource*> *_frameBuffers;
      
    
    void printResources();
    void printTextures();
    void printFrameBuffers();
    
    void genTexture(            char *KEY, GLuint *output );
    void genFrameBuffer(        char *KEY, GLuint *output);
    void genRenderBuffer(       char *KEY, GLuint *output);
   
    
    void deleteTexture(      GLuint *output);
    void deleteFrameBuffer(  GLuint *output);
    void deleteRenderBuffer( GLuint *output);
    
    void commonInit();
    void commonTearDown();

    typedef void (^FXBlock)(void);
#define FXSYNC  0
#define FXASYNC 1
    /*
     
        ENTER PLATFORM SPECIFIC CODE
     
     */
    
#if IS_MAC
    NSOpenGLContext *_context;
    NSOpenGLPixelFormat *_pixelFormat;
    
    //CVOpenGLTextureCacheRef coreVideoTextureCache;

    NSOpenGLContext *context();
    
#endif
    
    /*
     
     ENTER PLATFORM SPECIFIC CODE
     
     */
    
#if IS_IOS
    //--NSOpenGLContext *_context;
    
    EAGLContext *_context;
    EAGLContext *context();
    
    CVOpenGLESTextureCacheRef _glCVCache;
    CVOpenGLESTextureCacheRef glCVCache();
    
    dispatch_queue_t _contextQueue;
    dispatch_queue_t queue();
    
    
    dispatch_queue_t _loopQueue;
    dispatch_queue_t loopQueue();
    
    
    dispatch_queue_t _writerQueue;
    dispatch_queue_t writerQueue();
    
    dispatch_queue_t _visionQueue;
    dispatch_queue_t visionQueue();
    
    dispatch_queue_t _daemonQueue;
    dispatch_queue_t daemonQueue();
    
    dispatch_queue_t _cameraQueue;
    dispatch_queue_t cameraQueue();
    
    void queueGL    ( FXBlock block,  int mode=FXSYNC);
    void queueMain  ( FXBlock block,  int mode=FXSYNC);
    void queueLoop      ( FXBlock block,  int mode=FXSYNC);
    void queueWriter ( FXBlock block,  int mode=FXSYNC);
    void queueVision ( FXBlock block,  int mode=FXSYNC);
    void queueDaemon   ( FXBlock block,  int mode=FXSYNC);
    void queueCamera   ( FXBlock block,  int mode=FXSYNC);
    void clear();
    
    CFMutableDictionaryRef getCVCacheDescriptor();
    CFMutableDictionaryRef _CVCacheDescriptor;
    
     
    //delegates
    
    void didFinishWriter( void *);
    void didFailedWriting( void *);
    void didBeginMovie( void *);
    void didFinishMovie( void *);
    
    char *getContextName();
    void setContextName( char*);
    char *_contextName;
    
    bool _needsGLFinishWhenWriting;
    void setNeedsGLFinishWhenWriting(BOOL);
    
    bool _abortGLCommands;
#endif
    
    
    /*
     
     ENTER PLATFORM SPECIFIC CODE
     
     */
    
    
#if IS_ANDROID 

    void *_context;
    FX3EGLSurface * _eglSurface;
    
    void *context();
    void swapBuffers();
    void createBackgroundContext( int width, int height );
    
    
    void queueGL ( FXBlock block);
    
#endif
    
    float _lastPresentationDelay;
    void   setLastPresentationDelay(float delay);
    
};

#endif
