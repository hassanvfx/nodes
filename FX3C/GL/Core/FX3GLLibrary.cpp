//
//  FX3GLLibrary.cpp
//  FXLab2
//
//  Created by hassan vfx on 05/08/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//


#include "FX3GLLibrary.h"



#include "FX3JSONBuilder.h"
#include "FX3CoreUtilities.h"


#define LOG_TAG "FX3GLLibrary"



FX3GLLibrary *FX3GLLibrary::_shared=NULL;

FX3GLLibrary * FX3GLLibrary::shared(){
    
    if(_shared == NULL){
        _shared= new FX3GLLibrary();
        _shared->_libraryRegistered=false;
    }
    
    return _shared;
    
}

FX3Node* FX3GLLibrary::makeNodeFactory( char *className){
    



    /*
     
     CROSS PLATFORM  OPERATORS
     
     */
    

    if( strcmp( className, FX3VisionShader::builder() ) == 0 ){
        return new FX3VisionShader();
    }
    
    if( strcmp( className, FX3Solid::builder() ) == 0 ){
        return new FX3Solid();
    }
    
    else  if( strcmp( className, FX3Generator::builder() ) == 0 ){
          return new FX3Generator();
      }

    else  if( strcmp( className, FX3RenderBuffer::builder() ) == 0 ){
        return new FX3RenderBuffer();
    }
    
    else  if( strcmp( className, FX3Add::builder() ) == 0 ){
           return new FX3Add();
      }


    else  if( strcmp( className, FX3Resize::builder() ) == 0 ){
           return new FX3Resize();
      }      
      
    else  if( strcmp( className, FX3ResizeWithAspect::builder() ) == 0 ){
           return new FX3ResizeWithAspect();
      }      
 
    else  if( strcmp( className, FX3Fit::builder() ) == 0 ){
           return new FX3Fit();
      } 

    else  if( strcmp( className, FX3FitOrient::builder() ) == 0 ){
                 return new FX3FitOrient();
            }

    else  if( strcmp( className, FX3FitOrientScanTransform::builder() ) == 0 ){
        return new FX3FitOrientScanTransform();
    }
    
    else  if( strcmp( className, FX3Orient::builder() ) == 0 ){
                 return new FX3Orient();
            }

    else  if( strcmp( className, FX3AlphaAtlas::builder() ) == 0 ){
               return new FX3AlphaAtlas();
          }

    /*
     *
     * MEDIA DYNAMIC TEMPLATED CLASSES
     *
     */

    else  if( strcmp( className, FX3ImageProvider::builder() ) == 0 ){
          return new FX3ImageProvider();
    }
    else  if( strcmp( className, FX3MovieProvider::builder() ) == 0 ){
             return new FX3MovieProvider();
       }
    else  if( strcmp( className, FX3MovieWriter::builder() ) == 0 ){
             return new FX3MovieWriter();
       }

    /*
         
    PLATFORM SPECIFIC OPERATORS
         
    */
        
#if IS_MAC
    else  if( strcmp( className, FX3RenderViewOSX::builder() ) == 0 ){
        return new FX3RenderViewOSX();
    }
#endif
        
#if IS_IOS
    else  if( strcmp( className, FX3RenderViewIOS::builder() ) == 0 ){
        return new FX3RenderViewIOS();
    }
    
    else  if( strcmp( className, FX3CameraIOS::builder() ) == 0 ){
        return new FX3CameraIOS();
    }
//    else  if( strcmp( className, FX3CameraYUVIOS::builder() ) == 0 ){
//        return new FX3CameraYUVIOS();
//    }
    
    else  if( strcmp( className, FX3YUV2RGB::builder() ) == 0 ){
        return new FX3YUV2RGB();
    }
#endif
        
#if IS_ANDROID   
 
	else  if( strcmp( className, FX3RenderViewAndroid::builder() ) == 0 ){
        return new FX3RenderViewAndroid();
    }
    
    // TODO : THIS RAW AND OTHER SPECIFIC CLASSES SHOULD NOT BE EXPOSED IN HERE ....

       else  if( strcmp( className, FX3ImageProviderTGA::builder() ) == 0 ){
              return new FX3ImageProviderTGA();
         }


       else  if( strcmp( className, FX3ImageProviderPNG::builder() ) == 0 ){
              return new FX3ImageProviderPNG();
         }

       else  if( strcmp( className, FX3MovieProviderRAW::builder() ) == 0 ){
              return new FX3MovieProviderRAW();
         }

       else  if( strcmp( className, FX3MovieProviderFFMPEG::builder() ) == 0 ){
              return new FX3MovieProviderFFMPEG();
         }

       else  if( strcmp( className, FX3MovieWriterRAW::builder() ) == 0 ){
              return new FX3MovieWriterRAW();
         }

       else  if( strcmp( className, FX3MovieWriterFFMPEG::builder() ) == 0 ){
              return new FX3MovieWriterFFMPEG();
         }

    
#endif
 

    LOGE("FXLog: LIBRARY ERROR: Cannot find constructor for %s will use FX3Shader  for baseclass ",className);


    return new FX3Shader();

    
}


