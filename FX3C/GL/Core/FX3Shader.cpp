//
//  FX3Shader.cpp
//  FXLab2
//
//  Created by hassanvfx on 7/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//



#include "FX3Shader.h"



#define LOG_TAG "FX3Shader"



/*
 
 STATIC BUILDER STRING
 
 */


char* FX3Shader:: builder(){
    return (char *)"FX3Shader";
    
}




int FX3Shader::render(){
    
	if( ! this->timeline()->isCanceled() ){
		LOGI("FXLog: /\\  GOING UP STREAM %s\n",_NAME );
        
       // FX3GLContext::shared()->queueGL(^{
          
       
            this->doFinalOutput();
       
		LOGI("FXLog: \\/  RENDERING FINISHED %s\n",_NAME );
        
            this->lock();
        //});
	} else{
		LOGE("FXLog: - PIPELINE CANCELED FOR %s\n",_NAME );
        
	}
    return _output;
}

void FX3Shader::unlock(){
    this->_useCache=false;
    CVPixelBufferUnlockBaseAddress(_videoCVBuffer, 0);
}
#pragma mark context


FX3GLTimeline *FX3Shader::timeline(){
    if(_timeline ==nil){
       // _timeline() =FX3GLContext::shared()->timeline();
    }
    return _timeline;
}

void FX3Shader::setTimeline(FX3GLTimeline *newContext){
    _timeline=newContext;
}

/*
 
 EXTERNALSHADERS
 
 */

#pragma mark EXTERNAL SHADERS

char* FX3Shader::vertexShader()
{
    return SHADER_STRING
    (
     
     attribute mediump vec4 vertexPosition;
     attribute mediump vec4 vertexUV;
     varying mediump vec2 textureCoordinate;
     
     void main()
     {
         
         gl_Position = vertexPosition;
         textureCoordinate = vertexUV.xy;
     }
     );
    
}
char* FX3Shader::fragmentShader()
{
    
    return SHADER_STRING
    (
     
     varying mediump vec2 textureCoordinate;
     uniform sampler2D texture0;
     
     
     void main()
     {
         
         mediump vec4 textureColor =  texture2D(texture0, textureCoordinate);
         gl_FragColor = textureColor;
         
     }
     );
    
    
}




/*
 
 BUILDING
 
 */

#pragma mark BUILDING

FX3Shader::FX3Shader() : FX3INode(){
    
    _wasBussy    =false;
    _isBussy     =false;
    program     =NULL;
    
    backgroundColorRed      = 0.0;
    backgroundColorGreen    = 0.0;
    backgroundColorBlue     = 0.0;
    backgroundColorAlpha    = 1.0;
    
    _fragmentShader =NULL;
    _vertexShader	=NULL;
    shaderFramebuffer =FX3GL_UNDEFINED;
    outputTexture     =FX3GL_UNDEFINED;
    
    _requiredInputs = 3;
    _outputTextureSizeOverriden =false;
    _timeline=nil;
#if IS_IOS
    _isLinkedToCVPool=false;
    
    _videoCVBuffer =nil;
    _videoCVTexture =nil;
    _coreVideoTextureCache=nil;
    _videoCVPoolLink =nil;
    _videoCVPool=nil;
    _enableCVPixelBuffer=YES;
#endif
}
FX3Shader::~FX3Shader(){
    
    this->deleteFrameBuffer();
    this->deleteOutputTexture();
    this->deleteShader();
    
    if(_vertexShader!=NULL)
        free(this->_vertexShader);
    
    if(_fragmentShader!=NULL)
        free(this->_fragmentShader);
    
    
    this->tearDown();
    
}
void FX3Shader::setVertexShader	( char *shader){
	if(this->_vertexShader != NULL){
        free(this->_vertexShader);
    }
    
	this->_vertexShader = strdup( shader);
}

