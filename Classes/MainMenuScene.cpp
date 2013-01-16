//
//  MainMenuScene.cpp
//  VirtualController
//
//  Created by Lance Gray on 1/16/13.
//
//

#include "MainMenuScene.h"
#include "AppMacros.h"
#include "HelloWorldScene.h"

USING_NS_CC;

#pragma mark -
#pragma mark Constructors
MainMenuScene::MainMenuScene() {
    m_LabelTitle = NULL;
    m_ButtonTest = NULL;
    m_ButtonQuit = NULL;
}

MainMenuScene::~MainMenuScene() {
    
}

#pragma mark -
#pragma mark Initialization
CCScene * MainMenuScene::scene() {
    CCScene * scene = CCScene::create();
    MainMenuScene * layer = MainMenuScene::create();
    scene -> addChild( layer );
    
    return scene;
}

bool MainMenuScene::init() {
    if ( !CCLayer::init() ) return false;
    
    this -> drawLayer();
    
    return true;
}

#pragma mark -
#pragma mark Draw Methods
void MainMenuScene::drawLayer() {
    CCSize winSize = CCDirector::sharedDirector() -> getVisibleSize();
    CCPoint winOrigin = CCDirector::sharedDirector() -> getVisibleOrigin();
    
    m_LabelTitle = CCLabelTTF::create( "VirtualController Test", "Arial", TITLE_FONT_SIZE );
    m_LabelTitle -> setPosition( CCPointMake( winOrigin.x + ( winSize.width * 0.50f ), winOrigin.y + ( winSize.height * 0.80f ) ) );
    this -> addChild( m_LabelTitle );
    
    m_ButtonMenu = CCMenu::create();
    m_ButtonMenu -> setPosition( CCPointZero );
    this -> addChild( m_ButtonMenu );
    
    CCLabelTTF * tempLabel = NULL;
    tempLabel = CCLabelTTF::create( "Start", "Arial", TITLE_FONT_SIZE );
    m_ButtonTest = CCMenuItemLabel::create( tempLabel, this, menu_selector( MainMenuScene::doTest ) );
    m_ButtonTest -> setPosition( CCPointMake( winOrigin.x + ( winSize.width * 0.50f ), winOrigin.y + ( winSize.height * 0.30f ) ) );
    m_ButtonMenu -> addChild( m_ButtonTest );
    
    tempLabel = CCLabelTTF::create( "Quit", "Arial", TITLE_FONT_SIZE );
    m_ButtonQuit = CCMenuItemLabel::create( tempLabel, this, menu_selector( MainMenuScene::doQuit ) );
    m_ButtonQuit -> setPosition( CCPointMake( winOrigin.x + ( winSize.width * 0.50f ), winOrigin.y + ( winSize.height * 0.20f ) ) );
    m_ButtonMenu -> addChild( m_ButtonQuit );
}

#pragma mark -
#pragma mark Callback Methods
void MainMenuScene::doTest( cocos2d::CCObject * p_Sender ) {
    CC_UNUSED_PARAM( p_Sender );
    
    CCTransitionCrossFade * fadeTrans = CCTransitionCrossFade::create( 0.20f, HelloWorld::scene() );
    CCDirector::sharedDirector() -> replaceScene( fadeTrans );
}

void MainMenuScene::doQuit( cocos2d::CCObject * p_Sender ) {
    CC_UNUSED_PARAM( p_Sender );
    CCDirector::sharedDirector() -> end();
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    exit( 0 );
#endif
}