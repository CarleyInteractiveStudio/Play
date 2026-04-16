#ifndef GLES_WRAPPER_H
#define GLES_WRAPPER_H

#include <stdint.h>

/**
 * @file gles_wrapper.h
 * @brief Capa de compatibilidad OpenGL ES para motores de juego.
 */

// --- TIPOS GLES ---
typedef float GLfloat;
typedef uint32_t GLenum;
typedef uint32_t GLuint;
typedef int GLint;
typedef int GLsizei;

#define GL_TRIANGLES      0x0004
#define GL_TEXTURE_2D     0x0DE1
#define GL_FLOAT          0x1406

void glClear(GLenum mask);
void glDrawArrays(GLenum mode, GLint first, GLsizei count);
void glBindTexture(GLenum target, GLuint texture);

#endif // GLES_WRAPPER_H