void FX3Shader::setFragmentShader	( char *shader){
	if(this->_fragmentShader != NULL){
        free(this->_fragmentShader);
	}
    
    
	this->_fragmentShader = strdup( shader);
    
}
/*
void FX3Shader::setOutputTextureSize	( FX3Size size){
    _outputTextureSizeOverriden=true;
    this->outputTextureSize = FX3Size( size.width, size.height);
    
}*/



void FX3Shader::compileShader(){
    
	if(this->_vertexShader == NULL){
		this->_vertexShader   = strdup(this->vertexShader());
	}
    
	if(this->_fragmentShader == NULL){
		this->_fragmentShader  = strdup(this->fragmentShader());
	}
    
    
    this->createFromVertexAndFragment(this->_vertexShader , this->_fragmentShader);
    
}

void FX3Shader::createFromVertexAndFragment(char *vertex, char *fragment){
    
    
    
    this->validateContext();
    
    this->createShader();
    
    this->program->createFromVertexAndFragment(vertex, fragment);
    
    
    
    this->addAttributes();
    
    if (!this->program->link())
	{
		FX3Log(@"FXlog: fragment=%s" ,fragment);
        FX3Log(@"FXlog: vertex=%s"   ,vertex);
        
        char *fragLog = this->program->fragmentShaderLog();
		FX3Log(@"FXlog:\n\n %s Fragment shader compile log: %s\n\n",this->_NAME , fragLog);
		
        char *progLog = this->program->programLog();
		FX3Log(@"FXlog:\n\n %s Program link log: %s\n\n",this->_NAME , progLog);
		
        
        char *vertLog = this->program->vertexShaderLog();
		FX3Log(@"FXlog:\n\n %s Vertex shader compile log: %s\n\n",this->_NAME , vertLog);
		
        delete program;
        
        program=NULL;
        //NSAssert(NO, @"%@ shader link failed",name);
        
        progLog=NULL;
        fragLog=NULL;
        vertLog=NULL;
        
	}
    
    this->linkUniforms();
    this->linkTextures();
    this->enableAttributes();
    this->feedAttributes();
    
    
    
    
}

/*
 PROGRAM BUILDER ASSISTANTS
 */


#pragma mark   PROGRAM BUILDER ASSISTANTS

void FX3Shader::addAttributes(){
    
    for (int i=0; i<FX3GL_MAX_COMMON_ATTRIBUTES; i++) {
        char *attr = (char *)FXCommonAttributes[i];
        program->addAttribute(attr);
        
    }
}

void FX3Shader::feedAttributes(){
    
    int index = program->attributeIndex((char *)"vertexPosition");
    
    glVertexAttribPointer(index, 2, GL_FLOAT, 0, 0,
                          FX3GLContext::vertexPosition);
    
    index = program->attributeIndex((char *)"vertexUV");
    
    glVertexAttribPointer(program->attributeIndex((char *)"vertexUV"), 2, GL_FLOAT, 0, 0,
                          FX3GLContext::vertexUV);
    
    
}
void FX3Shader::linkUniforms(){
    
    
    
	for (int i = 0; i < FX3GL_MAX_COMMON_UNIFORMS; i++) {
		char *uniform = (char *) FXCommonUniforms[i];
		int index = program->uniformIndex(uniform);
        
        if( index > -1 && index < ULONG_MAX){
            FX3GLKnob *knob = (FX3GLKnob *)this->knobs()->lookup(uniform );
            LOGI("FXLog: Preparing to link uniform %s",uniform);
            
            if ( knob != NULL){
        		
                LOGI("FXLog: knob %s exists",uniform);
                
                // check if the knob is one of the global knobs
                // TODO:
                //we need to depricate this ....
                // but if we remove the following loop app crashes
                
                for ( int j = 0; j < FX3GL_MAX_GLOBAL_KNOBS; ++j )
                {
                    if ( strcmp( uniform, FXGlobalKnobs[j] ) == 0 ) {
                        LOGI("FXLog:  found a global knob");
                        // set the knob pointer to the global knob
                        //	knob = (FX3GLKnob *)this->context()->globalKnobs()->lookup(uniform );
                        //	this->knobs()->replace(knob->_NAME, knob);
                    }
                    
                }
                
                //only update the shader uniformindex
                //LOGI("FXLog: uniform %s exists updating shaderIndex = %u currentValue %f", uniform, index, knob->_float1);
                knob->uniformIndex = index;
            }
            else
            {
                LOGI("FXLog: knob %s does not exists",uniform);
                LOGI("FXLog: uniform %s doesn't exist creating shaderIndex = %u", uniform,  index);
                //create an insert
                
                //just to be sure that we are not pointing to dump memory
                
                this->createKnob( uniform, kKnobFloat1D, 0.0);
                knob =(FX3GLKnob *) this->knobs()->lookup(uniform);
                knob->uniformIndex = index;
                
                //this->knobs()->insert(knob->_NAME, knob);
            }
            
            /*
             FX3GLKnob *knob  = new FX3GLKnob(uniform, kKnobFloat1D);
             knob->uniformIndex = index;
             
             //just to be sure that we are not pointing to dump memory
             knob->_float1=0.5;
             
             this->knobs()->insert(knob->_NAME, knob);
             */
        }
    }
    
}

