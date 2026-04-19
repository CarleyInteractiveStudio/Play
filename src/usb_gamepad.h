#ifndef USB_GAMEPAD_H
#define USB_GAMEPAD_H
#include "input_handler.h"
#ifdef __cplusplus
extern "C" {
#endif
void usb_host_init(void);
void kernel_get_gamepad_state(cp_gamepad_state_t * state);
void cp_get_gamepad2_state(cp_gamepad_state_t * state);
#ifdef __cplusplus
}
#endif
#endif