#include "cp_physics.h"

bool cp_check_collision(cp_aabb_t a, cp_aabb_t b)
{
    return (a.x < (b.x + b.w) && (a.x + a.w) > b.x) &&
           (a.y < (b.y + b.h) && (a.y + a.h) > b.y) &&
           (a.z < (b.z + b.d) && (a.z + a.d) > b.z);
}

void cp_apply_gravity(float * y, float * velocity_y, float dt)
{
    const float gravity = -9.8f;
    *velocity_y += gravity * dt;
    *y += *velocity_y * dt;

    if(*y < 0.0f) { // Suelo
        *y = 0.0f;
        *velocity_y = 0.0f;
    }
}
