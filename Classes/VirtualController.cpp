//
//  VirtualController.cpp
//  VirtualController
//
//  Created by Alexis Tio on 1/15/13.
//
//

#include "VirtualController.h"

using namespace cocos2d;

#define dist( p1, p2 ) calculateDistanceBetweenPoints( p1, p2 )
#define  deg( p1, p2 ) calculateDegreesOfTwoPoints( p1, p2 )
#define  rad( p1, p2 ) calculateRadiansOfTwoPoints( p1, p2 )

#pragma mark -
#pragma mark Constructors
VirtualController::VirtualController() {
    m_ControlledObject = NULL;
    m_PadStick = NULL;
    m_DefaultStickPosition = CCPointZero;
    m_DefaultPosition = CCPointZero;
    m_DefaultSize = CCSizeZero;
    m_DefaultColor = ccc4( 255, 255, 255, 255 );
    m_StickRadius = 100;
}

VirtualController::~VirtualController() {
    if ( m_PadButtons ) {
        m_PadButtons -> release();
        m_PadButtons = NULL;
    }
}

#pragma mark -
#pragma mark Initialization
VirtualController * VirtualController::create( ControlledObject * p_Target ) {
    VirtualController * tempVC = new VirtualController();
    if ( tempVC && tempVC -> init( p_Target ) ) {
        tempVC -> autorelease();
        return tempVC;
    } else {
        delete tempVC;
        tempVC = NULL;
        return NULL;
    }
}

bool VirtualController::init( ControlledObject * p_Target ) {
    if ( !CCLayerColor::initWithColor( DEFAULT_COLOR() ) ) return false;
    
    m_ControlledObject = p_Target;
    m_DefaultStickPosition = CCPointMake( this -> getContentSize().width * 0.20f, this -> getContentSize().height * 0.30f );
    m_PadButtons = new CCArray();
    
    this -> drawLayer();
    this -> schedule( schedule_selector( VirtualController::updateVirtualController ) );
    
    CCDirector::sharedDirector() -> getTouchDispatcher() -> addStandardDelegate( this, 0 );
    
    return true;
}

#pragma mark -
#pragma mark Draw Methods
void VirtualController::drawLayer() {
    m_PadStick = CCSprite::create( "powerbutton.png" );
    m_PadStick -> setPosition( m_DefaultStickPosition );
    m_PadStick -> setScale( 3.0f );
    this -> addChild( m_PadStick );
}

#pragma mark -
#pragma mark Update Methods
void VirtualController::updateVirtualController() {
    this -> updateStick();
    this -> updateButtons();
}

void VirtualController::updateStick() {
    if ( m_StickDirection != StickDirectionNone ) {
        this -> vcStickMoved( m_PadStick -> getPosition() );
    } else {
        
    }
}

void VirtualController::updateButtons() {
    for ( int i = 0; i < m_ButtonFlags.size(); i++ ) {
        if ( m_ButtonFlags.at( i ) ) {
            this -> vcButtonHeld( i );
        }
    }
}

#pragma mark -
#pragma mark Getter Methods

#pragma mark -
#pragma mark SetterMethods
void VirtualController::setStickDirectionAuto( float p_Angle ) {
    float tempAngle = p_Angle;
    if ( tempAngle < 0 ) tempAngle = 360 + tempAngle;
    
    // RIGHT
    if ( ( tempAngle < 22.5f && tempAngle > 0.0f) || ( tempAngle < 360.0f && tempAngle > 337.5f ) ) {
        m_StickDirection = StickDirectionRight;
    }
    
    // UPPER-RIGHT
    else if ( tempAngle < 67.5f && tempAngle > 22.5f ) {
        m_StickDirection = StickDirectionUpRight;
    }
    
    // UP
    else if ( tempAngle < 112.5f && tempAngle > 67.5f ) {
        m_StickDirection = StickDirectionUp;
    }
    
    // UPPER-LEFT
    else if ( tempAngle < 157.5f && tempAngle > 112.5f ) {
        m_StickDirection = StickDirectionUpLeft;
    }
    
    // LEFT
    else if ( tempAngle < 202.5f && tempAngle > 157.5f ) {
        m_StickDirection = StickDirectionLeft;
    }
    
    // LOWER-LEFT
    else if ( tempAngle < 247.5f && tempAngle > 202.5 ) {
        m_StickDirection = StickDirectionDownLeft;
    }
    
    // DOWN
    else if ( tempAngle < 292.5f && tempAngle > 247.5f ) {
        m_StickDirection = StickDirectionDown;
    }
    
    // LOWER-RIGHT
    else if ( tempAngle < 337.5f && tempAngle > 292.5f ) {
        m_StickDirection = StickDirectionDownRight;
    }
    
    // Not Moving
    else {
        m_StickDirection = StickDirectionNone;
    }
}

