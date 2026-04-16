#ifndef CP_MATH_H
#define CP_MATH_H

#include <stdint.h>

/**
 * @file cp_math.h
 * @brief Librería matemática acelerada por NEON para juegos 3D.
 */

typedef struct {
    float m[16];
} mat4_t;

/**
 * @brief Multiplica dos matrices 4x4 usando NEON.
 */
void mat4_mul_neon(mat4_t * res, const mat4_t * a, const mat4_t * b);

#endif // CP_MATH_H
