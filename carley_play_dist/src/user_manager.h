#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <stdint.h>

/**
 * @file user_manager.h
 * @brief Sistema de perfiles de usuario para Carley Play.
 */

typedef struct {
    char name[32];
    uint32_t icon_id;
    uint32_t play_time_hours;
} cp_user_t;

/**
 * @brief Carga los usuarios registrados en la SD.
 */
void users_init(void);

/**
 * @brief Obtiene el usuario activo.
 */
cp_user_t* users_get_current(void);

#endif // USER_MANAGER_H
