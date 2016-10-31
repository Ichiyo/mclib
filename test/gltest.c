#include <stdio.h>
#include <stdlib.h>
#include <graphic/shader.h>

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GLES3/gl3.h>
#endif

GLdouble width, height;   /* window width and height */
int wd;                   /* GLUT window handle */
GLuint VBO, VAO, EBO;
g_shader* shader;
// Shaders
const GLchar* vertexShaderSource = "\n"
    "attribute vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}\0";
const GLchar* fragmentShaderSource = "\n"
    "\n"
    "void main()\n"
    "{\n"
    "gl_FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

void
init(void)
{
  width  = 1280.0;                 /* initial window width and height, */
  height = 800.0;                  /* within which we draw. */

  return;
}

void
display(void)
{
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // Draw our first triangle
  glUseProgram(shader->id);
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  glFlush();
}

void update(void)
{
  ref_update_auto_release_pool();
}

void
reshape(int w, int h)
{
  width = (GLdouble) w;
  height = (GLdouble) h;

  glViewport(0, 0, (GLsizei) width, (GLsizei) height);

  return;
}

void
kbd(unsigned char key, int x, int y)
{
  switch((char)key) {
  case 'q':
  case 27:    /* ESC */
    shader->release(shader);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glutDestroyWindow(wd);

    ref_update_auto_release_pool();
    exit(0);
  default:
    break;
  }

  return;
}

int
main(int argc, char *argv[])
{
  /* perform initialization NOT OpenGL/GLUT dependent,
     as we haven't created a GLUT window yet */
  init();
  /* initialize GLUT, let it extract command-line
     GLUT options that you may provide
     - NOTE THE '&' BEFORE argc */
  glutInit(&argc, argv);

  /* specify the display to be single
     buffered and color as RGBA values */
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

  /* set the initial window size */
  glutInitWindowSize((int) width, (int) height);

  /* create the window and store the handle to it */
  wd = glutCreateWindow("Experiment with line drawing" /* title */ );

  /* --- register callbacks with GLUT --- */

  /* register function to handle window resizes */
  glutReshapeFunc(reshape);

  /* register keyboard event processing function */
  glutKeyboardFunc(kbd);

  /* register function that draws in the window */
  glutDisplayFunc(display);

  glutIdleFunc(update);

  /* init GL */
  glClearColor(1.0, 1.0, 1.0, 0.0);

  //-----------------------------------------------
  // Build and compile our shader program
  shader = shader_new(vertexShaderSource, fragmentShaderSource);
  shader->retain(shader);

  GLfloat vertices[] = {
       0.5f,  0.5f, 0.0f,  // Top Right
       0.5f, -0.5f, 0.0f,  // Bottom Right
      -0.5f, -0.5f, 0.0f,  // Bottom Left
      -0.5f,  0.5f, 0.0f   // Top Left
  };
  GLuint indices[] = {  // Note that we start from 0!
      0, 1, 3,  // First Triangle
      1, 2, 3   // Second Triangle
  };
  VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

  glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

  /* start the GLUT main loop */
  glutMainLoop();

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  exit(0);
}
