#include <graphic/m_shader.h>
#include <stdio.h>
#include <stdlib.h>
#include <mstr/string.h>
#include <utils/file_utils.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

static GLuint last_shader_used = 0;

void m_shader_free(m_shader* shader)
{
  if(shader->id)
  {
    if(last_shader_used == shader->id) last_shader_used = 0;

    glDeleteProgram(shader->id);
  }
  free(shader);
}

/*EXPEND IMPLEMENTATION -- DO NOT DELETE THIS LINE*/


void m_shader_use(m_shader* shader)
{
  if(last_shader_used != shader->id)
  {
    glUseProgram(shader->id);
    last_shader_used = shader->id;
  }
}

int m_shader_get_id(m_shader*arg_0)
{
	return arg_0->id;
}

static m_shader_func base_m_shader_func =
{
  INHERIT_M_SHADER_FUNC
};

void m_shader_init(m_shader* node)
{
	node->func = &base_m_shader_func;
  //TODO init
}

static void init_shader(m_shader* ret, const char* vertex_source, const char* fragment_source)
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

m_shader* m_shader_new()
{
	REF_NEW_AUTO_RELEASE(m_shader, node)

  m_shader_init(node);
	return node;
}

m_shader* m_shader_new_from_source(const char* vertex_source, const char* fragment_source)
{
  m_shader* ret = m_shader_new();
  init_shader(ret, vertex_source, fragment_source);
  return ret;
}

m_shader* m_shader_new_from_file(const char* vertex_file, const char* fragment_file)
{
  m_shader* ret = m_shader_new();
  m_string* vertex = read_string_from_file(vertex_file);
  m_string* fragment = read_string_from_file(fragment_file);
  init_shader(ret, vertex->content, fragment->content);
  vertex->func->release(vertex);
  fragment->func->release(fragment);
  return ret;
}

#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