void FX3Shader::linkTextures(){
    
    for (int i=0; i<FX3GL_MAX_COMMON_TEXTURES; i++) {
        char *uniform = (char *)FXCommonTextures[i];
        int index = program->uniformIndex(uniform);
        
        if( index != -1){
            FX3GLKnob *knob = new FX3GLKnob(uniform, kKnobSampler2D);
            knob->uniformIndex = index;
            
            // we need to point to the corresponding
            // input port for the texture name
            // i.w. texture0->0 texture1->1 etc.
            knob->_int1 = i;
            
            
            LOGI("FXLog:linkedTexture  uniformIndex sampler %u toTextureUnit = %d",  index, i);
            
            
            this->knobs()->insert(knob->_NAME, knob);
        }
    }
    
}


void FX3Shader::enableAttributes(){
    for (int i=0; i<FX3GL_MAX_COMMON_ATTRIBUTES; i++) {
        char *attr = (char *)FXCommonAttributes[i];
        glEnableVertexAttribArray(program->attributeIndex(attr));
    }
    
}




/*
 
 UNIFORMS ATTRIBUTES FEEDING
 
 */

#pragma mark  UNIFORMS ATTRIBUTES FEEDING

void    FX3Shader::prepareShaderKnobs(){
    
}

void    FX3Shader::updateShaderKnobs(){
    
    
        
   
    /*
    
    //for (int i = 0; i <  this->knobs()->getCount() ; ++i) {
    FX3GLContext::shared()->queueGL(^{
   
    
    dispatch_queue_t queue =dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    
    dispatch_apply(this->knobs()->getCount(), queue, ^(size_t i) {
        FX3TableEntry< char *, FX3Knob*> **entries = this->knobs()->getEntries();
        
        
        FX3TableEntry< char *, FX3Knob*> *item = entries[i];
        FX3GLKnob * knob = (FX3GLKnob *)item->value;
        
        
        if( knob->_type ==  kKnobSampler2D)
        {
        	LOGI("FXLog: %s feeding texture uniformIndex %u with textureUnit %u", _NAME, knob->uniformIndex,knob->_int1 );
            
            glUniform1i(knob->uniformIndex,
                        knob->_int1);
        } else if( knob->_type ==  kKnobFloat1D) {
            
        	float val =knob->_float1;
            
        	FX3GLKnob *globalKnob = (FX3GLKnob *)this->context()->globalKnobs()->lookup(knob->_NAME );
        	if(globalKnob!=NULL){
        	  	LOGI("FXLog: GLOBAL OVERRIDE NEXT>");
                
        		val =globalKnob->_float1;
        	}
            
        	//LOGI("FXLog: %s feeding float for knob %s  uniformIndex %u with %f", _NAME, knob->_NAME, knob->uniformIndex, val );
           
                glUniform1f(knob->uniformIndex,
                        val);
          
        }
        
        delete [] entries;
    });
        
    
    });*/
    
    
    
    FX3TableEntry< char *, FX3Knob*> **entries = this->knobs()->getEntries();
    
    for (int i = 0; i <  this->knobs()->getCount() ; ++i) {
        
        FX3TableEntry< char *, FX3Knob*> *item = entries[i];
        FX3GLKnob * knob = (FX3GLKnob *)item->value;
        
        if (knob->uniformIndex!=FX3_UNDEFINED ||
            knob->uniformIndex < ULONG_MAX) {
               
           
                
                if( knob->_type ==  kKnobSampler2D)
                {
                    LOGI("FXLog: %s feeding texture uniformIndex %u with textureUnit %u", _NAME, knob->uniformIndex,knob->_int1 );
                    
                    glUniform1i(knob->uniformIndex,
                                knob->_int1);
                } else if( knob->_type ==  kKnobFloat1D) {
                    
                    float val =knob->_float1;
                    
                    FX3GLKnob *globalKnob = (FX3GLKnob *)this->timeline()->globalKnobs()->lookup(knob->_NAME );
                    if(globalKnob!=NULL){
                        LOGI("FXLog: GLOBAL OVERRIDE NEXT>");
                        
                        val =globalKnob->_float1;
                    }
                    
                     
                    if(knob->_lastFloat1!= val ){
                        
                        if(!knob->_animate
                           || knob->_lastFloat1 ==FX3GL_UNDEFINED
                           || knob->_animatedVal ==FX3GL_UNDEFINED ){
                            glUniform1f(knob->uniformIndex,
                                        val);
//                            FX3Log(@"%s feeding float for knob %s  uniformIndex %u with %f", _NAME, knob->_NAME, knob->uniformIndex, val );
                        }else{
                            float current = knob->_animatedVal;
                            float frame = 1.0 /15.0;
                            float goal =val;
                            val = val > current ? current +frame :  val < current ? current -frame: val;
                            val = fabs(goal-val)<frame ? goal:val;
                            
                            glUniform1f(knob->uniformIndex,
                                        val);
                            //FX3Log(@"%s feeding animated float for knob %s  uniformIndex %u with %f", _NAME, knob->_NAME, knob->uniformIndex, val );
                            knob->_animatedVal =val;
                            
                        }
                    }
                    knob->_animatedVal=val;
                    knob->_lastFloat1=val;
                }
            }
        
    }
    
    delete [] entries;
    
}



