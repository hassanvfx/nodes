//
//  FX3GLProgram.h
//  FXLab2
//
//  Created by hassanvfx on 7/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef FXLab2_FX3GLProgram_h
#define FXLab2_FX3GLProgram_h





#include "../FX3GL.h"

#include "../../PIPELINE/FX3Dictionary.h"


typedef void (*GLInfoFunction)(GLuint program, 
                               GLenum pname, 
                               GLint* params);
typedef void (*GLLogFunction) (GLuint program, 
                               GLsizei bufsize, 
                               GLsizei* length, 
                               GLchar* infolog);


class FX3GLProgram  
{
    
    protected:
    char**          attributes;
    int nextAttributeIndex;
    int findAttributeIndex(char *);
    
    //FX3Dictionary  *uniforms;
    GLuint          program,
	vertShader, 
	fragShader;	
    
    public:
    
    void createFromVertexAndFragment(char *,char *);
    bool compileShaderType(GLuint *, GLenum, char*);
    char * logForOpenGLObject(GLuint object, GLInfoFunction infoFunc,GLLogFunction logFunc);

    char * vertexShaderLog();
    char * fragmentShaderLog();
    char * programLog();
   
    void    addAttribute    (char *);
    GLuint  attributeIndex  (char *);
    GLuint  uniformIndex    (char *);
    
    bool link();
    void use();
 
    void validate();
    
    FX3GLProgram();
    ~FX3GLProgram();
    
};

#endif
