VirtualController
=================

A Virtual Controller (on-screen game pad) using COCOS2D-X

How to Use
==========
1. Include VirtualController.h/VirtualController.cpp, ControlledObject.h, and VirtualControllerComons.h in your project.
2. Subclass ControlledObject and implement the following methods, depending on which one you want the object to respond to:
      void onStickMoved( float pDistance, float pAngle, StickDirection pDir )
        - Invoked when the stick is moved/
        - pDistance is the number of pixels the stick moved from its origin.
        - pAngle is the angle of the stick from its origin.
        - pDir is the direction of the stick.
      
      void onStickReset( )
        - Invoked when the stick resets back into position (when user releases tap)
      
      void onButtonPressed( int pID )
        - Invoked when a button is pressed.
        - pID is the ID of the button pressed.
      
      void onButtonMoved( int )
        - Invoked when a button is moved.
        - pID is the ID of the button moved.
        - Currently not functional.
      
      void onButtonHeld( int )
        - Invoked every frame if button is pressed.
        - pID is the ID of the button held.
      
      void onButtonUnpressed( int )
        - Invoked when a button is unpressed.
        - pID is the ID of the button unpressed.
3. Create a VirtualController object and give it a ControlledObject target. You might need to type-cast it depending on how you will use it.
4. VirtualController is a CCLayer subclass so it must be added to the layer first.
5. Create CCSprite objects to serve as buttons and add it to the VirtualController object you just created using the addButton( ) function. You can create as many buttons as desired. All of them are stored in a CCArray.
