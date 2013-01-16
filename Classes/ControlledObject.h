//
//  ControlledObject.h
//  VirtualController
//
//  Created by Lance Gray on 1/15/13.
//
//

#ifndef __VirtualController__ControlledObject__
#define __VirtualController__ControlledObject__

#include "cocos2d.h"
#include "VirtualControllerCommons.h"

class ControlledObject {
public:
    virtual void onStickMoved( float p_Distance, float angle, StickDirection p_Direction ) {}
    virtual void onStickReset() {}
    virtual void onButtonPress( int p_ID ) {}
    virtual void onButtonMoved( int p_ID ) {}
    virtual void onButtonHeld( int p_ID ) {}
    virtual void onButtonUnpress( int p_ID ) {}
};

#endif /* defined(__VirtualController__ControlledObject__) */
