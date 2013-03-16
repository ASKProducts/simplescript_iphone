//
//  SSViewController.h
//  SSEdit
//
//  Created by stephen kaufer on 9/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface SSViewController : UIViewController {
    UITextView *tv;
    UITextField *tb;
    UISwitch *tc;
    UITextView *input;
    NSString *tvtext;
}

@property (strong)NSString *tvtext;

@property (strong, nonatomic) IBOutlet UISwitch *tc;
-(IBAction)add:(UIButton*)sender;

@property (strong, nonatomic) IBOutlet UITextView *input;
@end
