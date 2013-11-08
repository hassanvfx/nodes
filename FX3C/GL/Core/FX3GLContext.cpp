    //
//  FX3GLContext.cpp
//  FXLab2
//
//  Created by hassanvfx on 7/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//



#include "FX3GLContext.h"

#pragma mark singleton accessor

/*
 
 FX3 GL Resource
 
 */

FX3GLResource:: FX3GLResource(  char *owner, GLuint *pointer,char* ID) {
    
    this->_name     = pointer;
    this->_owner    = strdup(owner);
    this->_ID       = ID;
    
    
}

FX3GLResource::~FX3GLResource() {
 
    free( this->_owner);
    free( this->_ID);
}



void FX3GLContext::genTexture(  char *owner, GLuint *output){
    
    glGenTextures(1, output);
    
   /* char* THEKEY = (char*)malloc(12);
    sprintf(THEKEY , "%u",*output);

    FX3GLResource *resource = new FX3GLResource( owner,output,THEKEY);
    _textures->insert( THEKEY,resource);*/
    
    
    
    
}


void FX3GLContext::genFrameBuffer(  char *owner, GLuint *output){
    
     glGenFramebuffers(1, output);
    
    /*char* THEKEY = (char*)malloc(12);
    sprintf(THEKEY , "%u",*output);
    
    FX3GLResource *resource = new FX3GLResource( owner,output,THEKEY);
    _frameBuffers->insert( THEKEY,resource);*/
    
 
    
}
void FX3GLContext::genRenderBuffer(  char *KEY, GLuint *output){
    
}

// delete

void FX3GLContext::deleteTexture(      GLuint *output){
    
    
    /*/char* THEKEY = (char*)malloc(12);
    sprintf(THEKEY , "%d",*output);
    
    FX3GLResource *resource = _textures->lookup (THEKEY);
    _textures->remove (THEKEY);
    
    delete resource;*/
    
    glDeleteTextures(1, output);
    
}
void FX3GLContext::deleteFrameBuffer(  GLuint *output){
    
    
   /* char* THEKEY = (char*)malloc(12);
    sprintf(THEKEY , "%d",*output);
    
    FX3GLResource *resource = _frameBuffers->lookup (THEKEY);
    _frameBuffers->remove (THEKEY);
    delete resource;*/
    
    glDeleteFramebuffers(1, output);
    
}
void FX3GLContext::deleteRenderBuffer( GLuint *output){
    
}

void FX3GLContext::printResources(){
    
    LOGI("FXLog: \n");
    LOGI("FXLog: ------------------------- \n");
    LOGI("FXLog: ------ GL Resources ----- \n");
    
    this->printTextures();
    this->printFrameBuffers();
    
    LOGI("FXLog: ------------------------- \n");
    LOGI("FXLog: \n");
}
void FX3GLContext::printTextures(){
    
#if IS_ANDROID
    LOGI("FXLog: ----- Textures (%d)\n",_textures->getCount());
    
    FX3TableEntry< char *, FX3GLResource*> **entries = this->_textures->getEntries();
    
    for (int i = 0; i <  this->_textures->getCount() ; ++i) {
        
        FX3TableEntry< char *, FX3GLResource*> *item = entries[i];

        FX3GLResource * resource = (FX3GLResource *)item->value;
        
        LOGI("FXLog: GLTexture %d owned by %s\n", *resource->_name , resource->_owner );

    }
#endif
}
void FX3GLContext::printFrameBuffers(){
    
#if IS_ANDROID
    LOGI("FXLog: ----- Framebuffers (%d)\n",_textures->getCount());
    
    FX3TableEntry< char *, FX3GLResource*> **entries = this->_textures->getEntries();
    
    for (int i = 0; i <  this->_textures->getCount() ; ++i) {
        
        FX3TableEntry< char *, FX3GLResource*> *item = entries[i];
        FX3GLResource * resource = (FX3GLResource *)item->value;
        
        LOGI("FXLog: GLFrameBuffer %d owned by %s\n", *resource->_name , resource->_owner );
        
    }
#endif  
}



/*
 
 FX3 GL Context
 
 */

FX3GLContext *FX3GLContext::_shared=NULL;

GLfloat FX3GLContext::vertexPosition[] = {
    -1.0f,  -1.0f,
    1.0f, -1.0f,
    -1.0f,  1.0f,
    1.0f, 1.0f,
    
};



GLfloat FX3GLContext::vertexUV[] = {
    0.0,	0.0,
    1.0,	0.0,
    0.0,1.0,
    1.0,	1.0,   
    
};

