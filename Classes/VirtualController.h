//
//  VirtualController.h
//  VirtualController
//
//  Created by Alexis Tio on 1/15/13.
//
//

#ifndef __SHMUP__VCDPad__
#define __SHMUP__VCDPad__

#include "cocos2d.h"
#include "ControlledObject.h"
#include "CommonFunctions.h"

class VirtualController : public cocos2d::CCLayerColor {
private:
    float m_StickRadius;
    StickDirection m_StickDirection;
    
    ControlledObject * m_ControlledObject;    
    cocos2d::CCDictionary m_TouchedObjects;

    cocos2d::CCArray * m_PadButtons;
    cocos2d::CCSprite * m_PadStick;
    
    cocos2d::CCPoint m_DefaultStickPosition;
    cocos2d::CCPoint m_DefaultPosition;
    cocos2d::CCSize m_DefaultSize;
    cocos2d::ccColor4B m_DefaultColor;

public:
    // Constructors
    VirtualController();
    ~VirtualController();
    
    // Initialization
    static VirtualController * create( ControlledObject * p_Target );
    bool init( ControlledObject * p_Target );
    
    // Draw Methods
    void drawLayer();
    
    // Update Methods
    void updateVirtualController();
    void updateStick();
    
    // Getter Methods
    StickDirection getDirection();
    
    // Setter Methods
    void setStickDirectionAuto( float p_Angle );
    
    // Touch Handlers
    virtual void ccTouchesBegan( cocos2d::CCSet * touches, cocos2d::CCEvent * event );
    virtual void ccTouchesMoved( cocos2d::CCSet * touches, cocos2d::CCEvent * event );
    virtual void ccTouchesEnded( cocos2d::CCSet * touches, cocos2d::CCEvent * event );
    
    // Movement Methods
    void vcStickMoved( cocos2d::CCPoint p_NewPos );
    void vcStickReset();
    void vcButtonPressed( int p_ID );
    void vcButtonMoved( int p_ID );
    void vcButtonHeld( int p_ID );
    void vcButtonUnpressed( int p_ID );
    
    // Animation Methods
    void moveStickSprite( float p_PosX, float p_PosY );
    
    // Callback Methods
    
    // Creation Methods
    void addButton( cocos2d::CCSprite * p_Button );
    void removeButton( unsigned int p_ButtonID );
    
    // Helper Methods
    float calculateAngleFromOrigin( float p_PointX, float p_PointY );
    float calculateHypotenuse( float p_ValA, float p_ValB );
    float calculateDistanceBetweenPoints( cocos2d::CCPoint p_PointA, cocos2d::CCPoint p_PointB );
    float calculateDegreesOfTwoPoints( cocos2d::CCPoint p_PointA, cocos2d::CCPoint p_PointB );
    float calculateRadiansOfTwoPoints( cocos2d::CCPoint p_PointA, cocos2d::CCPoint p_PointB );
};

#endif /* defined(__SHMUP__VCDPad__) */
