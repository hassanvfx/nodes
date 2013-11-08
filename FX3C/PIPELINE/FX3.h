//
//  FX3.h
//  FXLab2
//
//  Created by hassanvfx on 7/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef FXLab2_FX3_h
#define FXLab2_FX3_h


__unused static NSString *FX3_GENERIC_ERROR=@"FX3_GENERIC_ERROR";
__unused static NSString *FX3_UNKNOWN_ERROR=@"FX3_UNKNOWN_ERROR";
__unused static NSString *FX3_ERROR_DECRIPTION=@"FX3_ERROR_DECRIPTION";


#include "FX3Config.h"
#include "FX3Constants.h"

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>


#if IS_ANDROID
#include <android/log.h>
// logging
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#endif


#if IS_IOS

//#define  LOGI(fmt, ...)  FX3Log((@"FXLOG > " fmt @"%s \n [Line %d]" ), ##__VA_ARGS__, __PRETTY_FUNCTION__, __LINE__);
//#define  LOGE(fmt, ...)  FX3Log((@"FXLOG > " fmt @"%s \n [Line %d] " ), ##__VA_ARGS__, __PRETTY_FUNCTION__, __LINE__);

#define LOGI(...)
#define LOGE(...)
//#define  LOGI(fmt, ...)  do { } while(0)
//#define  LOGE(fmt, ...)  do { } while(0)



#endif

#endif


