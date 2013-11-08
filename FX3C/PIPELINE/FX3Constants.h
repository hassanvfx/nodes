//
//  FX3Constants.h
//  FX3C
//
//  Created by hassan vfx on 26/07/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//

#ifndef FX3C_FX3Constants_h
#define FX3C_FX3Constants_h


#define _HOST_OSX
//--#define _HOST_IOS
//--#define _HOST_ANDROID


#define FX3_MAX_NODES 100
#define FX3_MAX_INPUTS 10
#define FX3_MAX_DICTIONARY_ITEMS 20
#define FX3_UNDEFINED -1

#define kKnobIntensity "knobIntensity"
#define kKnobMin "knobMin"
#define kKnobMax "knobMax"
#define kKnobMix "knobMix"


#define FX3_MAX_OBJECTS   1000
#define FX3_NAME_SIZE     100
// TODO:  move to FX3GLConstants
typedef enum {
    
    kKnobUndefined  =   0,
    kKnobString     =   1,
    kKnobFloat1D    =   2,
    kKnobFloat2D    =   3,
    kKnobFloat3D    =   4,
    kKnobFloat4D    =   5,
    kKnobSampler2D  =   6,
	
} FX3KnobType;

#endif
