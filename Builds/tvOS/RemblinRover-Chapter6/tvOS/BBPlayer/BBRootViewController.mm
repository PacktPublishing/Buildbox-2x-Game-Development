//
//  GameViewController.m
//  BBPlayer
//
//  Created by Nik Rudenko on 10/8/15.
//  Copyright (c) 2015 Buildbox. All rights reserved.
//

#import "BBRootViewController.h"
#import "models/PTModelController.h"
#import "PTPAppDelegate.h"
#import "PTPInputController.h"
#import <GameController/GameController.h>
@interface BBRootViewController () {

}
@property (strong, nonatomic) EAGLContext *context;
@end

// cocos2d application instance
static PTPAppDelegate s_sharedApplication;


@implementation BBRootViewController

- (void)viewDidLoad{
    [super viewDidLoad];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(controllerDidConnect:) name:GCControllerDidConnectNotification object:nil];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    
    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    self.preferredFramesPerSecond = 60;

    [self setupGL];
    
    PTModelController *mc = PTModelController::shared();
    mc->clean();
    mc->loadDataForClass( CCString::create("data/PTModelGeneralSettings.0.attributes.xml"), PTModelControllerDataTypeAttributes );
    mc->loadDataForClass( CCString::create("data/PTModelFont.0.attributes.xml"), PTModelControllerDataTypeAttributes );
    mc->loadDataForClass( CCString::create("data/PTModelScreen.0.attributes.xml"), PTModelControllerDataTypeAttributes );
    mc->loadDataForClass( CCString::create("data/PTModelObjectLabel.0.attributes.xml"), PTModelControllerDataTypeAttributes );
    mc->loadDataForClass( CCString::create("data/PTModelScreen.0.connections.xml"), PTModelControllerDataTypeConnections );
    
    cocos2d::CCApplication::sharedApplication()->run();
    //clean up main model controller before starting loading Objects form XML files
    mc->clean();

    
    printf("GL_VENDOR:     %s\n", glGetString(GL_VENDOR));
    printf("GL_RENDERER:   %s\n", glGetString(GL_RENDERER));
    printf("GL_VERSION:    %s\n", glGetString(GL_VERSION));
}

//- (void)viewDidAppear:(BOOL)animated {
//    [super viewDidAppear:animated];
//    [self becomeFirstResponder];
//}
//
//- (BOOL)canBecomeFirstResponder {
//    return YES;
//}

- (void)controllerDidConnect:(NSNotification *)notification {
    GCController *controller = notification.object;
    NSLog(@"controller: %@", controller);
    
    GCMicroGamepad *profile =  controller.microGamepad;
    profile.dpad.valueChangedHandler = ^ (GCControllerDirectionPad *gamepad, float x, float y){
        BOOL isPortraitController = YES;
        if (controller.motion) {
//            NSLog(@"gravity: %f %f %f", controller.motion.gravity.x, controller.motion.gravity.y, controller.motion.gravity.z);
//            NSLog(@"userAcc: %f %f %f", controller.motion.userAcceleration.x, controller.motion.userAcceleration.y, controller.motion.userAcceleration.z);
//                        NSLog(@"rotationRate: %f %f %f", controller.motion.rotationRate.x, controller.motion.rotationRate.y, controller.motion.rotationRate.z);
            
            if(controller.motion.gravity.x < -0.5 && controller.motion.gravity.y > -0.5){
                isPortraitController = NO;
            }
            else{
                isPortraitController = YES;
            }
        }
        
        static float previousValue = 0;
//        if (isPortraitController) {
////            PORTRAIT 
//            if (x == 0) {
//                PTPInputController::shared()->applyMoveVectorOnCharacters( ccp(0,0) );
//            }
//            else{
//                PTPInputController::shared()->applyMoveVectorOnCharacters( ccp(x*0.3,0) );
//            }
//            
//            if( y == 0 && previousValue != 0){
//                if (previousValue > 0.3) {
//                    PTPInputController::shared()->keyPressed( PTPInputControllerKeySelectUp );
//                }
//                if (previousValue < -0.3) {
//                    PTPInputController::shared()->keyPressed( PTPInputControllerKeySelectDown );
//                }
//            }
//            previousValue = y;
//        }else{
            if (y == 0) {
                PTPInputController::shared()->applyMoveVectorOnCharacters( ccp(0,0) );
            }
            else{
                PTPInputController::shared()->applyMoveVectorOnCharacters( ccp(-y*0.3,0) );
            }
            
            if( x == 0 && previousValue != 0){
                if (previousValue > 0.3) {
                    PTPInputController::shared()->keyPressed( PTPInputControllerKeySelectUp );
                }
                if (previousValue < -0.3) {
                    PTPInputController::shared()->keyPressed( PTPInputControllerKeySelectDown );
                }
            }
            previousValue = x;
//        }
    };
}

- (void)remoteControlReceivedWithEvent:(nullable UIEvent *)event{
    NSLog(@"remoteControlReceivedWithEvent: %@", event);
}


- (void)pressesBegan:(NSSet<UIPress *> *)presses withEvent:(nullable UIPressesEvent *)event{
//    NSLog(@"presses begun: %@", presses);
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    
    UIPress *press  =  [presses anyObject];
    if ([press type] == UIPressTypeMenu) {
        pDirector->getKeypadDispatcher()->dispatchKeypadMSG(kTypeBackClicked);
    }

    if ([press type] == UIPressTypePlayPause) {
        pDirector->getKeypadDispatcher()->dispatchKeypadMSG( 23, true);
        PTPInputController::shared()->keyPressed(PTPInputControllerKeySelectEnter);
    }
    if([press type] == UIPressTypeSelect){
        pDirector->getKeypadDispatcher()->dispatchKeypadMSG( 40, true);
        PTPInputController::shared()->keyPressed(PTPInputControllerKeySelectEnter);
    }
}


- (void)pressesChanged:(NSSet<UIPress *> *)presses withEvent:(UIPressesEvent *)event{
    NSLog(@"presses changed: %@", presses);
}
    


- (void)pressesEnded:(NSSet<UIPress *> *)presses withEvent:(UIPressesEvent *)event{
   
    CCDirector* pDirector = CCDirector::sharedDirector();
    UIPress *press  =  [presses anyObject];
    if ([press type] == UIPressTypePlayPause) {
        pDirector->getKeypadDispatcher()->dispatchKeypadMSG( 23, false);
        PTPInputController::shared()->keyReleased(PTPInputControllerKeySelectEnter);
    }
    if([press type] == UIPressTypeSelect){
        pDirector->getKeypadDispatcher()->dispatchKeypadMSG( 40, false); //
        PTPInputController::shared()->keyReleased(PTPInputControllerKeySelectEnter);

    }
}


- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    
    
//    glEnable(GL_DEPTH_TEST);

}

- (void)dealloc
{
//    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(0.65f, 0.65f, 0.65f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    cocos2d::CCDirector::sharedDirector()->mainLoop();
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

@end