FX3GLContext * FX3GLContext::shared(){
    
    if(_shared == NULL){
        _shared= new FX3GLContext();
        _shared->setContextName("shared");
    }
    
    return _shared;
    
}


void  FX3GLContext::clear(){

    
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
    
}

int FX3GLContext::getMediaOrientation(){
    
    return _mediaOrientation;
}
void FX3GLContext::setMediaOrientation(int neworient){
    
    _mediaOrientation = neworient;
    
}


#if IS_MAC
#pragma mark - OSX SPECIFIC CODE

FX3GLContext::FX3GLContext(){
    
    
    
	GLuint attributes[] =
    {
        NSOpenGLPFAWindow,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFADoubleBuffer,
        //NSOpenGLPFAColorSize,24,
        // NSOpenGLPFAAlphaSize,8,
        //NSOpenGLPFADepthSize,24,
        //NSOpenGLPFAMinimumPolicy,
        0
        
    };
    
    _pixelFormat = [[ NSOpenGLPixelFormat alloc] initWithAttributes: (NSOpenGLPixelFormatAttribute *) attributes ];
    
    if( _pixelFormat == nil){
        FX3Log(@"cannot create pixel format ");
    }
    
    _context = [ [ NSOpenGLContext alloc] 
                initWithFormat: _pixelFormat shareContext:nil];
    
    // resource management
    
    _textures       = new FX3Dictionary < char * , FX3GLResource *> (FX_KEYTYPE_CHARPTR);
    _frameBuffers   = new FX3Dictionary < char * , FX3GLResource *> (FX_KEYTYPE_CHARPTR);
    
   
    
}



FX3GLContext::~FX3GLContext(){
    
}



// member accessors

NSOpenGLContext * FX3GLContext::context(){
    return _context;
}

void FX3GLContext::activateContext(){
    
    [_context makeCurrentContext];
}

#endif



#if IS_IOS
#pragma mark - IOS SPECIFIC CODE
//--- builders

FX3GLContext::FX3GLContext(){
    
    this->commonInit();
    _glCVCache=nil;
    _context=nil;
    _contextQueue = nil;
    _CVCacheDescriptor =nil;
    _loopQueue=nil;
    _writerQueue=nil;
    _contextName=nil;
    _daemonQueue=nil;

    _visionQueue=nil;
    queue();
    loopQueue() ;
    writerQueue();
    visionQueue();
    daemonQueue();
    cameraQueue();
    _abortGLCommands=NO;
    
    _needsGLFinishWhenWriting=false;
}
FX3GLContext::~FX3GLContext(){
    
    this->commonTearDown();
    _context=nil;
}



void FX3GLContext::setContextName( char*name){
    this->_contextName = strdup(name);
}
char *FX3GLContext::getContextName(){
    if(this->_contextName ==nil){
        this->_contextName = "live";
    }
    return this->_contextName;
}

dispatch_queue_t FX3GLContext::queue(){
    if(_contextQueue==nil){
        NSString *queueName = [NSString stringWithFormat:@"com.viddy.fx3c.openglqueue"];
        _contextQueue = dispatch_queue_create([queueName UTF8String], DISPATCH_QUEUE_SERIAL);
        
       // dispatch_queue_t high = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH,NULL);
        
       // dispatch_set_target_queue(_contextQueue,high);
    }
    return _contextQueue;
}

dispatch_queue_t FX3GLContext::loopQueue(){
    if(_loopQueue==nil){
      
        NSString *queueName = [NSString stringWithFormat:@"com.viddy.fx3c.%s.loopqueue",this->getContextName()];
        _loopQueue = dispatch_queue_create([queueName UTF8String], DISPATCH_QUEUE_SERIAL);
      
        
        // dispatch_queue_t high = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH,NULL);
        
        // dispatch_set_target_queue(_contextQueue,high);
    }
    return _loopQueue;
}


dispatch_queue_t FX3GLContext::writerQueue(){
    if(_writerQueue==nil){
        
        NSString *queueName = [NSString stringWithFormat:@"com.viddy.fx3c.%s.writerqueue",this->getContextName()];
        
        _writerQueue = dispatch_queue_create([queueName UTF8String], DISPATCH_QUEUE_SERIAL);
        // dispatch_queue_t high = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH,NULL);
        
        // dispatch_set_target_queue(_contextQueue,high);
    }
    return _writerQueue;
}




dispatch_queue_t FX3GLContext::visionQueue(){
    if(_visionQueue==nil){
        
        NSString *queueName = [NSString stringWithFormat:@"com.viddy.fx3c.%s.visionqueue",this->getContextName()];
        
        _visionQueue = dispatch_queue_create([queueName UTF8String], DISPATCH_QUEUE_SERIAL);
        
    }
    return _visionQueue;
}

