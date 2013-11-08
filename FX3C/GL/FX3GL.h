//
//  FX3GL.h
//  FXLab2
//
//  Created by hassanvfx on 7/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef FXLab2_FX3GL_h
#define FXLab2_FX3GL_h

#pragma GCC diagnostic ignored "-Wwrite-strings"



#include "../PIPELINE/FX3.h"

#include "FX3GLConstants.h"

#include "Core/FX3CoreUtilities.h"
#include "Core/FX3GeoUtils.h"
#include "Core/FX3GLKnob.h"


#if IS_ANDROID

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>



#endif



#if IS_IOS || IS_OSX

#include <GLKit/GLKit.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import "NSURL+fx.h"
#endif


#endif
