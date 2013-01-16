//
//  TestObject.h
//  SHMUP
//
//  Created by Alexis Tio on 1/15/13.
//
//

#ifndef __SHMUP__TestObject__
#define __SHMUP__TestObject__

#include "cocos2d.h"
#include "ControlledObject.h"
#include "CommonFunctions.h"

class TestObject : public cocos2d::CCNode, ControlledObject {
private:
    cocos2d::CCSprite * m_Sprite;
    
public:
    virtual bool init();
    CREATE_FUNC( TestObject );
    
    virtual void onStickMoved( float p_Distance, float p_Angle, StickDirection p_Direction );
    virtual void onStickReset();
    virtual void onButtonPress( int p_ID );
    virtual void onButtonUnpress( int p_ID );
    
    void doFadeEnd( cocos2d::CCObject * p_Sender );
};

#endif /* defined(__SHMUP__TestObject__) */
