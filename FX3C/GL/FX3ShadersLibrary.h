//
//  FX3ShadersLibrary.h
//  FXLab2
//
//  Created by hassanvfx on 7/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef FXLab2_FX3ShadersLibrary_h
#define FXLab2_FX3ShadersLibrary_h




/*
 
 CROSS PLATFORM OPERTATORS
 
 */



#include "Core/FX3Shader.h"
#include "Core/FX3VisionShader.h"
#include "Library/FX3Solid.h"
#include "Library/FX3Add.h"


#include "Library/FX3ImageProvider.h"
#include "Library/FX3MovieProvider.h"
#include "Library/FX3MovieWriter.h"

#include "Library/FX3RenderBuffer.h"
#include "Library/FX3Resize.h"
#include "Library/FX3ResizeWithAspect.h"
#include "Library/FX3Fit.h"
#include "Library/FX3Orient.h"
#include "Library/FX3FitOrient.h"
#include "Library/FX3FitOrientScanTransform.h"
#include "Library/FX3AlphaAtlas.h"



/*
 
 PLATFORM SPECIFIC OPERATORS
 
 */

#if IS_MAC
#include "FX3RenderViewOSX.h"
#include "FX3ProviderOSX.h"
#include "FX3ImageProviderOSX.h"
#import "OSXUtils.h"
#endif




#if IS_IOS
#include "Library/FX3RenderViewIOS.h"
#include "Library/Media/FX3CameraIOS.h"
//#include "Library/Media/FX3CameraYUVIOS.h"
#include "Library/Media/FX3YUV2RGB.h"

#endif




#if IS_ANDROID

#include "Library/FX3RenderViewAndroid.h"

#include "Library/Media/FX3MovieWriterFFMPEG.h"
#include "Library/Media/FX3MovieProviderFFMPEG.h"


#include "Library/Media/FX3MovieProviderRAW.h"
#include "Library/Media/FX3MovieWriterRAW.h"

#include "Library/Media/FX3ImageProviderTGA.h"
#include "Library/Media/FX3ImageProviderPNG.h"

#endif

#endif
