#ifndef _M_GRAPHIC_H
#define _M_GRAPHIC_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GLES3/gl3.h>
#endif

#ifdef __cplusplus
}
#endif

#endif
