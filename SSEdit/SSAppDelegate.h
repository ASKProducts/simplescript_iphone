//
//  SSAppDelegate.h
//  SSEdit
//
//  Created by stephen kaufer on 9/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class SSViewController;
#define SharedVC [(SSAppDelegate*)[[UIApplication sharedApplication] delegate] viewController]
@interface SSAppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (strong, nonatomic) SSViewController *viewController;

@end
