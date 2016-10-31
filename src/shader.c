#include <graphic/shader.h>
#include <stdio.h>
#include <stdlib.h>
#include <mstr/string.h>
#include <utils/file_utils.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _opengl_shader
{
  REF_MACRO
  void(*use)(void*);
  GLuint id;
};
typedef struct _opengl_shader opengl_shader;

static void free_shader(opengl_shader* shader)
{
  if(shader->id)
  {
    glDeleteProgram(shader->id);
  }
  free(shader);
}

static void shader_use(opengl_shader* shader)
{
  glUseProgram(shader->id);
}

static void init_shader(opengl_shader* ret, const char* vertex_source, const char* fragment_source)
{
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertex_source, NULL);
  glCompileShader(vertexShader);
  // Check for compile time errors
  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
  }
  // Fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragment_source, NULL);
  glCompileShader(fragmentShader);
  // Check for compile time errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
  }
  // Link shaders
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // Check for linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  ret->id = shaderProgram;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
g_shader* shader_new(const char* vertex_source, const char* fragment_source)
{
  REF_NEW_AUTO_RELEASE(opengl_shader, ret)
  ret->free = free_shader;
  ret->use = shader_use;
  init_shader(ret, vertex_source, fragment_source);
  return ret;
}

g_shader* shader_new_from_file(const char* vertex_file, const char* fragment_file)
{
  REF_NEW_AUTO_RELEASE(opengl_shader, ret)
  ret->free = free_shader;
  ret->use = shader_use;
  m_string* vertex = read_string_from_file(vertex_file);
  m_string* fragment = read_string_from_file(fragment_file);
  init_shader(ret, vertex->content, fragment->content);
  vertex->release(vertex);
  fragment->release(fragment);
  return ret;
}

#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