dispatch_queue_t FX3GLContext::daemonQueue(){
    if(_daemonQueue==nil){
        
        NSString *queueName = [NSString stringWithFormat:@"com.viddy.fx3c.%s.daemonqueue",this->getContextName()];
        
        _daemonQueue = dispatch_queue_create([queueName UTF8String], DISPATCH_QUEUE_SERIAL);
        
    }
    return _daemonQueue;
}

dispatch_queue_t FX3GLContext::cameraQueue(){
    
    if(_cameraQueue==nil){
        
        NSString *queueName = [NSString stringWithFormat:@"com.viddy.fx3c.%s.cameraqueue",this->getContextName()];
        
        _cameraQueue = dispatch_queue_create([queueName UTF8String], DISPATCH_QUEUE_SERIAL);
        
    }
    return _cameraQueue;
}

void FX3GLContext::queueMain ( FXBlock block, int mode){
   
    if(mode == FXSYNC){
        
        if ([NSThread isMainThread] )
        {
            block();
        }
        else
        {
            dispatch_sync(dispatch_get_main_queue(), block);
        }
    } else{
        
        dispatch_async(dispatch_get_main_queue(), block);
        
    }
}


void FX3GLContext::queueGL ( FXBlock block, int mode){
   
      // block();
    //return;
    //dispatch_queue_t videoProcessingQueue = this->queue();
    
   
    
    if(mode == FXSYNC){

        if (dispatch_get_current_queue() == _contextQueue)
        {
            block();
        }
        else
        {
            dispatch_sync(_contextQueue, block);
        }
    } else{
        
        dispatch_async(_contextQueue, block);
        
    }
   

}



void FX3GLContext::queueLoop ( FXBlock block, int mode){
    
    // block();
    //return;
    //dispatch_queue_t videoProcessingQueue = this->queue();
    
    if(mode == FXSYNC){
        
        if (dispatch_get_current_queue() == _loopQueue || [[NSThread currentThread] isMainThread])
        {
            block();
        }
        else
        {
            dispatch_sync(_loopQueue, block);
        }
    } else{
        
        dispatch_async(_loopQueue, block);
        
    }
    
    
}



void FX3GLContext::queueWriter ( FXBlock block, int mode){
    
    // block();
    //return;
    //dispatch_queue_t videoProcessingQueue = this->queue();
    
    if(mode == FXSYNC){
        
        if (dispatch_get_current_queue() == _writerQueue  || [[NSThread currentThread] isMainThread])
        {
            block();
        }
        else
        {
            dispatch_sync(_writerQueue, block);
        }
    } else{
        
        dispatch_async(_writerQueue, block);
        
    }
    
    
}



void FX3GLContext::queueVision ( FXBlock block, int mode){
    
    // block();
    //return;
    //dispatch_queue_t videoProcessingQueue = this->queue();
    
    if(mode == FXSYNC){
        
        if (dispatch_get_current_queue() == _visionQueue  || [[NSThread currentThread] isMainThread])
        {
            block();
        }
        else
        {
            dispatch_sync(_visionQueue, block);
        }
    } else{
        
        dispatch_async(_visionQueue, block);
        
    }
    
}



void FX3GLContext::queueDaemon ( FXBlock block, int mode){
    
    // block();
    //return;
    //dispatch_queue_t videoProcessingQueue = this->queue();
    
    if(mode == FXSYNC){
        
        if (dispatch_get_current_queue() == _daemonQueue)
        {
            block();
        }
        else
        {
            dispatch_sync(_daemonQueue, block);
        }
    } else{
        
        dispatch_async(_daemonQueue, block);
        
    }
    
}



void FX3GLContext::queueCamera ( FXBlock block, int mode){
    
    // block();
    //return;
    //dispatch_queue_t videoProcessingQueue = this->queue();
    
  
    dispatch_queue_t queue = this->cameraQueue();
    
    if(mode == FXSYNC){
        
        if (dispatch_get_current_queue() == queue)
        {
            block();
        }
        else
        {
            dispatch_sync(queue, block);
        }
    } else{
        
        dispatch_async(queue, block);
        
    }
    
}



EAGLContext *FX3GLContext::context(){
    
    if (_context == nil)
    {
        _context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
       if(_context==nil)
//        FX3Log( @"Unable to create an OpenGL ES 2.0 context. The FX3 framework requires OpenGL ES 2.0 support to work.");
        
        [EAGLContext setCurrentContext:_context];
        
        // Set up a few global settings for the image processing pipeline
       glDisable(GL_DEPTH_TEST);
       glDisable(GL_BLEND);
    }
    
    return _context;
}


