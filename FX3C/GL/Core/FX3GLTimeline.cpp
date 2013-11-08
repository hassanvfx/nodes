//
//  FX3GLTimeline.cpp
//  FX3Ctest
//
//  Created by hassanvfx on 30/10/12.
//  Copyright (c) 2012 hassanvfx. All rights reserved.
//

#include "FX3GLTimeline.h"

FX3GLTimeline::FX3GLTimeline(){

    _paused=false;
    _globalKnobs=nil;
    this->makeGlobalKnobs();
}



FX3Dictionary<char *, FX3GLKnob*> * FX3GLTimeline::globalKnobs()
{
    if(_globalKnobs==nil)
        _globalKnobs	= new FX3Dictionary < char * , FX3GLKnob *> (FX_KEYTYPE_CHARPTR);
    
	return _globalKnobs;
}


void FX3GLTimeline::updateGlobalKnobMix( float value )
{
	this->_globalKnobs->lookup( kKnobMix )->_float1 = value;
}



void FX3GLTimeline::makeGlobalKnobs()
{
    
	for(int i=0; i< FX3GL_MAX_GLOBAL_KNOBS; i++ ){
        
		char *knobName = 	(char*)FXGlobalKnobs[i];
		float val = 			FXGlobalKnobsDefaults[i];
        
		FX3GLKnob * knob = new FX3GLKnob( knobName, kKnobFloat1D );
		knob->_float1 = val;
		this->globalKnobs()->insert( knobName, knob );
        
	}
    
	this->firstFrame();
    
}





int FX3GLTimeline::getCurrentFrame(){
	return _currentFrame;
}
int  FX3GLTimeline::nextFrame(){
	_currentFrame=_currentFrame+1;
	this->_globalKnobs->lookup( kKnobFrame )->_float1 = (float)_currentFrame;
	this->_globalKnobs->lookup( kKnobNoise )->_float1 = (float)((arc4random() % 100)/100.0f);

    return _currentFrame;
}
int  FX3GLTimeline::firstFrame(){
	_isCanceled=false;
	_currentFrame =0;
    
    
	this->_globalKnobs->lookup( kKnobFrame )->_float1 = (float)_currentFrame;
	this->_globalKnobs->lookup( kKnobNoise )->_float1 = (float)((arc4random() % 100)/100.0f);
     return _currentFrame;
    
}


bool FX3GLTimeline::isCanceled(){
	return _isCanceled;
}

void  FX3GLTimeline::cancel(){
	_isCanceled=true;
   
}


CMTime FX3GLTimeline::getCurrentProviderTime(){
    return _currentProviderTime;
}

void FX3GLTimeline::setCurrentProviderTime(CMTime t){
    _currentProviderTime = t;
    
}

/*CMTimeSubtract(this->timeline()->getTimelineTime(),
 //                                       origin);*/

CMTime FX3GLTimeline::getTimelinePlayhead(){
    CMTime playtime = CMTimeSubtract(_timelineCurrent, _timelineOrigin);
    //playtime = CMTimeSubtract(playtime, _pausedTime);
    return playtime; 
}


CMTime FX3GLTimeline::getTimelineTime(){
    return _timelineCurrent; //todo
}

void FX3GLTimeline::setTimelineTime(CMTime t){
    _timelineCurrent = t;
    
    
}



CMTime FX3GLTimeline::getTimelineOrigin(){
    return _timelineOrigin;
    
}

void FX3GLTimeline::setTimelineOrigin(CMTime newTime){
    _timelineOrigin = newTime;
    //_pausedTime= kCMTimeZero;
    _paused=false;
}


void FX3GLTimeline::setTimelineOriginWithOffset(CMTime newTime,CMTime offset){
    _timelineOrigin = CMTimeSubtract(newTime, offset);
    //_pausedTime= kCMTimeZero;
    _paused=false;
}

bool FX3GLTimeline::isTimelinePause(){
    return _paused;
}

void FX3GLTimeline::setTimelinePaused(){
    //_pauseStart = newTime;
    _paused=true;
}
/*
void FX3GLTimeline::setTimelineResume(CMTime newTime){
    
    if(!_paused)
        return;
    
     _paused=false;
    //_pauseEnd=newTime;
 
    this->setTimelineOriginWithOffset(_timelineCurrent, newTime);
    return;
    
    //CMTime pauseLapse = CMTimeSubtract(_pauseEnd, _pauseStart);
   // _pausedTime = CMTimeAdd( _pausedTime, pauseLapse);
    
   
}*/
