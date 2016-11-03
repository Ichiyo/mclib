#ifndef _M_GRAPHIC_H
#define _M_GRAPHIC_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GLES3/gl3.h>
#endif

#ifdef __cplusplus
}
#endif

#endif
