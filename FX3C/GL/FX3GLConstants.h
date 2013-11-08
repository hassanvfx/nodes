//
//  FX3GLConstants.h
//  FXLab2
//
//  Created by hassanvfx on 7/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef FXLab2_FX3GLConstants_h
#define FXLab2_FX3GLConstants_h


typedef enum { 

	FX3PROVIDER_WAITING =0,
	FX3PROVIDER_STARTED =1,
	FX3PROVIDER_PROCESSING=2,
	FX3PROVIDER_STOPPED=3,
	FX3PROVIDER_MOVIE_OVER=4

} FX3ProviderState;

#if !IS_IOS

typedef enum {
    UIDeviceOrientationUnknown,
    UIDeviceOrientationPortrait,
    UIDeviceOrientationPortraitUpsideDown,
    UIDeviceOrientationLandscapeLeft,
    UIDeviceOrientationLandscapeRight,
    UIDeviceOrientationFaceUp,
    UIDeviceOrientationFaceDown
} UIDeviceOrientation;

typedef enum {
    UIInterfaceOrientationPortrait           = UIDeviceOrientationPortrait,
    UIInterfaceOrientationPortraitUpsideDown = UIDeviceOrientationPortraitUpsideDown,
    UIInterfaceOrientationLandscapeLeft      = UIDeviceOrientationLandscapeRight,
    UIInterfaceOrientationLandscapeRight     = UIDeviceOrientationLandscapeLeft
} UIInterfaceOrientation;

#endif

//notifications

#if IS_IOS
#define kFX3SupportCoreVideoPools 1
#define kFX3DidFinishWriter @"kFX3DidFinishWriter"
#define kFX3DidBeginMovie @"kFX3DidBeginMovie"
#define kFX3DidFinishMovie @"kFX3DidFinishMovie"
#define kFX3DidFailedWriting @"kFX3DidFailedWriting"
#endif

#define kKnobDirectionIn      1
#define kKnobDirectionOut     0

#define kKnobTrue			1.0
#define kKnobFalse			0.0

#define kFilterNone              -1
#define kFilterDefault           0
#define kFilterFadeBlack         1
#define kFilterFadeWhite         2
#define kFilterCustom            3

#define kKnobMix 			"knobMix"
#define kKnobFrame   		"knobFrame"
#define kKnobNoise   		"knobNoise"
#define kKnobIntensity  	 "knobIntensity"
#define kKnobIntensity1   "knobIntensity1"
#define kKnobIntensity2   "knobIntensity2"
#define kKnobIntensity3   "knobIntensity3"
#define kKnobIntensity4   "knobIntensity4"
#define kKnobIntensity5   "knobIntensity5"
#define kKnobIntensity6   "knobIntensity6"
#define kKnobMin   "knobMin"
#define kKnobMax  "knobMax"
#define kKnobMin1  "knobMin1"
#define kKnobMax1   "knobMax1"
#define kKnobMin2   "knobMin2"
#define kKnobMax2   "knobMax2"
#define kKnobMin3   "knobMin3"
#define kKnobMax3   "knobMax3"
#define kKnobX  "knobX"
#define kKnobY  "knobY"
#define kKnobZ  "knobZ"
#define kKnobRotateX  "knobRotateX"
#define kKnobRotateY  "knobRotateX"
#define kKnobRotateZ  "knobRotateX"
#define kKnobScaleX  "knobScaleX"
#define kKnobScaleY  "knobScaleX"
#define kKnobScaleZ  "knobScaleX"
#define kKnobPanX  "knobPanX"
#define kKnobPanY  "knobPanY"
#define kKnobPanZ  "knobPanZ"
#define kKnobRed  "knobRed"
#define kKnobGreen  "knobGreen"
#define kKnobBlue  "knobBlue"
#define kKnobAlpha  "knobAlpha"
#define kKnobWidth  		"knobWidth"
#define kKnobHeight 	 "knobHeight"
#define kKnobInputWidth  	"knobInputWidth"
#define kKnobInputHeight 	 "knobInputHeight"
#define kKnobOutputWidth  	"knobOutputWidth"
#define kKnobOutputHeight 	 "knobOutputHeight"
#define kKnobFileName   	"knobFileName"
#define kKnobOrientation 	"knobOrientation"
#define kKnobInvert		 	"knobInvert"
#define kKnobCanvasWidth 	"knobCanvasWidth"
#define kKnobCanvasHeight 	"knobCanvasHeight"
#define kKnobFrame		 	"knobFrame"
#define kKnobNoise		 	"knobNoise"
#define kKnobDuration      	"knobDuration"
#define kKnobDirection      	"knobDirection"
#define kKnobStartFrame     	"knobStartFrame"
#define kKnobVertical      	"knobVertical"
#define kKnobHorizontal     "knobHorizontal"
#define kKnobUseMask			"knobUseMask"
#define kKnobSmooth			"knobSmooth"
#define kKnobEncodingFPS	"knobEncodingFPS"
#define kKnobFitWidth  	"   knobFitWidth"
#define kKnobFitHeight 	 "knobFitHeight"
#define kKnobCameraResolution 	 "knobCameraResolution"
#define kKnobLut1D          "knobLut1D"
#define kKnobLutTone          "knobLutTone"
#define kKnobEnhancer           "knobEnhancer"
#define kKnobLut                "knobLut"
#define kKnobVignette           "knobVignette"
#define kKnobTextelWidth        "knobTextelWidth"
#define kKnobTextelHeight       "knobTextelHeight"
#define kKnobFramerate       "kKnobFramerate"


