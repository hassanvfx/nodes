



#include "FX3Plugin.h"



#define LOG_TAG "FX3Plugin"


FX3Plugin::FX3Plugin(){

	_alias		= NULL;
	_builder	 	= NULL;
	_fragmentShader = NULL;
	_vertexShader = NULL;

}

FX3Plugin::~FX3Plugin( ){

	free(_alias);
	free(_builder);


}


// accessors

char * FX3Plugin::alias()
{
	return _alias;

}


char * FX3Plugin::builder()
{
	return _builder;
}
    
    
void FX3Plugin::setAlias( char * a )
{
	_alias = a;
}


void FX3Plugin::setBuilder( char * b )
{
	_builder = b;
}




