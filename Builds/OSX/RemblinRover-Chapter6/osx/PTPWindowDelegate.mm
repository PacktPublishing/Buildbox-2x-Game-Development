#import "PTPWindowDelegate.h"
#import "EAGLView.h"
#import "PTPWindow.h"
#import "PTPSettingsController.h"

@implementation PTPWindowController

- (void)windowDidEndLiveResize:(NSNotification *)notification {
    PTPWindow *window = notification.object;
    NSRect rect = [window frame];
    [window resizeView:rect];
    
    cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1136, 640, cocos2d::CCEGLView::sharedOpenGLView()->resolutionPolicy());
}

- (void)windowWillClose:(NSNotification *)notification {
    PTPSettingsController::shared()->save();
}
@end
