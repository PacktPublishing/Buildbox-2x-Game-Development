
#import "cocos2d.h"
#import "EAGLView.h"
#import "PTPWindow.h"

@class PTPWindowController;

@interface AppController : NSObject <NSApplicationDelegate> {
    PTPWindow *window;
    PTPWindowController *winController;
    EAGLView *glView;
    
    NSRect _originalWinRect;
    cocos2d::CCSize _originalFrameSize;
}
@property (nonatomic, assign) IBOutlet NSWindow* window;
@property (nonatomic, assign) IBOutlet EAGLView* glView;

-(void)setFullscreen:(BOOL)value;
-(NSRect)screenResolution;
-(void)loadingDidComplete;
-(void)adjustWindowForFullscreen:(BOOL)fullscreen;
@end

