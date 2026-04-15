/**
 * @file input_handler.cpp
 * @brief Implementación de la lectura de mandos para Carley Play.
 *
 * El usuario debe conectar las funciones del kernel aquí.
 */

#include "input_handler.h"

// Estas funciones deben ser implementadas en el kernel del usuario
extern "C" {
    void kernel_get_gamepad_state(cp_gamepad_state_t * state);
}

static cp_gamepad_state_t last_state;
static lv_group_t * g;

void cp_input_init(void)
{
    g = lv_group_create();
    lv_group_set_default(g);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = cp_gamepad_read;
    lv_indev_t * indev = lv_indev_register(&indev_drv);
    lv_indev_set_group(indev, g);
}

lv_group_t* cp_input_get_group(void)
{
    return g;
}

void cp_gamepad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    cp_gamepad_state_t current_state;

    // Leer el estado real desde el hardware/kernel
    kernel_get_gamepad_state(&current_state);

    // Mapear los botones a teclas de LVGL
    if(current_state.up) data->key = LV_KEY_UP;
    else if(current_state.down) data->key = LV_KEY_DOWN;
    else if(current_state.left) data->key = LV_KEY_LEFT;
    else if(current_state.right) data->key = LV_KEY_RIGHT;
    else if(current_state.ok) data->key = LV_KEY_ENTER;
    else if(current_state.back) data->key = LV_KEY_ESC;

    // Detectar si algún botón está presionado
    if(current_state.up || current_state.down || current_state.left ||
       current_state.right || current_state.ok || current_state.back) {
        data->state = LV_INDEV_STATE_PR;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}