#define kKnobInsetLeft       "knobInsetLeft"
#define kKnobInsetRight      "knobInsetRight"
#define kKnobInsetTop        "knobInsetTop"
#define kKnobInsetBottom     "knobInsetBottom"
#define kKnobInsetEnabled    "knobInsetEnabled"
#define kKnobOverlayAlpha     "knobOverlayAlpha"

#define kKnobVignetteUser       "knobVignetteUser"

extern "C" {
    #define STRINGIZE(x) #x
    #define SHADER_STRING(text) STRINGIZE(text)
    

}

__unused static const char* FXCommonUniforms[] = {

    
    (const char*)kKnobMix,
    (const char*)kKnobCanvasWidth,
    (const char*)kKnobCanvasHeight,
    (const char*)kKnobFrame,
    (const char*)kKnobNoise,
    (const char*)kKnobIntensity,
    (const char*) kKnobIntensity1,
    (const char*)kKnobIntensity2,
    (const char*)kKnobIntensity3,
    (const char*)kKnobIntensity4,
    (const char*)kKnobIntensity5,
    (const char*)kKnobIntensity6,
    (const char*)kKnobMin,
    (const char*)kKnobMax,
    (const char*)kKnobMin1,
    (const char*)kKnobMax1,
    (const char*)kKnobMin2,
    (const char*)kKnobMax2,
    (const char*) kKnobMin3,
    (const char*)kKnobMax3,
    (const char*)kKnobX,
    (const char*)kKnobY,
    (const char*)kKnobZ,
    (const char*)kKnobRed,
    (const char*)kKnobGreen,
    (const char*)kKnobBlue,
    (const char*)kKnobAlpha,
    (const char*)kKnobWidth,
    (const char*)kKnobHeight,
    (const char*)kKnobInputWidth,
    (const char*)kKnobInputHeight,
    (const char*)kKnobOutputWidth,
    (const char*)kKnobOutputHeight,
    (const char*)kKnobFileName,
    (const char*)kKnobOrientation,
    (const char*)kKnobInvert,
    (const char*)kKnobDuration,
    (const char*)kKnobDirection,
    (const char*)kKnobStartFrame,
    (const char*)kKnobVertical,
    (const char*)kKnobHorizontal,
    (const char*)kKnobUseMask,
    (const char*)kKnobSmooth,
    (const char*)kKnobEncodingFPS,
    (const char*)kKnobFitWidth,
    (const char*)kKnobFitHeight,
    (const char*)kKnobCameraResolution,
    (const char*)kKnobLut1D,
    (const char*)kKnobLutTone,
    (const char*)kKnobEnhancer,
    (const char*)kKnobLut,
    (const char*)kKnobVignette,
    (const char*)kKnobTextelWidth,
    (const char*)kKnobTextelHeight,
    (const char*)kKnobInsetLeft,
    (const char*)kKnobInsetRight,
    (const char*)kKnobInsetTop,
    (const char*)kKnobInsetBottom,
    (const char*)kKnobInsetEnabled,
    (const char*)kKnobOverlayAlpha,
    (const char*)kKnobVignetteUser

    
};


static const float FXGlobalKnobsDefaults[] = {

    0.5,
    320,
    240,
    0,
    0.13777,


};


__unused static const char* FXGlobalKnobs[] = {
    
    (const char*)kKnobMix,
    (const char*)kKnobCanvasWidth,
    (const char*)kKnobCanvasHeight,
    (const char*)kKnobFrame,
    (const char*)kKnobNoise,

    
};


__unused static const char* FXCommonTextures[] = {
    
    "texture0",  
    "texture1",
    "texture2",
    "texture3", 
    "texture4", 
    "texture5", 
    "texture6", 
    "texture7", 
    "texture8", 
    "texture9", 
    
};


static const float FXCommonTexturesValues[] = {
    
    
    1,
    2,
    3, 
    4, 
    5, 
    6, 
    7, 
    8, 
    9, 
    0
    
};

__unused static const char* FXCommonAttributes[] = {
    
    "vertexPosition",  
    "vertexUV",

};


#define FX3GL_MAX_ATTRIBUTES        10

#define FX3GL_MAX_COMMON_UNIFORMS   61

#define FX3GL_MAX_COMMON_TEXTURES   10
#define FX3GL_MAX_COMMON_ATTRIBUTES 2
#define FX3GL_MAX_GLOBAL_KNOBS 		5
#define FX3GL_UNDEFINED		 		-1

/*math helpers*/


typedef float mat4[16];
// Pre-calculated value of PI / 180.
#define kPI180   0.017453

// Pre-calculated value of 180 / PI.
#define k180PI  57.295780

// Converts degrees to radians.
#define degreesToRadians(x) (x * kPI180)

// Converts radians to degrees.
#define radiansToDegrees(x) (x * k180PI)


#endif
