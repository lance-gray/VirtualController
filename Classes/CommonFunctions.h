//
//  CommonFunctions.h
//  VirtualController
//
//  Created by Alexis Tio on 1/16/13.
//
//

#ifndef VirtualController_CommonFunctions_h
#define VirtualController_CommonFunctions_h

#define DEFAULT_POSITION CCPointZero
#define DEFAULT_COLOR() ccc4( 0, 0, 0, 0 )
#define DEFAULT_SIZE() CCSizeMake( 500, 500 )

typedef enum {
    StickDirectionNone,         // Stick is not moving/dragged
    StickDirectionUp,           // Stick is dragged straight up
    StickDirectionUpRight,      // Stick is dragged diagonally to the upper-right
    StickDirectionRight,        // Stick is dragged straight right
    StickDirectionDownRight,    // Stick is dragged diagonnally to the lower-right
    StickDirectionDown,         // Stick is dragged straght down
    StickDirectionDownLeft,     // Stick is dragged diagonally to the lower-left
    StickDirectionLeft,         // Stick is dragged straight left
    StickDirectionUpLeft        // Stick is dragged diagonally to the upper-left
} StickDirection;

#endif