#pragma mark -
#pragma mark Touch Handlers
void VirtualController::ccTouchesBegan( cocos2d::CCSet * touches, cocos2d::CCEvent * event ) {
    for ( CCSetIterator iterator = touches -> begin(); iterator != touches -> end(); iterator++ ) {
        CCTouch * touch = ( CCTouch * ) ( * iterator );
        if ( m_PadStick -> boundingBox().containsPoint( touch -> getLocation() ) ) {
            m_TouchedObjects.setObject( m_PadStick, touch -> getID() );
        } else {
            CCObject * it = NULL;
            CCARRAY_FOREACH( m_PadButtons, it ) {
                CCSprite * button = dynamic_cast< CCSprite * > ( it );
                if ( button -> boundingBox().containsPoint( touch -> getLocation() ) ) {
                    vcButtonPressed( m_PadButtons -> indexOfObject( it ) );
                }
            }
        }
    }
}

void VirtualController::ccTouchesMoved( cocos2d::CCSet * touches, cocos2d::CCEvent * event ) {
    for ( CCSetIterator iterator = touches -> begin(); iterator != touches -> end(); iterator++ ) {
        CCTouch * touch = ( CCTouch * ) ( * iterator );
        if ( m_TouchedObjects.objectForKey( touch -> getID() ) == m_PadStick ) {
            vcStickMoved( touch -> getLocation() );
        }
    }
}

void VirtualController::ccTouchesEnded( cocos2d::CCSet * touches, cocos2d::CCEvent * event ) {
    for ( CCSetIterator iterator = touches -> begin(); iterator != touches -> end(); iterator++ ) {
        CCTouch * touch = ( CCTouch * ) ( * iterator );
        if ( m_TouchedObjects.objectForKey( touch -> getID() ) == m_PadStick ) {
            m_TouchedObjects.removeObjectForKey( touch -> getID() );
            vcStickReset();
        } else {
            CCObject * it = NULL;
            CCARRAY_FOREACH( m_PadButtons, it ) {
                CCSprite * button = dynamic_cast< CCSprite * > ( it );
                if ( button -> boundingBox().containsPoint( touch -> getLocation() ) ) {
                    vcButtonUnpressed( m_PadButtons -> indexOfObject( it ) );
                }
            }
        }
    }
}

#pragma mark -
#pragma mark Movement Methods
void VirtualController::vcStickMoved( cocos2d::CCPoint p_NewPos ) {
    this -> moveStickSprite( p_NewPos.x, p_NewPos.y );
    if ( m_ControlledObject ) m_ControlledObject -> onStickMoved( dist( m_DefaultStickPosition, p_NewPos ), deg( m_DefaultStickPosition, p_NewPos ), m_StickDirection );
}

void VirtualController::vcStickReset() {
    m_PadStick -> setPosition( m_DefaultStickPosition );
    m_StickDirection = StickDirectionNone;
    if ( m_ControlledObject ) m_ControlledObject -> onStickReset();
}

