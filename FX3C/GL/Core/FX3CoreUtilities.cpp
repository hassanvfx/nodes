//
//  FXCoreUtilities.cpp
//  FX3C
//
//  Created by Brent Rabowsky on 7/27/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//


#include "FX3CoreUtilities.h"

#include <string.h>
#include <ctype.h>



#define LOG_TAG "FX3CoreUtilities"





// STRING HANDLING METHODS ==============================================


int FX3CoreUtilities::substringSearch( char p[], char t[] )
{
    if ( !p || !t )
        return -1;
    
    int lenP = strlen( p );
    int lenT = strlen( t );
    int lastPos = lenT - lenP;
    if ( lastPos < 0 )
        return -1;  // target is less than pattern, can't contain it
    
    // to reduce comparisons, see if the LAST letter in the pattern matches,
    // then skip ahead lenP positions if no match
    int i = 0;
    while ( i <= lastPos )
    {
        if ( p[lenP - 1] == t[i+(lenP-1)] )
        {
            bool noMatch = false;
            for ( int j = 0, k = i; j < lenP; ++j, ++k ) {
                if ( p[j] != t[k] ) {
                    noMatch = true;
                    break;
                }
            }
            
            if ( !noMatch )
                return i;
            else
                i += lenP - 1;
        }
        else
            ++i;
    }
    
    return -1;
}


FX3Tokenized * FX3CoreUtilities::stringTokenizer( char string[], char * delimiter )
{
    FX3Tokenized * tokens = NULL;
    tokens = new FX3Tokenized;
    if ( !tokens ) {
        return NULL;
    }
    tokens->_delimiter = delimiter;
    tokens->_numComponents = 0;
    char * copy1 = strdup( string );

    // determine the number of components so can dynamically allocate
    // an array to hold each token
    char *pch = strtok( copy1, delimiter );
    if ( !pch ) {
        free(copy1);
        return NULL;
    }

    while ( pch != NULL ) {
        ++(tokens->_numComponents);
        pch = strtok( NULL, delimiter );
    }
    
    tokens->_components = new char*[tokens->_numComponents];
    
    // now add tokens to the array to be returned
    char * copy2 = strdup( string );
    char * pch2 = strtok( copy2, delimiter );
    int i = 0;
    while ( pch2 != NULL )
    {
        char * nextToken = strdup( pch2 );
        tokens->_components[i] = nextToken;
        ++i;
        pch2 = strtok( NULL, delimiter );
    }
    
    free( copy1 );
    free( copy2 );
    
    return tokens;
}


char * FX3CoreUtilities::convertToAlphaOnly( char * s )
{
	int len = strlen( s );
	char * out = (char *)malloc( sizeof(char) * ( len + 1 ) );
	int i;
	for ( i = 0; i < len; ++i )
	{
		if ( isalpha( s[i] ) || i == 2 )  // i == 2 saves the 3 in 'FX3 . . . '
			out[i] = s[i];
		else 
			break;
		
	}
	
	out[i] = '\0';
	
	return out;	
}






// URL ENCODING & DECODING ==============================================


static char hexa[]={"0123456789ABCDEFabcdef"};
static char nonencode[]={"abcdefghijklmnopqrstuvwqyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789/\\"};

static int GetHex(char val){
    int i;
    for(i=0;hexa[i];i++){
        if(hexa[i]==val){
            if(i>15){ return i-6; }
            return i;
        }
    }
    return -1;
}


void FX3CoreUtilities::URLDecode(char* dest,int len,char* source){
    int destc=0,i;
    for(i=0;destc+1<len&&source[i];i++){
        if(source[i]=='%'&&(GetHex(source[i+1])>=0&&GetHex(source[i+2])>=0)){
            dest[destc]=GetHex(source[i+1])<<4|GetHex(source[i+2]);
            i+=2;
        }
        else if(source[i]=='+'){
            dest[destc]=' ';
        }
        else{
            dest[destc]=source[i];
        }
        destc++;
    }
    dest[destc]='\0';
}


void FX3CoreUtilities::URLEncode(char* dest,int len,char* source){
    int destc=0,i,a,clear=0;
    for(i=0;destc+1<len&&source[i];i++){
        clear=0;
        for(a=0;nonencode[a];a++){
            if(nonencode[a]==source[i]){
                clear=1;
                break;
            }
        }
        if(!clear){
            if(destc+3>=len){
                break;
            }
            dest[destc]='%';
            dest[destc+1]=hexa[source[i]/16];
            dest[destc+2]=hexa[source[i]%16];
            destc+=3;
        }
        else{
            dest[destc]=source[i];
            destc++;
        }
    }
    dest[destc]='\0';
}






// DEBUGGING & ERROR CHECKING METHODS ===============================================


int FX3CoreUtilities::pngWriteSnapshot(char* filename, int width, int height, uint8_t *buffer, char* title)
{
    
#if IS_ANDROID
	int code = 0;
	FILE *fp;
	png_structp png_ptr;
	png_infop info_ptr;
	png_bytep row;
	
	uint8_t * curPtr = buffer;
	
	
	// Open file for writing (binary mode)
	fp = fopen(filename, "wb");
	if (fp == NULL) {
		LOGE("Could not open file %s for writing", filename);
		code = 1;
		goto finalise;
	}

	// Initialize write structure
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		LOGE("Could not allocate write struct");
		code = 1;
		goto finalise;
	}

	// Initialize info structure
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		LOGE("Could not allocate info struct");
		code = 1;
		goto finalise;
	}

	// Setup Exception handling
	if (setjmp(png_jmpbuf(png_ptr))) {
		LOGE("Error during png creation");
		code = 1;
		goto finalise;
	}

	png_init_io(png_ptr, fp);

	// Write header (8 bit color depth)
	png_set_IHDR(png_ptr, info_ptr, width, height,
			8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,       // for RGB change to PNG_COLOR_TYPE_RGB
			PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	// Set title
	if (title != NULL) {
		png_text title_text;
		title_text.compression = PNG_TEXT_COMPRESSION_NONE;
		title_text.key = "Title";
		title_text.text = title;
		png_set_text(png_ptr, info_ptr, &title_text, 1);
	}

	png_write_info(png_ptr, info_ptr);
/*
	// Allocate memory for one row (3 bytes per pixel - RGB)
	row = (png_bytep) malloc(3 * width * sizeof(png_byte));

	// Write image data
	for (int y = 0 ; y < height ; y++) {
		int outPtr = 0, inPtr = 0;
		for (int x = 0 ; x < width ; x++) {
			outPtr = x * 3;
			row[outPtr] = buffer[y*width + inPtr];
			row[outPtr+1] = buffer[y*width + inPtr + 1];
			row[outPtr+2] = buffer[y*width + inPtr + 2];	
			inPtr += 4;		
		}
		png_write_row(png_ptr, row);
	}
*/
	// Allocate memory for one row (4 bytes per pixel - RGBA)
	row = (png_bytep) malloc(4 * width * sizeof(png_byte));
	// Write image data
	for (int y = 0 ; y < height ; y++) {
		memcpy( row, curPtr, width*4 );	
		png_write_row(png_ptr, row);
		curPtr += width * 4;
	}

	// End write
	png_write_end(png_ptr, NULL);

	finalise:
	if (fp != NULL) fclose(fp);
	if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
	if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
	if (row != NULL) free(row);

	return code;
#endif
    
    return 0;
}


void FX3CoreUtilities::checkGlError(const char* op) 
{
    for (GLint error = glGetError(); error; error
         = glGetError()) {
        LOGE("after %s() glError (0x%x)\n", op, error);
    }
}







