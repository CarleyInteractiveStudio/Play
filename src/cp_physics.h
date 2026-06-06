#ifndef CP_PHYSICS_H
#define CP_PHYSICS_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @file cp_physics.h
 * @brief Módulo de físicas 3D para Carley Play.
 */

typedef struct {
    float x, y, z;
    float w, h, d;
} cp_aabb_t;

/**
 * @brief Detecta colisión entre dos cajas AABB.
 */
bool cp_check_collision(cp_aabb_t a, cp_aabb_t b);

/**
 * @brief Aplica gravedad a una posición.
 */
void cp_apply_gravity(float * y, float * velocity_y, float dt);

#endif // CP_PHYSICS_H
