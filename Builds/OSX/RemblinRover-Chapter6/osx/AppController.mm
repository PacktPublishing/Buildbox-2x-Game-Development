

#import "AppController.h"
#import "PTPAppDelegate.h"
#import "PTPWindowDelegate.h"

#import "models/PTModelController.h"
#import "models/PTModelGeneralSettings.h"
#import "PTPSettingsController.h"

@implementation AppController
    @synthesize window, glView;

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static PTPAppDelegate s_sharedApplication;

-(void) applicationDidFinishLaunching:(NSNotification *)aNotification{

    PTModelController *mc = PTModelController::shared();
    mc->clean();
    mc->loadDataForClass( CCString::create("data/PTModelGeneralSettings.0.attributes.xml"), PTModelControllerDataTypeAttributes );
    mc->loadDataForClass( CCString::create("data/PTModelFont.0.attributes.xml"), PTModelControllerDataTypeAttributes );     
    mc->loadDataForClass( CCString::create("data/PTModelScreen.0.attributes.xml"), PTModelControllerDataTypeAttributes );
    mc->loadDataForClass( CCString::create("data/PTModelObjectLabel.0.attributes.xml"), PTModelControllerDataTypeAttributes );
    mc->loadDataForClass( CCString::create("data/PTModelScreen.0.connections.xml"), PTModelControllerDataTypeConnections );

    PTPSettingsController::shared()->load();

    window = nil;
    glView = nil;

    BOOL fullscreen = PTPSettingsController::shared()->isFullscreen();
    NSRect rect = [self screenResolution];
    window = [[PTPWindow alloc] initWithContentRect:rect
                                          styleMask:0
                                            backing:NSBackingStoreBuffered
                                              defer:YES];
    glView = [[EAGLView alloc] initWithFrame:rect];
    [window setContentView:glView];

    [window setOpaque:true];
    [window setHidesOnDeactivate:YES];

    winController = [[PTPWindowController alloc] init];
    [window setEAGLView:glView];
    [window setDelegate:winController];

    [self adjustWindowForFullscreen:fullscreen];

    NSString *gameName = [NSString stringWithUTF8String:PTModelGeneralSettings::shared()->applicationName().getCString()];
    [window setTitle:gameName];


    printf("GL_VENDOR:     %s\n", glGetString(GL_VENDOR));
    printf("GL_RENDERER:   %s\n", glGetString(GL_RENDERER));
    printf("GL_VERSION:    %s\n", glGetString(GL_VERSION));

    [glView lockOpenGLContext];
    cocos2d::CCApplication::sharedApplication()->run();
    //clean up main model controller before starting loading Objects form XML files
    mc->clean();
    
    
    if (fullscreen) {
        [window setStyleMask:NSTitledWindowMask];
        [window makeKeyAndOrderFront:self];
        [self setFullscreen:true];
    }
}

-(NSRect)screenResolution{
    NSScreen *screen = [NSScreen mainScreen];
    return [screen frame];
}

-(BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication
{
    return YES;
}

-(void) dealloc{
    cocos2d::CCDirector::sharedDirector()->end();
    [winController release];
    [super dealloc];
}

-(void)setFullscreen:(BOOL)value{
    [self adjustWindowForFullscreen:value];
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1136, 640, CCEGLView::sharedOpenGLView()->resolutionPolicy());

}
-(void)adjustWindowForFullscreen:(BOOL)fullscreen{
    NSRect rect = [self screenResolution];
    int styleMask = fullscreen ? NSBackingStoreBuffered : (NSTitledWindowMask | NSClosableWindowMask | NSResizableWindowMask | NSMiniaturizableWindowMask);

    if (fullscreen)
        [glView initWithFrame:rect];
    else {
        rect.size.width *= 0.6;
        rect.size.height *= 0.6;
    }
    [window setStyleMask:styleMask];
    [window setFrame:rect display:NO];
    [glView setFrame:rect];

    if(fullscreen) {
        [window setLevel:NSMainMenuWindowLevel+1];
        [window setHidesOnDeactivate:YES];
        [window setHasShadow:NO];
        [glView setFrameZoomFactor:1.0];
    }
    else {
        [window setHasShadow:YES];
        [glView setFrameZoomFactor:1.0];
        [window resizeView:rect];
        NSButton *fsButton = [window standardWindowButton:NSWindowZoomButton];
        [fsButton setHidden:YES];
    }
    [window becomeFirstResponder];
    [window makeKeyAndOrderFront:self];
    [window setAcceptsMouseMovedEvents:NO];
}
-(void)loadingDidComplete{

}

@end

