//
//  PTPWindow.m
//  PTPlayer
//
//  Created by Nik Rudenko on 9/25/14.
//
//

#import "PTPWindow.h"
#include "PTPInputController.h"
#include "models/PTModelGeneralSettings.h"
#include "screens/PTPScreen.h"

@implementation PTPWindow

- (void)keyDown:(NSEvent *)theEvent{
    NSLog(@"key down: %u", [theEvent keyCode]);
    
    if([theEvent isARepeat]){
        return;
    }
    
    int key = [self mapKeys:[theEvent keyCode]];    
    PTPInputController *inputController = PTPInputController::shared();
    
    PTPScreen *screenLayer = PTPScreen::getTopScreen();
    if ( inputController->handleKeyReleaseOnScreen(key, screenLayer ) ) {
        return;
    }
    
    PTModelGeneralSettings *settsModel = PTModelGeneralSettings::shared();
    if ( settsModel->moveUpKey() == key ) {
        inputController->buttonMoveUpPressed();
        return;
    }
    if ( settsModel->moveDownKey() == key ) {
        inputController->buttonMoveDownPressed();
        return;
    }
    if ( settsModel->moveLeftKey() == key ) {
        inputController->buttonMoveLeftPressed();
        return;
    }
    if ( settsModel->moveRightKey() == key ) {
        inputController->buttonMoveRightPressed();
        return;
    }
    if ( settsModel->motorCWKey() == key ) {
        inputController->buttonMotorCWPressed();
        return;
    }
    if ( settsModel->motorCCWKey() == key ) {
        inputController->buttonMotorCCWPressed();
        return;
    }
    if ( settsModel->rotateLeftKey() == key ) {
        inputController->buttonRotateLeftPressed();
        return;
    }
    if ( settsModel->rotateRightKey() == key ) {
        inputController->buttonRotateRightPressed();
        return;
    }
    if ( settsModel->shootKey() == key ) {
        inputController->buttonShootPressed();
        return;
    }
    if ( settsModel->jumpKey() == key ) {
        inputController->buttonJumpPressed();
        return ;
    }
   

}
- (void)keyUp:(NSEvent *)theEvent{
    if([theEvent isARepeat]){
        return;
    }
    
    int key = [self mapKeys:[theEvent keyCode]];
    
    PTPInputController *inputController = PTPInputController::shared();
    
    PTPScreen *screenLayer = PTPScreen::getTopScreen();
    if ( inputController->handleKeyPressOnScreen( key, screenLayer ) ) {
        return;
    }
    PTModelGeneralSettings *settsModel = PTModelGeneralSettings::shared();
    if ( settsModel->moveUpKey() == key ) {
        inputController->buttonMoveUpReleased();
        return;
    }
    if ( settsModel->moveDownKey() == key ) {
        inputController->buttonMoveDownReleased();
        return;
    }
    if ( settsModel->moveLeftKey() == key ) {
        inputController->buttonMoveLeftReleased();
        return;
    }
    if ( settsModel->moveRightKey() == key ) {
        inputController->buttonMoveRightReleased();
        return;
    }
    if ( settsModel->motorCWKey() == key ) {
        inputController->buttonMotorCWReleased();
        return;
    }
    if ( settsModel->motorCCWKey() == key ) {
        inputController->buttonMotorCCWReleased();
        return;
    }
    if ( settsModel->rotateLeftKey() == key ) {
        inputController->buttonRotateLeftReleased();
        return;
    }
    if ( settsModel->rotateRightKey() == key ) {
        inputController->buttonRotateRightReleased();
        return;
    }
    if ( settsModel->shootKey() == key ) {
        inputController->buttonShootReleased();
        return;
    }
    if ( settsModel->jumpKey() == key ) {
        inputController->buttonJumpReleased();
        return;
    }
}

- (int)mapKeys:(unsigned short)key{
    std::map<unsigned short, int> m = {
        {50, 96},
        {18, 49},
        {19, 50},
        {20, 51},
        {21, 52},
        {23, 53},
        {22, 54},
        {26, 55},
        {28, 56},
        {25, 57},
        {29, 48},
        {27, 45},
        {24, 61},
        {51, 16777219},
        {12, 81},
        {13, 87},
        {14, 69},
        {15, 82},
        {17, 84},
        {16, 89},
        {32, 85},
        {34, 73},
        {31, 79},
        {35, 80},
        {33, 91},
        {30, 93},
        {42, 92},
        {0, 65},
        {1, 83},
        {2, 68},
        {3, 70},
        {5, 71},
        {4, 72},
        {38, 74},
        {40, 75},
        {37, 76},
        {41, 59},
        {39, 39},
        {36, 16777220},
        {6, 90},
        {7, 88},
        {8, 67},
        {9, 86},
        {11, 66},
        {45, 78},
        {46, 77},
        {43, 44},
        {47, 46},
        {44, 47},
        {49, 32},
        {123, 16777234},
        {126, 16777235},
        {125, 16777237},
        {124, 16777236},
        {82, 48},
        {65, 46},
        {76, 16777221},
        {83, 49},
        {84, 50},
        {85, 51},
        {86, 52},
        {87, 53},
        {88, 54},
        {89, 55},
        {91, 56},
        {92, 57},
        {53, 16777216}
    };
    
    return m[ key ];
    
}

- (void) setEAGLView:(EAGLView *)glView {
    _glView = glView;
}

- (void) resizeView:(NSRect) rect {
    NSRect rectClient = [self contentRectForFrameRect:rect];
    NSRect convertedRect = [self convertRectFromScreen:rectClient];
    convertedRect.origin.y = rectClient.size.height - rect.size.height;
    convertedRect.origin.x = 0;
    [_glView initWithFrame:convertedRect];
    [_glView setFrameSize:rect.size];
    [_glView setFrameZoomFactor:1.0];
}

@end
