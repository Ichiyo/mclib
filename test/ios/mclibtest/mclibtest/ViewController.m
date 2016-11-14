//
//  ViewController.m
//  mclibtest
//
//  Created by Manh Tran on 11/10/16.
//  Copyright © 2016 Manh Tran. All rights reserved.
//

#import "ViewController.h"
#include <graphic/graphic.h>
#include <graphic/m_texture.h>
#include <graphic/m_shader.h>
#include <graphic/m_sprite2d.h>
#include <graphic/m_node3d.h>
#include <utils/file_utils.h>
#include <base/ref.h>
#include <math/math.h>

@interface ViewController ()
{
    EAGLContext* context;
    GLKView* view;
    int first_time;
    m_node* root;
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
    root = 0;
    
    [self addChildViewController:viewController];
    [self.view addSubview:view];
}

-(void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    if(root)
    {
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClearStencil(0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        
        quaternion offset_q = quaternion_new_angle_axis(DEG_TO_RAD(-50 * 0.016), 0, 1, 0);
        root->func->set_quat(root, quaternion_mul(offset_q, root->quat));
        
        root->func->visit(root, matrix4_identity, 0);
    }
}

-(void)glkViewControllerUpdate:(GLKViewController *)controller
{
    if(first_time)
    {
        first_time = 0;
        
        m_string* _3d_vert = read_string_from_file("res/shaders/shader_skin_3d.vert");
        m_string* _3d_frag = read_string_from_file("res/shaders/shader_skin_3d.frag");
        
        _3d_vert->func->replace_str(_3d_vert, new_string_from_char("$number_join_ids"), new_string_from_char("5"));
        _3d_vert->func->replace_str(_3d_vert, new_string_from_char("$number_joins"), new_string_from_char("30"));
        _3d_vert->func->replace_str(_3d_vert, new_string_from_char("$use_model_index"), new_string_from_char("0"));
        m_shader* shadertest = m_shader_new_from_source(_3d_vert->content, _3d_frag->content);
        
        m_texture* tex = m_texture_new_from_file_char("res/Silent-Morning.png");
        m_texture* tex2 = m_texture_new_from_file_char("res/floor/TexturesCom_FloorsCheckerboard0017_1_seamless_S.jpg");
        m_shader* shader = m_shader_new_from_file("res/shaders/shader_2d.vert", "res/shaders/shader_2d.frag");
        m_shader* shader2 = m_shader_new_from_file("res/shaders/shader_3d.vert", "res/shaders/shader_3d.frag");
        
        m_sprite2d* sprite = m_sprite2d_new();
        sprite->func->set_texture(sprite, tex);
        sprite->func->set_shader(sprite, shader);
        sprite->func->set_size(sprite, vector3_new(50, 50, 0));
        sprite->func->retain(sprite);
        
        
        {
            m_node3d* sprite4 = m_node3d_new();
            sprite4->size = vector3_new(30, 30, 30);
            sprite4->func->set_shader(sprite4, shader2);
            sprite4->func->set_texture(sprite4,tex2);
            sprite->func->add_child(sprite, sprite4);
            sprite4->func->set_model_obj(sprite4, "res/model/cube.obj");
            sprite4->func->set_position(sprite4, vector3_new(50, 0, 0));
            quaternion offset_q = quaternion_new_angle_axis(DEG_TO_RAD(45), 0, 0, 1);
            sprite4->func->set_quat(sprite4, quaternion_mul(sprite4->quat, offset_q));
        }
        
        m_matrix4 mview = matrix4_create_look_at(
                                                0.01f, 0.0f, 200.0f,
                                                0.0f, 0.0f, 0.0f,
                                                0.0f, 1.0f, 0.0f
                                                );
        m_matrix4 proj = matrix4_create_perspective(DEG_TO_RAD(45.0f), 800.0f / 600.0f, 1.0f, 1000.0f);
        shader->func->use(shader);
        glUniform1i(glGetUniformLocation(shader->func->get_id(shader), "tex"), 0);
        glUniformMatrix4fv(glGetUniformLocation(shader->func->get_id(shader), "view"), 1, GL_FALSE, mview.m);
        glUniformMatrix4fv(glGetUniformLocation(shader->func->get_id(shader), "proj"), 1, GL_FALSE, proj.m);
        shader2->func->use(shader2);
        glUniformMatrix4fv(glGetUniformLocation(shader2->func->get_id(shader2), "proj"), 1, GL_FALSE, proj.m);
        glUniformMatrix4fv(glGetUniformLocation(shader2->func->get_id(shader2), "view"), 1, GL_FALSE, mview.m);
        int diffuse = 0;
        glUniform1iv(glGetUniformLocation(shader2->func->get_id(shader2), "material.diffuse"),1, &diffuse);
        
        GLint lightDirLoc = glGetUniformLocation(shader2->func->get_id(shader2), "light.direction");
        m_vector3 vector = vector3_new(-1, 0, -1);
        glUniform3fv(lightDirLoc,1, &vector);
        vector = vector3_new(0.5f, 0.5f, 0.5f);
        glUniform3fv(glGetUniformLocation(shader2->func->get_id(shader2), "light.ambient"),  1, &vector);
        vector = vector3_new(1,1,1);
        glUniform3fv(glGetUniformLocation(shader2->func->get_id(shader2), "light.diffuse"),  1, &vector);
        vector = vector3_new(1, 1, 1);
        glUniform3fv(glGetUniformLocation(shader2->func->get_id(shader2), "light.specular"), 1, &vector);
        // Set material properties
        float shinness = 32;
        glUniform1fv(glGetUniformLocation(shader2->func->get_id(shader2), "material.shininess"), 1, &shinness);
        
        glEnable(GL_DEPTH_TEST);
        
        root = sprite;
    }
    
    ref_update_auto_release_pool();
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
