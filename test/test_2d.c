#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <graphic/graphic.h>
#include <graphic/m_texture.h>
#include <graphic/m_shader.h>
#include <graphic/m_sprite2d.h>
#include <graphic/m_node3d.h>
#include <base/ref.h>
#include <math/math.h>
#include <utils/file_utils.h>

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
  m_texture* tex = m_texture_new_from_file_char("res/Silent-Morning.png");
  m_texture* tex2 = m_texture_new_from_file_char("res/floor/TexturesCom_FloorsCheckerboard0017_1_seamless_S.jpg");
  m_shader* shader = m_shader_new_from_file("res/shaders/shader_2d.vert", "res/shaders/shader_2d.frag");

  m_string* _3d_vert = read_string_from_file("res/shaders/shader_skin_3d.vert");
  m_string* _3d_frag = read_string_from_file("res/shaders/shader_skin_3d.frag");

  _3d_vert->func->replace_str(_3d_vert, new_string_from_char("$number_join_ids"), new_string_from_char("0"));
  _3d_vert->func->replace_str(_3d_vert, new_string_from_char("$number_joins"), new_string_from_char("0"));
  _3d_vert->func->replace_str(_3d_vert, new_string_from_char("$use_model_index"), new_string_from_char("1"));
  m_shader* shader2 = m_shader_new_from_source(_3d_vert->content, _3d_frag->content);
  QUICK_RELEASE(_3d_vert);
  QUICK_RELEASE(_3d_frag);
  // m_shader* shader2 = m_shader_new_from_file("res/shaders/shader_3d.vert", "res/shaders/shader_3d.frag");

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

  m_matrix4 view = matrix4_create_look_at(
    0.01f, 0.0f, 200.0f,
    0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f
  );
  m_matrix4 proj = matrix4_create_perspective(DEG_TO_RAD(45.0f), 800.0f / 600.0f, 1.0f, 1000.0f);

  shader->func->use(shader);
  glUniform1i(glGetUniformLocation(shader->func->get_id(shader), "tex"), 0);
  glUniformMatrix4fv(glGetUniformLocation(shader->func->get_id(shader), "view"), 1, GL_FALSE, view.m);
  glUniformMatrix4fv(glGetUniformLocation(shader->func->get_id(shader), "proj"), 1, GL_FALSE, proj.m);
  shader2->func->use(shader2);
  glUniformMatrix4fv(glGetUniformLocation(shader2->func->get_id(shader2), "proj"), 1, GL_FALSE, proj.m);
  glUniformMatrix4fv(glGetUniformLocation(shader2->func->get_id(shader2), "view"), 1, GL_FALSE, view.m);
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
  quaternion offset_q = quaternion_identity;
  float time = 0;
  int touch = 0;
  int key = 0;
  while (1)
  {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
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
        case SDLK_a:
          offset_q = quaternion_new_angle_axis(DEG_TO_RAD(50 * 0.016), 0, 0, 1);
          sprite->func->set_quat(sprite, quaternion_mul(sprite->quat, offset_q));
          break;
        case SDLK_s:
          offset_q = quaternion_new_angle_axis(DEG_TO_RAD(-50 * 0.016), 0, 0, 1);
          sprite->func->set_quat(sprite, quaternion_mul(sprite->quat, offset_q));
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

  m_texture_free_cache();
  ref_update_auto_release_pool();
  SDL_GL_DeleteContext(context);
  SDL_Quit();
  return 0;
}
