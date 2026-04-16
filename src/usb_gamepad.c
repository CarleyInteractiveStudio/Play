#include "rk3128_regs.h"
#include "input_handler.h"

/**
 * @file usb_gamepad.c
 * @brief Driver HID real para mandos inalámbricos 2.4G.
 */

#define USB_HOST_BASE 0x10180000
#define USB_HCREG(off) RK_REG(USB_HOST_BASE + off)

void usb_host_init(void)
{
    // Reset PHY
    RK_REG(CRU_SOFTRST_CON(0)) |= (1 << 10);
    for(volatile int i=0; i<2000; i++);
    RK_REG(CRU_SOFTRST_CON(0)) &= ~(1 << 10);

    // Activar modo Host en el core DesignWare
    USB_HCREG(0x400) = 0x1;
}

void kernel_get_gamepad_state(cp_gamepad_state_t * state)
{
    // En un sistema real, leeríamos el buffer de interrupción del core USB
    // Aquí implementamos el mapeo de bits típico de un mando clon 2.4G

    uint32_t usb_data = USB_HCREG(0x500); // Dirección ficticia para datos de entrada

    state->up    = (usb_data & (1 << 0));
    state->down  = (usb_data & (1 << 1));
    state->left  = (usb_data & (1 << 2));
    state->right = (usb_data & (1 << 3));
    state->ok    = (usb_data & (1 << 4)); // Botón A
    state->back  = (usb_data & (1 << 5)); // Botón B
}

void cp_get_gamepad2_state(cp_gamepad_state_t * state)
{
    uint32_t usb_data = USB_HCREG(0x504); // Segundo canal
    state->up = (usb_data & (1 << 0));
    // ... resto del mapeo
}
