#include "rk3128_regs.h"
#include "input_handler.h"

/**
 * @file usb_gamepad.c
 * @brief Driver de Host USB para mandos inalámbricos en Carley Play.
 */

#define USB_GINTSTS       (USB_HOST_BASE + 0x0014)
#define USB_HAINT         (USB_HOST_BASE + 0x0414)

void usb_host_init(void)
{
    // 1. Reset PHY y controlador
    RK_REG(CRU_SOFTRST_CON(0)) |= (1 << 10);
    for(volatile int i=0; i<2000; i++);
    RK_REG(CRU_SOFTRST_CON(0)) &= ~(1 << 10);

    // 2. Habilitar interrupciones de Host
    RK_REG(USB_HOST_BASE + 0x0400) = 0x1; // Host config
}

void kernel_get_gamepad_state(cp_gamepad_state_t * state)
{
    // Jugador 1
    state->up = false;
    state->down = false;
    state->left = false;
    state->right = false;
    state->ok = false;
    state->back = false;
}

void cp_get_gamepad2_state(cp_gamepad_state_t * state)
{
    // Jugador 2
    state->up = false;
    state->down = false;
    state->left = false;
    state->right = false;
    state->ok = false;
    state->back = false;
}
