//
//  FXCoreUtilities.h
//  FX3C
//
//  Created by Brent Rabowsky on 7/27/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//

#ifndef FX3C_FXCoreUtilities_h
#define FX3C_FXCoreUtilities_h

#include "../FX3GL.h"

#if IS_ANDROID
extern "C" {
	#include <png.h>
}
#endif



// utility class for an object returned by the stringTokenizer method below

class FX3Tokenized {
    
  public:
    
    int _numComponents;
    char * _delimiter;
    char ** _components;
    
    ~FX3Tokenized() {
        if ( _numComponents > 0) {
            for ( int i = 0; i < _numComponents; ++i )
                delete [] _components[i];
        }
        if ( _components )
            delete [] _components;
    }
    
    FX3Tokenized() {
        _numComponents = 0;
        _delimiter = NULL;
        _components = NULL;
    }
    
};


class FX3CoreUtilities  {
    
    
  public:
    
    // STRING HANDLING METHODS ==============================================
     
    static int substringSearch( char p[], char t[] );
    
    static FX3Tokenized * stringTokenizer( char string[], char * delimiter );

	/// @deprecated converts e.g. "FX3RedShader32" to "FX3RedShader"    
    static char * convertToAlphaOnly( char * s );
    
    
    
    // URL ENCODING & DECODING ==============================================
    
    static void URLDecode(char* dest, int len, char* source);
    
    static void URLEncode(char* dest, int len, char* source);
    
    
    
    // DEBUGGING & ERROR CHECKING METHODS ===============================================
    
    // write a snapshot of the current pixel buffer to sd card or wherever specified by filename  
   
    static int pngWriteSnapshot(char* filename, int width, int height, uint8_t *buffer, char* title);

    static void checkGlError(const char* op);
    
   
};


#endif
