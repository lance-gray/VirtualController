//
//  ControlledObject.h
//  SHMUP
//
//  Created by Alexis Tio on 1/15/13.
//
//

#ifndef __SHMUP__ControlledObject__
#define __SHMUP__ControlledObject__

#include "cocos2d.h"
#include "CommonFunctions.h"

class ControlledObject {
public:
    virtual void onStickMoved( float p_Distance, float angle, StickDirection p_Direction ) {}
    virtual void onStickReset() {}
    virtual void onButtonPress( int p_ID ) {}
    virtual void onButtonUnpress( int p_ID ) {}
};

#endif /* defined(__SHMUP__ControlledObject__) */
