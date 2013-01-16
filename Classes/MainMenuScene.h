//
//  MainMenuScene.h
//  VirtualController
//
//  Created by Lance Gray on 1/16/13.
//
//

#ifndef __VirtualController__MainMenuScene__
#define __VirtualController__MainMenuScene__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::CCLayer {
private:
    cocos2d::CCLabelTTF * m_LabelTitle;
    
    cocos2d::CCMenuItemLabel * m_ButtonTest;
    cocos2d::CCMenuItemLabel * m_ButtonQuit;
    cocos2d::CCMenu * m_ButtonMenu;
    
public:
    // Constructors
    MainMenuScene();
    ~MainMenuScene();
    
    // Initialization
    static cocos2d::CCScene * scene();
    virtual bool init();
    CREATE_FUNC( MainMenuScene );
    
    // Draw Methods
    void drawLayer();
    
    // Callback Methods
    void doTest( cocos2d::CCObject * p_Sender );
    void doQuit( cocos2d::CCObject * p_Sender );
};

#endif /* defined(__VirtualController__MainMenuScene__) */
