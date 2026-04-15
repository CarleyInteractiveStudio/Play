#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <stdint.h>

/**
 * @file config_manager.h
 * @brief Gestión de ajustes persistentes en Carley Play.
 */

typedef struct {
    uint8_t volume;
    uint8_t language;
    uint8_t brightness;
} cp_config_t;

/**
 * @brief Carga la configuración desde system.cfg en la SD.
 */
void config_load(void);

/**
 * @brief Guarda la configuración actual en system.cfg.
 */
void config_save(void);

/**
 * @brief Obtiene el objeto de configuración actual.
 */
cp_config_t* config_get(void);

#endif // CONFIG_MANAGER_H