void VirtualController::vcButtonPressed( int p_ID ) {
    CCSprite * button = ( CCSprite * ) m_PadButtons -> objectAtIndex( p_ID );
    button -> setScale( button -> getScale() + 0.20f );
    m_ButtonFlags.at( p_ID ) = true;
    
    if ( m_ControlledObject )
        m_ControlledObject -> onButtonPress( p_ID );
}

void VirtualController::vcButtonMoved( int p_ID ) {
    
}

void VirtualController::vcButtonHeld( int p_ID ) {
    if ( m_ControlledObject ) m_ControlledObject -> onButtonHeld( p_ID );
}

void VirtualController::vcButtonUnpressed( int p_ID ) {
    CCSprite * button = ( CCSprite * ) m_PadButtons -> objectAtIndex( p_ID );
    button -> setScale( button -> getScale() - 0.20f );
    m_ButtonFlags.at( p_ID ) = false;
    
    if ( m_ControlledObject )
        m_ControlledObject -> onButtonUnpress( p_ID );
}

#pragma mark -
#pragma mark Animation Methods
void VirtualController::moveStickSprite( float p_PosX, float p_PosY ) {
    float angleInRadians = rad( m_DefaultStickPosition, CCPointMake( p_PosX, p_PosY ) );
    float angleInDegrees = deg( m_DefaultStickPosition, CCPointMake( p_PosX, p_PosY ) );
    float distance = dist( m_DefaultStickPosition, CCPointMake( p_PosX, p_PosY ) );
    float newPosX = p_PosX;
    float newPosY = p_PosY;
    
    if ( distance > m_StickRadius ) {
        newPosX = m_DefaultStickPosition.x - cosf( angleInRadians ) * m_StickRadius;
        newPosY = m_DefaultStickPosition.y - sinf( angleInRadians ) * m_StickRadius;
    }
    
    m_PadStick -> setPosition( CCPointMake( newPosX, newPosY ) );
    m_PadStick -> setRotation( - angleInDegrees );
    
    this -> setStickDirectionAuto( angleInDegrees );
}

#pragma mark -
#pragma mark Creation Methods
void VirtualController::addButton( cocos2d::CCSprite * p_Button ) {
    m_PadButtons -> addObject( p_Button );
    m_ButtonFlags.push_back( false );
    this -> addChild( p_Button );
}

void VirtualController::removeButton( unsigned int p_ButtonID ) {
    this -> removeChild( ( CCSprite * ) m_PadButtons -> objectAtIndex( p_ButtonID ), true );
    m_ButtonFlags.erase( m_ButtonFlags.begin() + p_ButtonID );
    m_PadButtons -> removeObjectAtIndex( p_ButtonID );
}

#pragma mark -
#pragma mark Helper Methods
float VirtualController::calculateHypotenuse( float p_ValA, float p_ValB ) {
    return sqrtf( ( p_ValA * p_ValA ) + ( p_ValB * p_ValB ) );
}

float VirtualController::calculateDistanceBetweenPoints( cocos2d::CCPoint p_PointA, cocos2d::CCPoint p_PointB ) {
    float deltaX = ( p_PointB.x - p_PointA.x ) * ( p_PointB.x - p_PointA.x );
    float deltaY = ( p_PointB.y - p_PointA.y ) * ( p_PointB.y - p_PointA.y );
    
    return sqrtf( deltaX + deltaY );
}

float VirtualController::calculateDegreesOfTwoPoints( cocos2d::CCPoint p_PointA, cocos2d::CCPoint p_PointB ) {
    float deltaX = p_PointB.x - p_PointA.x;
    float deltaY = p_PointB.y - m_DefaultStickPosition.y;
    
    return atan2f( deltaY, deltaX ) * 180 / 3.14285714;
}

float VirtualController::calculateRadiansOfTwoPoints( cocos2d::CCPoint p_PointA, cocos2d::CCPoint p_PointB ) {
    float deltaX = p_PointB.x - p_PointA.x;
    float deltaY = p_PointB.y - m_DefaultStickPosition.y;
    
    return atan2f( deltaY, deltaX ) + 3.14285714;
}