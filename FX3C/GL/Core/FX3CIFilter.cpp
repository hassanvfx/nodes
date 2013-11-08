//
//  FX3CIFilter.cpp
//  FX3Ctest
//
//  Created by hassanvfx on 11/10/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//

#include "FX3CIFilter.h"


char* FX3CIFilter:: builder(){
    return (char *)"FX3CIFilter";
    
}

int FX3CIFilter::render(){
    if( !this->linkToInputTexture()){
        return FX3Shader::render();
    }
    
    this->renderCoreImage();
    
    return outputTexture;
}



bool FX3CIFilter::linkToInputTexture(){
    
    _linkToOutputTexture=false;
    
    FX3Shader *input =  (FX3Shader *)this->_inputs[0];
    
    if( input!=NULL){
        if(input->_videoCVTexture!=nil){
               input->render();
            _videoCVBuffer  = input->_videoCVBuffer;
            _videoCVTexture = input->_videoCVTexture;
            outputTexture   =  input->outputTexture;
            _linkToOutputTexture = true;
        }
    }
    
    
    
    return _linkToOutputTexture;
    
}

void FX3CIFilter::renderCoreImage(){
   
   CIImage *myImage = [CIImage imageWithCVPixelBuffer:this->_videoCVBuffer   ];
 /*
    ///Volumes/TITAN1/viddy/VD-IOS/ios/tags/2.0.H2/FX3Ctest2/FX3Ctest/external/FX3/FX3C/GL/Core/FX3CIFilter.cpp:55:64: Cannot initialize a parameter of type 'NSString *' with an lvalue of type 'const CFStringRef' (aka 'const __CFString *const')
   
    NSDictionary *options = [NSDictionary dictionaryWithObject:
                             
                             [NSNumber numberWithInt:1]
                                                        forKey:CIDetectorImageOrientation];
    
    NSArray *adjustments = [myImage autoAdjustmentFiltersWithOptions:options];
    
    for (CIFilter *filter in adjustments){
        [filter setValue:myImage forKey:kCIInputImageKey];
        myImage = filter.outputImage;
        
    }
    */
   
    CIFilter *toneCurveFilter = [CIFilter filterWithName:@"CIToneCurve"];
    [toneCurveFilter setDefaults];
    [toneCurveFilter setValue:myImage forKey:kCIInputImageKey];
    [toneCurveFilter setValue:[CIVector vectorWithX:0.0  Y:0.0] forKey:@"inputPoint0"]; // default
    [toneCurveFilter setValue:[CIVector vectorWithX:0.27 Y:0.26] forKey:@"inputPoint1"];
    [toneCurveFilter setValue:[CIVector vectorWithX:0.5  Y:0.80] forKey:@"inputPoint2"];
    [toneCurveFilter setValue:[CIVector vectorWithX:0.7  Y:1.0] forKey:@"inputPoint3"];
    [toneCurveFilter setValue:[CIVector vectorWithX:1.0  Y:1.0] forKey:@"inputPoint4"]; // default
    
    myImage =[toneCurveFilter outputImage    ];
   
}