CVOpenGLESTextureCacheRef FX3GLContext::glCVCache(){
    if (_glCVCache == nil)
    {
        
        CVReturn err = CVOpenGLESTextureCacheCreate(kCFAllocatorDefault
                                                    , NULL
                                                    , /*(__bridge void *) < iOS 6.0*/
                                                    this->context()
                                                    , NULL
                                                    , &_glCVCache);
      
        if (err)
        {
//            FX3Log(@"Error at CVOpenGLESTextureCacheCreate %d", err);
        }
    }
    
    return _glCVCache;
}

CFMutableDictionaryRef FX3GLContext::getCVCacheDescriptor(){
    
    if(!_CVCacheDescriptor){
       
        CFDictionaryRef empty; 
      
        empty = CFDictionaryCreate(kCFAllocatorDefault, // our empty IOSurface properties dictionary
                               NULL,
                               NULL,
                               0,
                               &kCFTypeDictionaryKeyCallBacks,
                               &kCFTypeDictionaryValueCallBacks);
        _CVCacheDescriptor = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                      1,
                                      &kCFTypeDictionaryKeyCallBacks,
                                      &kCFTypeDictionaryValueCallBacks);
    
        CFDictionarySetValue(_CVCacheDescriptor,
                         kCVPixelBufferIOSurfacePropertiesKey,
                         empty);
    }
    
    return _CVCacheDescriptor;
    
}

void FX3GLContext::activateContext(){
    
    [EAGLContext setCurrentContext:this->context()];

}

//---delegates

void FX3GLContext::didFailedWriting( void * controller){
    
    NSValue *object =[NSValue valueWithPointer:controller];
    [[NSNotificationCenter defaultCenter] postNotificationName:kFX3DidFailedWriting object:object];
    

}

void FX3GLContext::didFinishWriter( void *controller){
    
    NSValue *object =[NSValue valueWithPointer:controller];
    [[NSNotificationCenter defaultCenter] postNotificationName:kFX3DidFinishWriter object:object];
    
}

void FX3GLContext::didBeginMovie( void *controller){
    
    NSValue *object =[NSValue valueWithPointer:controller];
    [[NSNotificationCenter defaultCenter] postNotificationName:kFX3DidBeginMovie object:object];
    
}

void FX3GLContext::didFinishMovie( void *controller){
    
    NSValue *object =[NSValue valueWithPointer:controller];
    [[NSNotificationCenter defaultCenter] postNotificationName:kFX3DidFinishMovie     object:object];
    
}

void FX3GLContext::setNeedsGLFinishWhenWriting(BOOL value){
    this->_needsGLFinishWhenWriting=value;
}

void   FX3GLContext::setLastPresentationDelay(float delay){
    _lastPresentationDelay =delay;
}

#endif

#pragma mark-
void FX3GLContext::commonInit(){
    
    _textures       = new FX3Dictionary < char * , FX3GLResource *> (FX_KEYTYPE_CHARPTR);
    _frameBuffers   = new FX3Dictionary < char * , FX3GLResource *> (FX_KEYTYPE_CHARPTR);
    //_globalKnobs	= new FX3Dictionary < char * , FX3GLKnob *> (FX_KEYTYPE_CHARPTR);

    // global knobs instantiation
   // this->timeline();
    _mediaOrientation = 0;
    
}
void FX3GLContext::commonTearDown(){
    
	// TODO:  cleanup contents of tables
    delete _textures;
    delete _frameBuffers;
    
}

#if IS_ANDROID
#pragma mark - ANDROID SPECIFIC CODE


//--- builders


FX3GLContext::FX3GLContext(){
    
    this->commonInit();
     _eglSurface = NULL;
}


FX3GLContext::~FX3GLContext(){

	this->commonTearDown();
    //TODO release the _eglSurface ??
    
}
void FX3GLContext::queueGL ( FXBlock block, int mode){
    block();
}

void FX3GLContext::activateContext(){
    
    
}

void * FX3GLContext::context(){
    return _context;
}


void FX3GLContext::swapBuffers()
{
	_eglSurface->swapBuffers();
}


void FX3GLContext::createBackgroundContext( int width, int height )
{
	if ( _eglSurface != NULL )
		delete _eglSurface;
		
	_eglSurface = new FX3EGLSurface( width, height );
	_eglSurface->initialize();
}



#endif
