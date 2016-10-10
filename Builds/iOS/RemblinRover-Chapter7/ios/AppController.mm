
#import <UIKit/UIKit.h>
#import "AppController.h"
#import "cocos2d.h"
#import "EAGLView.h"
#import "PTPAppDelegate.h"

#import "RootViewController.h"

#import "GameKit/GKLocalPlayer.h"
#import "GameKit/GKScore.h"
#import "GameKit/GKAchievement.h"

#import "models/PTModelController.h"


@implementation AppController
@synthesize viewController;

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static PTPAppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    

    PTModelController *mc = PTModelController::shared();
    mc->clean();
    mc->loadFile( "data/PTModelGeneralSettings.0.attributes.xml", PTModelController::Attributes );
    mc->loadFile( "data/PTModelFont.0.attributes.xml", PTModelController::Attributes );     
    mc->loadFile( "data/PTModelScreen.0.attributes.xml", PTModelController::Attributes );
    mc->loadFile( "data/PTModelObjectLabel.0.attributes.xml", PTModelController::Attributes );
    mc->loadFile( "data/PTModelObjectLoadingBar.0.attributes.xml", PTModelController::Attributes );
    mc->loadFile( "data/PTModelScreen.0.connections.xml", PTModelController::Connections );

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
										pixelFormat: kEAGLColorFormatRGBA8
										depthFormat: GL_DEPTH_COMPONENT16
								 preserveBackbuffer: YES
                                         sharegroup: nil
                                      multiSampling: NO
                                    numberOfSamples: 0];
    
    __glView.multipleTouchEnabled = YES;
    
    // Use RootViewController manage EAGLView 
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = __glView;
 
    
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0) {
        [window addSubview: viewController.view];
    }
    else  {
        [window setRootViewController:viewController];
    }
    
    [window makeKeyAndVisible];
    
    [[UIApplication sharedApplication] setStatusBarHidden: YES];
    
//    [EventHandling observeAllEventsWithObserver:self withSelector:@selector(eventFired:)];

    printf("GL_VENDOR:     %s\n", glGetString(GL_VENDOR));
    printf("GL_RENDERER:   %s\n", glGetString(GL_RENDERER));
    printf("GL_VERSION:    %s\n", glGetString(GL_VERSION));

    cocos2d::CCApplication::sharedApplication()->run();
    //clean up main model controller before starting loading Objects form XML files
    mc->clean();
    return YES;
}



-(NSUInteger)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(UIWindow *)window
{
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
        return UIInterfaceOrientationMaskAll;
    else  /* iphone */
        return UIInterfaceOrientationMaskAllButUpsideDown;
}

- (void)applicationWillResignActive:(UIApplication *)application {
	cocos2d::CCDirector::sharedDirector()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
	cocos2d::CCDirector::sharedDirector()->resume();
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {

}

- (void)loadingDidComplete{

}

-(void)showCustomFullscreenAd{

}

#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}


- (void)dealloc {
    [super dealloc];
}


@end

