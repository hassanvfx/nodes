//
//  FX3Context.h
//  FXLab2
//
//  Created by hassanvfx on 8/7/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef FXLab2_FX3Context_h
#define FXLab2_FX3Context_h


class FX3Context{
    
public:
    
    
    static FX3Context *_shared;
    static FX3Context *shared();
    
    //FX3Dictionary *_objects();

    int _objectsCount;
    
    int  createID(); 
    
    
    
    FX3Context();
    ~FX3Context();
};



#endif
