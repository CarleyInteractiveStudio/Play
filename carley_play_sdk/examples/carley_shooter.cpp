#include "cp_sdk.h"
#include "cp_math.h"
#include "cp_physics.h"

/**
 * @file carley_shooter.cpp
 * @brief Ejemplo de Shooter en Primera Persona para Carley Play OS.
 */

static float cam_x = 0, cam_y = 1.7f, cam_z = 0;
static float cam_yaw = 0;

void game_init()
{
    // Cargar texturas de armas y enemigos
    // cp_gpu_load_image("weapon.png");
}

void game_loop(float dt)
{
    cp_input_t input;
    cp_get_input(&input);

    // Movimiento
    if(input.up) cam_z += 5.0f * dt;
    if(input.down) cam_z -= 5.0f * dt;
    if(input.left) cam_yaw -= 2.0f * dt;
    if(input.right) cam_yaw += 2.0f * dt;

    // Disparar
    if(input.a) {
        // audio_play_sfx(GUNSHOT);
        // check_hit_npc();
    }

    // Dibujar escena
    // cp_gpu_set_camera(cam_x, cam_y, cam_z, cam_yaw);
    // cp_gpu_draw_world();
}
