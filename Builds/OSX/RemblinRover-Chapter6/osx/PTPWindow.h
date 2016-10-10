//
//  PTPWindow.h
//  PTPlayer
//
//  Created by Nik Rudenko on 9/25/14.
//
//

#import <Cocoa/Cocoa.h>
#import "EAGLView.h"

@interface PTPWindow : NSWindow{
    EAGLView *_glView;
}
- (void)keyDown:(NSEvent *)theEvent;
- (void)keyUp:(NSEvent *)theEvent;
- (int)mapKeys:(unsigned short)key;
- (void)setEAGLView:(EAGLView *)glView;
- (void)resizeView:(NSRect) rect;
@end
