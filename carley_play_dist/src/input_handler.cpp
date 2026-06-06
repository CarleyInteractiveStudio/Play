/**
 * @file input_handler.cpp
 * @brief Implementación de la lectura de mandos para Carley Play (LVGL v9).
 */

#include "input_handler.h"

extern "C" {
    void kernel_get_gamepad_state(cp_gamepad_state_t * state);
}

static lv_group_t * g;

void cp_gamepad_read(lv_indev_t * indev, lv_indev_data_t * data)
{
    cp_gamepad_state_t current_state;
    kernel_get_gamepad_state(&current_state);

    if(current_state.up) data->key = LV_KEY_UP;
    else if(current_state.down) data->key = LV_KEY_DOWN;
    else if(current_state.left) data->key = LV_KEY_LEFT;
    else if(current_state.right) data->key = LV_KEY_RIGHT;
    else if(current_state.ok) data->key = LV_KEY_ENTER;
    else if(current_state.back) data->key = LV_KEY_ESC;

    if(current_state.up || current_state.down || current_state.left ||
       current_state.right || current_state.ok || current_state.back) {
        data->state = LV_INDEV_STATE_PR;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}

void cp_input_init(void)
{
    g = lv_group_create();
    lv_group_set_default(g);

    lv_indev_t * indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_KEYPAD);
    lv_indev_set_read_cb(indev, cp_gamepad_read);
    lv_indev_set_group(indev, g);
}

lv_group_t* cp_input_get_group(void)
{
    return g;
}