/*
 
 RENDERING PIPE OVERRIDE
 
 */

#pragma mark RENDERING PIPE OVERRIDES

void FX3Shader::preRenderEngine(){
    
         
    this->validateContext();
    
    
    this->validateShader();  // first validate to create all the posible required knobs  for all other process
    

    this->getInputsInfo();
    
    if( !isLinkedToCVPool()){
        this->setOutputsInfo();
    }
    
    this->validateSize();
    
    this->validateOutputTexture();
    this->validateFrameBuffer();
    
    this->prepareShaderKnobs();
    
    
}
void FX3Shader::renderEngine(){
    
    this->activateShader();
    this->updateShaderKnobs();
    
    this->activateFrameBuffer();
    this->activateViewport();
    this->clear();
    
    this->draw();
}
void FX3Shader::postRenderEngine(){
    
    this->tearDown();
}

/*
 
 LINKING
 
 */
#pragma mark LINKING

void FX3Shader::linkOutputInput(FX3Node* output, int input){
    
    FX3Shader *outputShader= (FX3Shader*)output;
    
    FX3GLContext::shared()->queueGL(^{
        glActiveTexture( GL_TEXTURE0 + input );
       // glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, outputShader->outputTexture);
          // glDisable(GL_TEXTURE_2D);
        
       // GLuint ptrOutTex = outputShader->outputTexture;
      //  LOGI("FXLog: linking TextureUnit %d with TextureData %u from %s", input, ptrOutTex,output->_NAME);
        // FX3Log(@"FXLog: linking TextureUnit %d with TextureData %u from %s", input, ptrOutTex,output->_NAME);
        
    });
    
    
    
}

