//
//  SSViewController.m
//  SSEdit
//
//  Created by stephen kaufer on 9/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "SSViewController.h"

#include "m_processor.h"


@implementation SSViewController
@synthesize input;
@synthesize tc,tvtext;

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle
-(void)get{
    [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(checkdone:) userInfo:nil repeats:YES];
}

-(void)checkdone:(NSTimer*)t{
    if(tc.on){
        [tc setOn:NO animated:YES];
        wordset code = breakDownWordset((char*)[input.text UTF8String],';');
        for (int i = 0; i<code.wordCount; i++) {
            LOOP
                if(code.words[i][0] == ' ' || code.words[i][0] == '\n')code.words[i]++;
                else BREAK_OUT_OF_LOOP;
            char *t;
            t = malloc(strlen(code.words[i]) + 1);
            strcpy(t,code.words[i]);
            String a;
            if(strcmp(a = processCode(t), "Success") != 0){printf("\nerror: %s  on line: %s\n",a,code.words[i]);}
        }
         [[[UIAlertView alloc] initWithTitle:@"Output" message:tvtext delegate:self cancelButtonTitle:@"ok" otherButtonTitles:nil] show];
        endautoreleasepool
        startautoreleasepool
        initProcessor();
        tvtext = @"";
    }
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self get];
    startautoreleasepool
    initProcessor();
    tvtext=@"";
}

- (void)viewDidUnload
{
    [self setTc:nil];
    [self setInput:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
}

- (void)viewDidDisappear:(BOOL)animated
{
	[super viewDidDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationLandscapeRight);
}
-(IBAction)add:(UIButton*)sender{
    input.text = [input.text stringByAppendingString:sender.titleLabel.text];
}

- (IBAction)submit:(id)sender {
}

@end
