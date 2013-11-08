
#ifndef FX3MovieWriter_h
#define FX3MovieWriter_h


// this is a kind of template class
// will allocate appropiate platform specific codec

#include "../../PIPELINE/FX3Config.h"

#if IS_ANDROID
#include "Media/FX3MovieWriterFFMPEG.h"


class FX3MovieWriter : public FX3MovieWriterFFMPEG {

  public:

	   static char* builder();
};

#endif


#if IS_IOS || IS_OSX
#include "Media/FX3MovieWriterCOCOA.h"


class FX3MovieWriter : public FX3MovieWriterCOCOA {
    
public:
    
    static char* builder();
    
    FX3MovieWriter():FX3MovieWriterCOCOA(){};
};

#endif

#endif