/*
 
 RENDERING SETUP
 
 */

#pragma mark RENDERING SETUP

void FX3Shader::validateContext(){
    
    FX3GLContext::shared()->activateContext();
    
}


void FX3Shader::setOutputTextureSize(float width,float  height){
    this->_outputTextureSizeOverriden=true;
    
    this->createKnob( kKnobOutputWidth    , kKnobFloat1D, width );
    this->createKnob( kKnobOutputHeight   , kKnobFloat1D, height );
    
    outputTextureSize=FX3Size(width,height);
    
    
    
}

void  FX3Shader::getInputsInfo(){
    
	if ( this->_inputs[0] != NULL ) {
	    FX3Shader * input0 = (FX3Shader*)this->_inputs[0];
	    inputTextureSize = FX3Size(input0->outputTextureSize.width,input0->outputTextureSize.height);
        
        if(isnan(inputTextureSize.width) ||
           isnan(inputTextureSize.height) ){
            NSLog(@"error");
        }
        FX3GLContext::shared()->queueGL(^{
            this->setKnobToFloat1Value(kKnobInputWidth,   (float)inputTextureSize.width );
            this->setKnobToFloat1Value(kKnobInputHeight,  (float)inputTextureSize.height );
            //this->setKnobToFloat1Value(kKnobTextelWidth,  1.0/(float)inputTextureSize.width );
            //this->setKnobToFloat1Value(kKnobTextelHeight, 1.0/(float)inputTextureSize.height );
        });
    }
    
}

bool FX3Shader::isLinkedToCVPool(){
    
    if(_isLinkedToCVPool){
        outputTextureSize = _videoCVPoolLink->outputTextureSize;    
    }
    
    return _isLinkedToCVPool;
   
}

void  FX3Shader::setOutputsInfo(){
    
  
        
    
    if(_outputTextureSizeOverriden)
        return;
    
    FX3GLKnob *outputWidth = 	( FX3GLKnob *)this->knobs()->lookup(kKnobOutputWidth);
    FX3GLKnob *outputHeight =  	( FX3GLKnob *)this->knobs()->lookup(kKnobOutputHeight);
    
    if (outputWidth !=NULL &&
        outputHeight !=NULL) {
        outputTextureSize =FX3Size(outputWidth->_float1,
                                   outputHeight->_float1);
    }else{
        outputTextureSize =FX3Size(inputTextureSize.width,
                                   inputTextureSize.height);
  
    }  
    
   
    
}

/*
 
 VALIDATIONS
 
 */

#pragma mark VALIDATIONS

void FX3Shader::validateSize(){
    
    //only use 16x sizes
   // outputTextureSize.width     = roundf(outputTextureSize.width/16.0)*16.0;
  //  outputTextureSize.height    = roundf(outputTextureSize.height/16.0)*16.0;
    
    if(outputTextureSize.width != lastOutputTextureSize.width ||
       outputTextureSize.height != lastOutputTextureSize.height ){
        this->deleteOutputTexture();
        this->deleteFrameBuffer();
    }
    
    lastOutputTextureSize = FX3Size(outputTextureSize.width, outputTextureSize.height );
    
}

