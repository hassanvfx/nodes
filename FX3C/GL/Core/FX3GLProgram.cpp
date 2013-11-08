 //
//  FX3GLProgram.cpp
//  FXLab2
//
//  Created by hassanvfx on 7/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//



#include "FX3GLProgram.h"


#define LOG_TAG "FX3GLProgram"


// START:init

FX3GLProgram::FX3GLProgram(){
    attributes = new char*[FX3GL_MAX_ATTRIBUTES];
    nextAttributeIndex=0;
    program = 0;
    vertShader = 0;
    fragShader = 0;
    
}
FX3GLProgram::~FX3GLProgram(){

    if (vertShader != 0 )
        glDeleteShader(vertShader);

    if (fragShader != 0 )
        glDeleteShader(fragShader);

    if (program != 0 )
        glDeleteProgram(program);

    if ( attributes != NULL )
    	delete [] attributes;
    
    vertShader = 0;
    fragShader = 0;
    program = 0;
    attributes = NULL;
}

int FX3GLProgram::findAttributeIndex( char *key){
    
    for (int i=0; i<nextAttributeIndex; i++) {
        char *a = (char *)FXCommonAttributes[i];
        if(strcmp (a,key) == 0){
            return i;
        }
    }
    
    return -1;
}


void FX3GLProgram::createFromVertexAndFragment(char *vShaderString, char *fShaderString)
{
    
    program = glCreateProgram();
    
    
    LOGI("vertex= %s\n",vShaderString);
    LOGI("fragment= %s\n",fShaderString);
    
    if( ! this->compileShaderType( &vertShader,
                                  GL_VERTEX_SHADER, 
                                  vShaderString) 
       )
        LOGI("FXLog: Failed to compile vertex shader\n");
        
    if( ! this->compileShaderType( &fragShader, 
                                  GL_FRAGMENT_SHADER, 
                                  fShaderString) 
       )
        LOGI("FXLog: Failed to compile fragment shader\n");
    
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
 
}

// START:compile
bool FX3GLProgram::compileShaderType(GLuint *shader, GLenum type , char *shaderString)
{
    GLint status;
    const GLchar *source;
    
    source = (GLchar *)shaderString;
    if (!source)
    {
       //LOGI(@"FXLog: Failed to load shader type %d\n",type);
        return false;
    }
    
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);
    
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    
	if (status != GL_TRUE)
	{
		GLint logLength;
		glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0)
		{
			GLchar *log = (GLchar *)malloc(logLength);
			glGetShaderInfoLog(*shader, logLength, &logLength, log);
//			FX3Log(@"FXLog: Shader compile log:\n%s\n", log);
			free(log);
		}
	}	
	
    return status == GL_TRUE;
}
// END:compile
#pragma mark -
// START:addattribute
void FX3GLProgram::addAttribute(char * attributeName)
{
    if ( this->findAttributeIndex(attributeName)==-1)
    {
        //posibly copy the char
        attributes[nextAttributeIndex] = attributeName;
        
        glBindAttribLocation(program, 
                             nextAttributeIndex, 
                             attributeName);
        
        nextAttributeIndex+=1;
    }
}
// END:addattribute
// START:indexmethods
GLuint FX3GLProgram::attributeIndex(char * attributeName)
{
    return (GLuint)this->findAttributeIndex(attributeName);
}
GLuint FX3GLProgram::uniformIndex(char * uniformName)
{
    return (GLuint)glGetUniformLocation(program, uniformName);
}
// END:indexmethods
#pragma mark -
// START:link
bool FX3GLProgram::link()
{
    GLint status;
    
    glLinkProgram(program);
    
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
        return false;
    
    if (vertShader)
        glDeleteShader(vertShader);
        if (fragShader)
            glDeleteShader(fragShader);
            
            return true;
}
// END:link
// START:use
void FX3GLProgram::use()
{
    glUseProgram(program);
}
// END:use
#pragma mark -
// START:privatelog
char * FX3GLProgram::logForOpenGLObject(GLuint object, GLInfoFunction infoFunc,GLLogFunction logFunc)

{
    GLint logLength = 0, charsWritten = 0;
    
    infoFunc(object, GL_INFO_LOG_LENGTH, &logLength);    
    if (logLength < 1)
        return NULL;
    
    char *logBytes = (char*)malloc(logLength);
    logFunc(object, logLength, &charsWritten, logBytes);
    
    return logBytes;
}
// END:privatelog
// START:log
char * FX3GLProgram::vertexShaderLog()
{

    return this->logForOpenGLObject(vertShader, 
                                    (GLInfoFunction)&glGetProgramiv, 
                                    (GLLogFunction)&glGetProgramInfoLog);
    
}
char * FX3GLProgram::fragmentShaderLog()
{
   
    return this->logForOpenGLObject(fragShader, 
                                    (GLInfoFunction)&glGetProgramiv, 
                                    (GLLogFunction)&glGetProgramInfoLog);
    
}
char * FX3GLProgram::programLog()
{
   
    
    return this->logForOpenGLObject(program, 
                                    (GLInfoFunction)&glGetProgramiv, 
                                    (GLLogFunction)&glGetProgramInfoLog);
}
// END:log

void FX3GLProgram::validate()
{
	GLint logLength;
	
	glValidateProgram(program);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		GLchar *log = (GLchar *)malloc(logLength);
		glGetProgramInfoLog(program, logLength, &logLength, log);
//		FX3Log(@"FXLog: Program validate log:\n%s", log);
		free(log);
	}	
}


