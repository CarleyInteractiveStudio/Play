#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "lvgl/lvgl.h"

/**
 * @file input_handler.h
 * @brief Interfaz para la entrada de mandos en Carley Play.
 */

// Estructura para los botones del mando
typedef struct {
    bool up;
    bool down;
    bool left;
    bool right;
    bool ok;    // Botón A o similar
    bool back;  // Botón B o similar
} cp_gamepad_state_t;

/**
 * @brief Inicializa el driver de entrada para LVGL.
 */
void cp_input_init(void);

/**
 * @brief Obtiene el grupo de entrada para asociar objetos de la UI.
 */
lv_group_t* cp_input_get_group(void);

/**
 * @brief Función que LVGL llamará periódicamente para leer el mando.
 */
void cp_gamepad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);

#endif // INPUT_HANDLER_H