/*
 *
 * plugin engine
 *
 */

FX3Dictionary<char*, FX3Plugin *> * FX3GLLibrary::plugins(){

	if( this->_plugins == NULL){
		this->_plugins =  new FX3Dictionary<char*, FX3Plugin *>( FX_KEYTYPE_CHARPTR );
	}
	
	return this->_plugins;
}


void FX3GLLibrary::registerJSONLibrary( char* json ){
    
    if(_libraryRegistered)
        return;
    
	LOGE("preparing to load library at %s", json );
	FX3JSONBuilder * builder = new FX3JSONBuilder();
	builder->createJSONObjectFromString( json, true );
	builder->buildPluginLibrary();

	delete builder;
}


/*
 *
 *
 *
 */




FX3Shader* FX3GLLibrary::makeShader( char *className, char *fragment, char *vertex){

	LOGI("FXLog: makeNode %s %s %s",className,fragment, vertex);

	FX3Plugin *plugin = (FX3Plugin *)this->plugins()->lookup(className);

	if(plugin!=NULL){

		LOGI("FXLog: makeNode using virtual class %s -> %s",className, plugin->builder() );
		//if we are using a plugin we change the classname to be one of the real base classess
		className = plugin->builder();

	}

	FX3Shader *result = (FX3Shader*)this->makeNodeFactory(className);

	if(plugin!=NULL){

		// handle the virtual class overriding
		if(plugin->_fragmentShader!=NULL){
		    	result->setFragmentShader(plugin->_fragmentShader);
		}

		if(plugin->_vertexShader!=NULL){
		    	result->setVertexShader(plugin->_vertexShader);
		}

		// loop for the plugin default knobs and assign the default knobs
		// for each knob in plugin create a knob in the resulting node
    	FX3TableEntry< char *, FX3Knob*> **entries = plugin->knobs()->getEntries();
 
	    for (int i = 0; i <  plugin->knobs()->getCount() ; ++i) {
	        
	        FX3TableEntry< char *, FX3Knob*> *item = entries[i];
	        FX3GLKnob * knob = (FX3GLKnob *)item->value;
			result->createKnob( knob->_NAME, knob->_type, knob->_float1);
	    }
	    
	    delete [] entries;		

	}

	// handle specific instance overriding

    if(fragment!=NULL){
    		result->setFragmentShader(fragment);
    }

    if(vertex!=NULL){
    		result->setVertexShader(vertex);
    }

    return (FX3Shader*)result;
}


FX3Shader* FX3GLLibrary::makeShaderWithJSONName( char *className, char *fragment, char *vertex, char * jsonName ){

	LOGI("FXLog: makeNode %s %s %s",className,fragment, vertex);
	
	FX3Plugin *plugin = (FX3Plugin *)this->plugins()->lookup( className );

	if(plugin!=NULL){

		LOGI("FXLog: makeNode using virtual class %s -> %s",className, plugin->builder() );
		//if we are using a plugin we change the classname to be one of the real base classess
		className = plugin->builder();

	}

	FX3Shader *result = (FX3Shader*)this->makeNodeFactory(className);

	if(plugin!=NULL){

		// handle the virtual class overridin
		if(plugin->_fragmentShader!=NULL){
		    	result->setFragmentShader(plugin->_fragmentShader);
		}

		if(plugin->_vertexShader!=NULL){
		    	result->setVertexShader(plugin->_vertexShader);
		}

		// loop for the plugin default knobs and assign the default knobs
		// for each knob in plugin create a knob in the resulting node

    	FX3TableEntry< char *, FX3Knob*> **entries = plugin->knobs()->getEntries();


    		// TODO THIS IS UNAFE IN CASE OF RECEIVING AN STRING ....
		// this is making nuts the pipe then disable temp
    	    // reenabled on sept 22, the error is in FXDictonary replace , it was patched

	    for (int i = 0; i <  plugin->knobs()->getCount() ; ++i) {
	        
	        FX3TableEntry< char *, FX3Knob*> *item = entries[i];
	        FX3GLKnob * knob = (FX3GLKnob *)item->value;
			result->createKnob( knob->_NAME, knob->_type, knob->_float1);
	    }
	    
	    delete [] entries;
	}

	// handle specific instance overriding

    if(fragment!=NULL){
    		result->setFragmentShader(fragment);
    }

    if(vertex!=NULL){
    		result->setVertexShader(vertex);
    }

    return (FX3Shader*)result;
}

