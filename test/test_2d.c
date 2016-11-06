#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <graphic/graphic.h>
#include <graphic/texture.h>
#include <graphic/shader.h>
#include <graphic/sprite2d.h>
#include <graphic/node3d.h>
#include <base/ref.h>
#include <math/math.h>

int main(int argc, char *argv[])
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_Window* window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
  SDL_GLContext context = SDL_GL_CreateContext(window);
  SDL_Event windowEvent;

  //-------------------------------
  g_texture* tex = texture_new_from_file_char("res/Silent-Morning.png");
  g_texture* tex2 = texture_new_from_file_char("res/paper.jpg");
  g_shader* shader = shader_new_from_file("res/shaders/shader_2d.vert", "res/shaders/shader_2d.frag");
  g_shader* shader2 = shader_new_from_file("res/shaders/shader_3d.vert", "res/shaders/shader_3d.frag");

  g_sprite2d* sprite = sprite2d_new();
  sprite->func->retain(sprite);
  sprite->size = vector3_new(50,50,0);
  sprite->func->set_shader(sprite,shader);
  sprite->func->set_texture(sprite,tex);

  g_sprite2d* sprite2 = sprite2d_new();
  sprite2->size = vector3_new(50,50,0);
  sprite2->func->set_shader(sprite2,shader);
  sprite2->func->set_texture(sprite2,tex);
  sprite->func->add_child(sprite, sprite2);
  sprite2->func->set_position(sprite2, vector3_new(0,0,0.1));

  g_sprite2d* sprite3 = sprite2d_new();
  sprite3->size = vector3_new(50,50,0);
  sprite3->func->set_shader(sprite3,shader);
  sprite3->func->set_texture(sprite3,tex);
  sprite2->func->add_child(sprite2, sprite3);
  sprite3->func->set_position(sprite3, vector3_new(0,0,0.1));

  g_node3d* sprite4 = node3d_new();
  sprite4->size = vector3_new(30, 30, 30);
  sprite4->func->set_shader(sprite4, shader2);
  sprite4->func->set_texture(sprite4,tex2);
  sprite->func->add_child(sprite, sprite4);
  sprite4->func->set_position(sprite4, vector3_new(50, 0, 0));
  sprite4->func->set_model_obj(sprite4, "res/model/monkey.obj");

  matrix4 view = matrix4_create_look_at(
    0.01f, 0.0f, 200.0f,
    0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f
  );
  matrix4 proj = matrix4_create_perspective(DEG_TO_RAD(45.0f), 800.0f / 600.0f, 1.0f, 1000.0f);
  shader->func->use(shader);
  glUniform1i(glGetUniformLocation(shader->func->get_id(shader), "tex"), 0);
  glUniformMatrix4fv(glGetUniformLocation(shader->func->get_id(shader), "view"), 1, GL_FALSE, view.m);
  glUniformMatrix4fv(glGetUniformLocation(shader->func->get_id(shader), "proj"), 1, GL_FALSE, proj.m);
  shader2->func->use(shader2);
  glUniformMatrix4fv(glGetUniformLocation(shader2->func->get_id(shader2), "proj"), 1, GL_FALSE, proj.m);
  glUniformMatrix4fv(glGetUniformLocation(shader2->func->get_id(shader2), "view"), 1, GL_FALSE, view.m);
  glUniform1i(glGetUniformLocation(shader2->func->get_id(shader2), "tex"), 0);
  glEnable(GL_DEPTH_TEST);
  quaternion offset_q = quaternion_identity;
  float time = 0;
  int touch = 0;
  int key = 0;
  while (1)
  {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    if (SDL_PollEvent(&windowEvent))
    {
      if (windowEvent.type == SDL_QUIT) break;
      if (windowEvent.type == SDL_KEYUP &&
          windowEvent.key.keysym.sym == SDLK_ESCAPE) break;
      if (windowEvent.type == SDL_KEYUP){
        touch = 0;
        continue;
      }

      if(windowEvent.type == SDL_KEYDOWN)
      {
        touch = 1;
        key = windowEvent.key.keysym.sym;
      }
    }
    if(touch)
    {
      switch(key)
      {
        case SDLK_LEFT:
          offset_q = quaternion_new_angle_axis(DEG_TO_RAD(-50 * 0.016), 0, 1, 0);
          sprite->func->set_quat(sprite, quaternion_mul(offset_q, sprite->quat));
          break;
        case SDLK_RIGHT:
          offset_q = quaternion_new_angle_axis(DEG_TO_RAD(50 * 0.016), 0, 1, 0);
          sprite->func->set_quat(sprite, quaternion_mul(offset_q, sprite->quat));
          break;
        case SDLK_DOWN:
          offset_q = quaternion_new_angle_axis(DEG_TO_RAD(50 * 0.016), 1, 0, 0);
          sprite->func->set_quat(sprite, quaternion_mul(offset_q, sprite->quat));
          break;
        case SDLK_UP:
          offset_q = quaternion_new_angle_axis(DEG_TO_RAD(-50 * 0.016), 1, 0, 0);
          sprite->func->set_quat(sprite, quaternion_mul(offset_q, sprite->quat));
          break;
        case SDLK_z:
          offset_q = quaternion_new_angle_axis(DEG_TO_RAD(50 * 0.016), 0, 0, 1);
          sprite->func->set_quat(sprite, quaternion_mul(offset_q, sprite->quat));
          break;
        case SDLK_x:
          offset_q = quaternion_new_angle_axis(DEG_TO_RAD(-50 * 0.016), 0, 0, 1);
          sprite->func->set_quat(sprite, quaternion_mul(offset_q, sprite->quat));
          break;
        default:
            break;
      }
    }
    sprite->func->visit(sprite, matrix4_identity, 0);

    ref_update_auto_release_pool();
    SDL_GL_SwapWindow(window);
  }
  sprite->func->release(sprite);

  texture_free_cache();
  ref_update_auto_release_pool();
  SDL_GL_DeleteContext(context);
  SDL_Quit();
  return 0;
}
