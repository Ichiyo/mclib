#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <graphic/graphic.h>
#include <graphic/texture.h>
#include <graphic/shader.h>
#include <graphic/sprite2d.h>
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
  g_texture* tex = texture_new_from_file_char("res/nature.jpg");
  g_texture* tex2 = texture_new_from_file_char("res/Silent-Morning.png");
  // Create Vertex Array Object
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Create a Vertex Buffer Object and copy the vertex data to it
  GLuint vbo;
  glGenBuffers(1, &vbo);

  GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

    -1.0f, -1.0f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    1.0f, -1.0f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    1.0f,  1.0f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f,  1.0f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
   -1.0f,  1.0f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
   -1.0f, -1.0f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f
  };

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Create an element array
  GLuint ebo;
  glGenBuffers(1, &ebo);

  GLuint elements[] = {
      0, 1, 2,
      2, 3, 0
  };

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

  // Create and compile the vertex shader
  g_shader* shader = shader_new_from_file("res/shader.vert", "res/shader.frag");
  shader->func->retain(shader);
  shader->func->use(shader);

  // Specify the layout of the vertex data
  GLint posAttrib = glGetAttribLocation(shader->func->get_id(shader), "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), 0);

  GLint colAttrib = glGetAttribLocation(shader->func->get_id(shader), "color");
  glEnableVertexAttribArray(colAttrib);
  glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

  GLint texAttrib = glGetAttribLocation(shader->func->get_id(shader), "texcoord");
  glEnableVertexAttribArray(texAttrib);
  glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(7 * sizeof(GLfloat)));

  glUniform1i(glGetUniformLocation(shader->func->get_id(shader), "tex"), 0);
  glUniform1i(glGetUniformLocation(shader->func->get_id(shader), "tex2"), 1);

  GLint uniModel = glGetUniformLocation(shader->func->get_id(shader), "model");

  tex->func->bind(tex, 0);
  tex->func->retain(tex);
  tex2->func->bind(tex2, 1);
  tex2->func->retain(tex2);
  float blend = 0;
  float sig = 1;
  float time = 0;

  glEnable(GL_DEPTH_TEST);
  // glDepthFunc(GL_LESS);
  // glEnable(GL_STENCIL_TEST);
  // glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
  // glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

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
    }
    time += 0.016 / 10;
    // glUniform1f(glGetUniformLocation(shader->func->get_id(shader), "time"), time);

    m_matrix4 view = matrix4_create_look_at(
      2.5f, 2.5f, 2.0f,
      0.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f
    );
    GLint uniView = glGetUniformLocation(shader->func->get_id(shader), "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, view.m);

    m_matrix4 proj = matrix4_create_perspective(DEG_TO_RAD(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);
    GLint uniProj = glGetUniformLocation(shader->func->get_id(shader), "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, proj.m);

    m_matrix4 model = matrix4_identity;
    model = matrix4_rotate(model, DEG_TO_RAD(180) * time, 0, 0, 1);
    // GLfloat s = sin(time * 5.0f) * 0.25f + 0.75f;
    // GLfloat s = 0.5f;
    // model = matrix4_scale_vector3(model, vector3_new(s, s, s));
    GLint uniTrans = glGetUniformLocation(shader->func->get_id(shader), "model");
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, model.m);

    // blend += sig * 0.016;
    // if(blend >= 1 || blend <= 0)
    // {
    //   sig *= -1;
    //   blend = MAX(0, MIN(1, blend));
    // }
    blend = 0.5;
    glUniform1fv(glGetUniformLocation(shader->func->get_id(shader), "blend"), 1, &blend);
    // Clear the screen to black

    //
    // //      Draw bound
    // glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    // // glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    // glStencilMask(0x00);
    // glDisable(GL_DEPTH_TEST);
    // model = matrix4_scale_vector3(
    //     matrix4_translate_vector3(model, vector3_new(0, 0, 0)),
    //     vector3_new(1.9, 1.9, 1.9)
    // );
    // glUniformMatrix4fv(uniModel, 1, GL_FALSE, model.m);
    // glDrawArrays(GL_TRIANGLES, 0, 36);
    // glStencilMask(0xFF);
    // glEnable(GL_DEPTH_TEST);

    //      Draw Grass
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GLint uniColor = glGetUniformLocation(shader->func->get_id(shader), "overrideColor");
    m_vector4 color = vector4_new(1, 1, 1, 1);
    glUniform4fv(uniColor, 1, color.v);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    //      Draw floor
    // glEnable(GL_STENCIL_TEST);
    // glStencilFunc(GL_ALWAYS, 1, 0xFF);
    // glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    // glStencilMask(0xFF);
    // glDepthMask(GL_FALSE);
    // glClear(GL_STENCIL_BUFFER_BIT);
    // color = vector4_new(1, 1, 1, 0.5);
    // glUniform4fv(uniColor, 1, color.v);
    // glDrawArrays(GL_TRIANGLES, 36, 6);

    //    Draw cube reflection
    // glStencilFunc(GL_LEQUAL, 1, 0xFF);
    // glStencilMask(0x00);
    // glDepthMask(GL_TRUE);

    m_matrix4 model2 = matrix4_scale_vector3(
        matrix4_translate_vector3(model, vector3_new(0, 0, -1)),
        vector3_new(1, 1, -1)
    );
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, model2.m);

    color = vector4_new(0.3, 0.3, 0.3, 1.0);
    glUniform4fv(uniColor, 1, color.v);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = matrix4_scale_vector3(model, vector3_new(4, 4, 1));
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, model.m);
    color = vector4_new(0.6, 0.3, 0.1, 0.75);
    glUniform4fv(uniColor, 1, color.v);
    glDrawArrays(GL_TRIANGLES, 36, 6);

    // glDisable(GL_STENCIL_TEST);
    //
    ref_update_auto_release_pool();
    SDL_GL_SwapWindow(window);
  }
  shader->func->release(shader);
  tex->func->release(tex);
  tex2->func->release(tex2);

  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);

  glDeleteVertexArrays(1, &vao);
  texture_free_cache();
  ref_update_auto_release_pool();
  SDL_GL_DeleteContext(context);
  SDL_Quit();
  return 0;
}
