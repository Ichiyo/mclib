//
//  ViewController.m
//  mclibtest
//
//  Created by Manh Tran on 11/10/16.
//  Copyright © 2016 Manh Tran. All rights reserved.
//

#import "ViewController.h"
#include <graphic/graphic.h>
#include <graphic/texture.h>
#include <graphic/shader.h>
#include <graphic/sprite2d.h>
#include <graphic/node3d.h>
#include <utils/file_utils.h>
#include <base/ref.h>
#include <math/math.h>

@interface ViewController ()
{
    EAGLContext* context;
    GLKView* view;
    int first_time;
}

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    view = [[GLKView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    view.drawableDepthFormat = GLKViewDrawableDepthFormat16;
    view.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    view.context = context;
    view.delegate = self;
    
    GLKViewController* viewController = [[GLKViewController alloc] initWithNibName:nil bundle:nil];
    viewController.view = view;
    viewController.delegate = self;
    viewController.preferredFramesPerSecond = 60;
    first_time = 1;
    
    [self addChildViewController:viewController];
    [self.view addSubview:view];
}

-(void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    
}

-(void)glkViewControllerUpdate:(GLKViewController *)controller
{
    if(first_time)
    {
        first_time = 0;
        
        g_shader* shader = shader_new_from_file("res/shaders/shader_2d.vert", "res/shaders/shader_2d.frag");
    }
    
    ref_update_auto_release_pool();
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
