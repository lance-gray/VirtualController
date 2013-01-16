//
//  TestObject.cpp
//  SHMUP
//
//  Created by Alexis Tio on 1/15/13.
//
//

#include "TestObject.h"
#include "AppMacros.h"

using namespace cocos2d;

bool TestObject::init() {
    m_Sprite = CCSprite::create( "powerbutton.png" );
    this -> addChild( m_Sprite );
    
    return true;
}

void TestObject::onStickMoved( float p_Distance, float p_Angle, StickDirection p_Direction ) {
    m_Sprite -> setRotation( -p_Angle );
    
    float newPosX = m_Sprite -> getPosition().x;
    float newPosY = m_Sprite -> getPosition().y;
    
    if ( p_Direction == StickDirectionRight || p_Direction == StickDirectionDownRight || p_Direction == StickDirectionUpRight )
        newPosX += 8;
    
    if ( p_Direction == StickDirectionLeft || p_Direction == StickDirectionDownLeft || p_Direction == StickDirectionUpLeft )
        newPosX -= 8;
    
    if ( p_Direction == StickDirectionUp || p_Direction == StickDirectionUpLeft || p_Direction == StickDirectionUpRight )
        newPosY += 8;
    
    if ( p_Direction == StickDirectionDown || p_Direction == StickDirectionDownLeft || p_Direction == StickDirectionDownRight )
        newPosY -= 8;
    
    m_Sprite -> setPosition( CCPointMake( newPosX, newPosY ) );
}

void TestObject::onStickReset() {
    
}

void TestObject::onButtonPress( int p_ID ) {
    if ( p_ID == 0 ) {
        CCLabelTTF * label = CCLabelTTF::create( "A!", "Arial", TITLE_FONT_SIZE );
        label -> setPosition( m_Sprite -> getPosition() );
        label -> setTag( 10 );
        this -> addChild( label );
        
        CCMoveBy * moveAction = CCMoveBy::create( 0.2f, CCPointMake( 0, 64 ) );
        CCFadeOut * fadeAction = CCFadeOut::create( moveAction -> getDuration() );
        CCSpawn * spawnAction = CCSpawn::createWithTwoActions( moveAction, fadeAction );
        CCCallFunc * callFunc = CCCallFunc::create( this, callfunc_selector( TestObject::doFadeEnd ) );
        CCSequence * sequenceAction = CCSequence::createWithTwoActions( spawnAction, callFunc );
        
        label -> runAction( sequenceAction );
    } else if ( p_ID == 1 ) {
        CCLabelTTF * label = CCLabelTTF::create( "B!", "Arial", TITLE_FONT_SIZE );
        label -> setPosition( m_Sprite -> getPosition() );
        label -> setTag( 10 );
        this -> addChild( label );
        
        CCMoveBy * moveAction = CCMoveBy::create( 0.2f, CCPointMake( 0, 64 ) );
        CCFadeOut * fadeAction = CCFadeOut::create( moveAction -> getDuration() );
        CCSpawn * spawnAction = CCSpawn::createWithTwoActions( moveAction, fadeAction );
        CCCallFunc * callFunc = CCCallFunc::create( this, callfunc_selector( TestObject::doFadeEnd ) );
        CCSequence * sequenceAction = CCSequence::createWithTwoActions( spawnAction, callFunc );
        
        label -> runAction( sequenceAction );
    }
    
    
}

void TestObject::onButtonUnpress( int p_ID ) {
    
}

void TestObject::doFadeEnd(cocos2d::CCObject *p_Sender) {
    CCLabelTTF * labelTrigger = ( CCLabelTTF * ) this -> getChildByTag( 10 );
    labelTrigger -> removeFromParentAndCleanup( true );
}