#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "VirtualController.h"
#include "TestObject.h"

USING_NS_CC;


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !CCLayer::init() ) return false;
    
    CCSize winSize = CCDirector::sharedDirector() -> getVisibleSize();
    
    TestObject * testTarget = TestObject::create();
    testTarget -> setPosition( CCPointMake( winSize.width / 2, winSize.height * 0.70f ) );
    this -> addChild( testTarget );
    
    VirtualController * dpad = VirtualController::create( ( ControlledObject * ) testTarget );
    this -> addChild( dpad );
    
    CCSprite * buttonA = CCSprite::create( "powerbutton.png" );
    buttonA -> setPosition( CCPointMake( winSize.width * 0.80f, winSize.height * 0.50f ) );
    buttonA -> setScale( 2.0f );
    dpad -> addButton( buttonA );
    
    CCSprite * buttonB = CCSprite::create( "powerbutton.png" );
    buttonB -> setPosition( CCPointMake( winSize.width * 0.60f, winSize.height * 0.30f ) );
    buttonB -> setScale( 2.0f );
    dpad -> addButton( buttonB );
    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
