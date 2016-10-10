
#import "RootViewController.h"
#include "models/PTModelGeneralSettings.h"
#include "cocos2d.h"

@implementation RootViewController

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    PTModelGeneralSettings *generalSettings = PTModelGeneralSettings::shared();
    if(generalSettings->orientation() == PTPScreenOrientationLandscape){    
        return UIInterfaceOrientationIsLandscape( interfaceOrientation );
    }
    else if(generalSettings->orientation() == PTPScreenOrientationPortrait){
        return UIInterfaceOrientationIsPortrait( interfaceOrientation );
    }

    return NO;
}

- (NSUInteger) supportedInterfaceOrientations{
    PTModelGeneralSettings *generalSettings = PTModelGeneralSettings::shared();
    if(generalSettings->orientation() == PTPScreenOrientationLandscape){    
        return UIInterfaceOrientationMaskLandscape;

   }
   else if(generalSettings->orientation() == PTPScreenOrientationPortrait){
       return UIInterfaceOrientationMaskPortrait;    
   }

   return NO;
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}


- (void)viewDidLoad
{
    [super viewDidLoad];
    if ([self respondsToSelector:@selector(setNeedsStatusBarAppearanceUpdate)])
    {
        [self prefersStatusBarHidden];
        [self performSelector:@selector(setNeedsStatusBarAppearanceUpdate)];
    }
    else
    {
        // iOS 6
        [[UIApplication sharedApplication] setStatusBarHidden:YES withAnimation:UIStatusBarAnimationSlide];
    }
}

// Add this method
- (BOOL)prefersStatusBarHidden {
    return YES;
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}


@end