void FX3Shader::validateShader(){
    
    FX3GLContext::shared()->queueGL(^{
        if(program==NULL){
            this->compileShader();
        }
    });
}
void FX3Shader::validateOutputTexture(){
    if(outputTexture ==FX3GL_UNDEFINED ){
        this->deleteFrameBuffer();
        this->createOutputTexture();
    }
}
void FX3Shader::validateFrameBuffer(){
    
    if(shaderFramebuffer ==FX3GL_UNDEFINED ){

        this->createFrameBuffer();
    }
    
  
    
    
}


/*
 
 CREATE
 
 */

#pragma mark CREATE
void FX3Shader::createShader(){
    
    this->deleteShader();
    
    
    FX3GLContext::shared()->queueGL(^{
        this->program = new FX3GLProgram();
    });
    
}
void FX3Shader::createOutputTexture(){
    //FX3Log(@"recreating texture %s",this->_NAME );
//#if kFX3SupportCoreVideoPools
    //CVCache extension
    if (_enableCVPixelBuffer) {

        this->createCVOutputTexture();
        return;
    }
    //#endif
    FX3Log(@"--->FX3Shader::createOutputTexture | BASIC | %s",this->_NAME);
    
    this->deleteOutputTexture();
    
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
void FX3Shader::createFrameBuffer(){
    
    this->deleteFrameBuffer();
    
    FX3GLContext::shared()->queueGL(^{
        FX3GLContext::shared()->genFrameBuffer(this->_NAME, &shaderFramebuffer);
        
        
         
        bool useMimap =false;
        if(outputTextureSize.width == outputTextureSize.height &&
           (
            (int)outputTextureSize.width == 32 ||
            (int)outputTextureSize.width == 64 ||
            (int)outputTextureSize.width == 128 ||
            (int)outputTextureSize.width == 256 ||
            (int)outputTextureSize.width == 512 ||
            (int)outputTextureSize.width == 1024 ||
            (int)outputTextureSize.width == 2048
            )
           ){
            FX3Log(@"enabling mipmap for %s",this->_NAME);
            useMimap =true;
        }
         
        glBindFramebuffer(GL_FRAMEBUFFER, shaderFramebuffer);
        // glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, outputTexture);
        
        if(useMimap){
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        }
        
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGBA,
                     (int)outputTextureSize.width,
                     (int)outputTextureSize.height,
                     0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     0);
        
        glFramebufferTexture2D(GL_FRAMEBUFFER,
                               GL_COLOR_ATTACHMENT0,
                               GL_TEXTURE_2D,
                               outputTexture,
                               0);
        if(useMimap){
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        
        LOGI("FXLog: Framebuffer status %d\n",glCheckFramebufferStatus(GL_FRAMEBUFFER));
        glBindTexture(GL_TEXTURE_2D, 0);
    });
}


/*
 
 DELETE
 
 */


#pragma mark DELETE

void FX3Shader::flushNow(){
    
    
    LOGI("FXLog: < < < <   FLUSHING NOW %s > > > >  \n",_NAME );
    
    
    this->deleteFrameBuffer();
    this->deleteOutputTexture();
    this->deleteShader();
    this->_flushASAP=false;
    this->_useCache=false;
    
}



void FX3Shader::deleteShader(){
//    FX3GLContext::shared()->queueGL(^{
        if(program!=NULL){
            LOGI("About to delete program for node = %s", this->_NAME );
            delete program;
            program = NULL;
        }
 //   });
}
void FX3Shader::deleteOutputTexture(){
    
    
#if IS_IOS
    //CVCache extension
    this->deleteCVOutputTexture();
   // return;
#endif
//    FX3Log(@"--->FX3Shader::deleteOutputTexture | BASIC | %s",this->_NAME);
    
   // FX3GLContext::shared()->queueGL(^{
        if (outputTexture != FX3GL_UNDEFINED)
        {
            
            FX3GLContext::shared()->deleteTexture(  &outputTexture);
            //glDeleteTextures(1, &outputTexture);
            
            outputTexture = FX3GL_UNDEFINED;
        }
   // });
    
    
}
void FX3Shader::deleteFrameBuffer(){
   // FX3GLContext::shared()->queueGL(^{
        if (shaderFramebuffer != FX3GL_UNDEFINED)
        {
            FX3GLContext::shared()->deleteFrameBuffer(  &shaderFramebuffer);
            
            //glDeleteFramebuffers(1, &shaderFramebuffer);
            shaderFramebuffer = FX3GL_UNDEFINED;
        }
  //  });
    
}

/*
 
 LOW LEVEL DRAWING
 
 */


#pragma mark LOW LEVEL DRAWING

void FX3Shader::activateViewport(){
    FX3GLContext::shared()->queueGL(^{
        glViewport(0, 0, (int)outputTextureSize.width, (int)outputTextureSize.height);
    });
}

void FX3Shader::clear(){
    FX3GLContext::shared()->queueGL(^{
        glClearColor(backgroundColorRed, backgroundColorGreen, backgroundColorBlue, backgroundColorAlpha);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    });
}

void FX3Shader::activateFrameBuffer(){
    FX3GLContext::shared()->queueGL(^{
        glBindFramebuffer(GL_FRAMEBUFFER, shaderFramebuffer);
        //glBindFramebuffer(GL_FRAMEBUFFER, 0);
    });
    
}
void FX3Shader::activateShader(){
    
    FX3GLContext::shared()->queueGL(^{
        this->program->use();
    });
}
void FX3Shader::draw(){
    
     FX3GLContext::shared()->queueGL(^{
       
         glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
     
     });
    /*
    if(!_isLinkedToCVPool)
    {
        FX3GLContext::shared()->queueGL(^{
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            //glFinish();
        });
        
    }else{
        
        FX3GLContext::shared()->queueWriter(^{
     
             //  CVPixelBufferUnlockBaseAddress(_videoCVBuffer, 0);
            
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            glFinish(); //glFinish()
            
            // if(_isLinkedToCVPool)
          //  CVPixelBufferLockBaseAddress(_videoCVBuffer, 0);
        },FXSYNC);
    }*/

}
void FX3Shader::tearDown(){
//    FX3GLContext::shared()->queueGL(^{
//        glBindFramebuffer(GL_FRAMEBUFFER, 0);
//        //glEnable(GL_TEXTURE_2D);
//        glBindTexture(GL_TEXTURE_2D, 0);
//    });
}

void FX3Shader::stop()
{
    
}


/*
 *
 *  knobs creation
 *
 */


// KNOBS CREATION


void* FX3Shader::createKnobFactory( char * n, int t){
	LOGI("FXlog: creating a FX3GLKnob %s",n);
	return new FX3GLKnob(n,t);
}

#if IS_IOS
// CVCache extension
#pragma mark CVExtension

void FX3Shader::deleteCVOutputTexture(){
    
   // FX3Log(@"--->FX3Shader::deleteCVOutputTexture < CVPixelBuffer > %s",this->_NAME);
    
    
    if(outputTexture==FX3GL_UNDEFINED)
        return;
    
    if(_videoCVBuffer){
      
             CVPixelBufferUnlockBaseAddress(_videoCVBuffer, 0);
             CVPixelBufferRelease(_videoCVBuffer);
             //CFRelease(_videoCVBuffer);
             _videoCVBuffer=nil;
        
    }
    
    
    if(_videoCVTexture){
        
             // Flush the CVOpenGLESTexture cache and release the texture
             CVOpenGLESTextureCacheFlush(_coreVideoTextureCache, 0);
             CFRelease(_videoCVTexture	);
             _videoCVTexture=nil;
       
       
    }
    outputTexture = FX3GL_UNDEFINED;
}
void FX3Shader::unlinkToCVPixelBbufferPool(){
    _isLinkedToCVPool = false;
    _videoCVPoolLink  =  nil;
    _videoCVPool      =  nil;
    
}

void FX3Shader::linkToCVPixelBufferPool( FX3Shader * link){
    
    
    //size must be the same
    //that the one described in the pixel pool
    
     _isLinkedToCVPool=false;
    if( link!=nil){
        _isLinkedToCVPool=true;
        _videoCVPoolLink = link;
        _videoCVPool      =  _videoCVPoolLink->getCVPixelBufferPool();
        outputTextureSize =  _videoCVPoolLink->outputTextureSize;
       // return true;
    }
    

    
}


CVPixelBufferPoolRef  FX3Shader::getCVPixelBufferPool(){
    return nil;
}

void FX3Shader::createCVOutputTexture(){
    
    this->deleteCVOutputTexture();
    
    //FX3GLContext::shared()->activateContext();

   
    if (_videoCVPool  !=nil) {
//        FX3Log(@"--->FX3Shader::createCVOutputTexture < FROM POOL > %s",this->_NAME);
        
        CVPixelBufferPoolCreatePixelBuffer (NULL,
                                           _videoCVPool,
                                            &_videoCVBuffer); //le decimos que aqui vamos a escribir
        
    } else{
//        FX3Log(@"--->FX3Shader::createCVOutputTexture <  SINGLE > %s",this->_NAME);
        CVPixelBufferCreate(kCFAllocatorDefault,
                        outputTextureSize.width,
                        outputTextureSize.height,
                        kCVPixelFormatType_32BGRA,
                        FX3GLContext::shared()->getCVCacheDescriptor(),
                        &_videoCVBuffer);
    }
   
   // FX3Log(@"_videoCVBuffer %@",_videoCVBuffer);
    
    // in real life check the error return value of course
    
    _coreVideoTextureCache = FX3GLContext::shared()->glCVCache();;
    
     CVPixelBufferLockBaseAddress(_videoCVBuffer, 0);
    
    CVReturn err =
    CVOpenGLESTextureCacheCreateTextureFromImage(
                                                 kCFAllocatorDefault,
                                                 _coreVideoTextureCache,
                                                 _videoCVBuffer,
                                                 NULL,
                                                 GL_TEXTURE_2D,
                                                 GL_RGBA,
                                                 outputTextureSize.width,
                                                 outputTextureSize.height,
                                                 GL_BGRA,
                                                 GL_UNSIGNED_BYTE,
                                                 0,
                                                 &_videoCVTexture);
    
    
   
    
    if (!_videoCVTexture || err != kCVReturnSuccess) {
          int32_t errorCode =err;
        
        NSDictionary *userinfo = [NSDictionary dictionaryWithObjectsAndKeys:
                                  [NSNumber  numberWithFloat:outputTextureSize.width], @"outputTextureSize.width",
                                  [NSNumber  numberWithFloat:outputTextureSize.height], @"outputTextureSize.height",
                                  [NSNumber  numberWithInt:errorCode], @"CVReturn",
                                  nil];

        NSError *error = [NSError errorWithDomain:@"FX3_ENGINE"
                                             code:(NSInteger)errorCode
                                         userInfo:userinfo];
        
        // FX3Log(@"Movie Provider CVOpenGLESTextureCacheCreateTextureFromImage failed (error: %d)", err);
        this->failWithError(@"CVOpenGLESTextureCacheCreateTextureFromImage failed in a Shader", error);
        
        _videoCVTexture=nil;
        
        return;
    }
    
    outputTexture = CVOpenGLESTextureGetName(_videoCVTexture);
    //FX3Log(@"FX3Shader %s outputTexture %d",this->_NAME,outputTexture);
    
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
    
   
}

void FX3Shader::setEnableCVPixelBuffer(BOOL value){
    
    FX3Log(@"--->FX3Shader::setEnableCVPixelBuffer %d %s",value,this->_NAME);
    
    _enableCVPixelBuffer=value;
    this->deleteOutputTexture();
    this->validateOutputTexture();
    this->validateFrameBuffer();
}


#endif