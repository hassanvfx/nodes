
#ifndef FX3MovieProvider_h
#define FX3MovieProvider_h


// this is a kind of template class
// will allocate appropiate platform specific codec

#include "../../PIPELINE/FX3Config.h"

#if IS_ANDROID
#include "Media/FX3MovieProviderFFMPEG.h"


class FX3MovieProvider : public FX3MovieProviderFFMPEG {

  public:

	   static char* builder();
};

#endif


#if IS_IOS || IS_OSX
#include "Media/FX3MovieProviderCOCOA.h"


class FX3MovieProvider : public FX3MovieProviderCOCOA {
    
public:
    
    static char* builder();
    FX3MovieProvider():FX3MovieProviderCOCOA(){};
};

#endif


#endif
