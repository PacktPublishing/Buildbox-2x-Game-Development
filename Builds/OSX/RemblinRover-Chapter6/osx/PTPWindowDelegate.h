#import <Cocoa/Cocoa.h>
#import "cocos2d.h"

@interface PTPWindowController : NSObject <NSWindowDelegate> {
}

- (void)windowDidEndLiveResize:(NSNotification *)notification;
- (void)windowWillClose:(NSNotification *)notification;

@end
