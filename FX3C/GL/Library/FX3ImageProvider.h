
#ifndef FX3ImageProvider_h
#define FX3ImageProvider_h


// this is a kind of template class
// will allocate appropiate platform specific codec
// it would be required to nest all android codec into FX3ImageProviderAndroid > JPG > PNG later

#include "../../PIPELINE/FX3Config.h"

#if IS_ANDROID
#include "Media/FX3ImageProviderPNG.h"


class FX3ImageProvider : public FX3ImageProviderPNG {

  public:

	   static char* builder();
};

#endif



#if IS_IOS || IS_OSX


#include "Media/FX3ImageProviderCOCOA.h"


class FX3ImageProvider : public FX3ImageProviderCOCOA {


  public:

	   static char* builder();
};



#endif
#endif
