//
//  FX3GLTimeline.h
//  FX3Ctest
//
//  Created by hassanvfx on 30/10/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//

#ifndef __FX3Ctest__FX3GLTimeline__
#define __FX3Ctest__FX3GLTimeline__


#include "../FX3GL.h"
#include "../../PIPELINE/FX3Dictionary.h"
#include <CoreMedia/CoreMedia.h>

class FX3GLTimeline {
public:
    
    FX3GLTimeline();
    CMTime _currentProviderTime;
    void setCurrentProviderTime(CMTime newTime);
    CMTime getCurrentProviderTime();
    
    CMTime _timelineCurrent;
    void setTimelineTime(CMTime);
    CMTime getTimelineTime();
    CMTime getTimelinePlayhead();
    
    CMTime _timelineOrigin;
    CMTime getTimelineOrigin();
    void setTimelineOrigin(CMTime newTime);
    void setTimelineOriginWithOffset(CMTime newTime,CMTime offset);
    
    
    //CMTime _pausedTime;
    ////CMTime _pauseStart;
    //CMTime _pauseEnd;
    bool _paused;
    bool isTimelinePause();
    void setTimelinePaused();
   // void setTimelineResume(CMTime newTime);
    
    FX3Dictionary<char *, FX3GLKnob*> *_globalKnobs;
	FX3Dictionary<char *, FX3GLKnob*> *globalKnobs();
	void updateGlobalKnobMix( float value );
	void makeGlobalKnobs();
    
	int _currentFrame;
	int getCurrentFrame();
	int nextFrame();
	int firstFrame();
    
	bool isCanceled();
	bool _isCanceled;
	void cancel();
    
};
#endif /* defined(__FX3Ctest__FX3GLTimeline__) */
