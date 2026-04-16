#include "cp_sdk.h"
#include "rk3128_regs.h"

// Implementación de las funciones del SDK que los juegos usarán
void cp_get_input(cp_input_t * input)
{
    // Llamar a la lógica interna de usb_gamepad
}

void cp_play_pcm(const uint8_t * data, uint32_t size)
{
    // Llamar al mixer
}
