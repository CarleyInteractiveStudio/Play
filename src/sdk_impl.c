#include "cp_sdk.h"
#include "rk3128_regs.h"
#include <arm_neon.h>

// Implementación de las funciones del SDK que los juegos usarán
void cp_get_input(cp_input_t * input)
{
    // Llamar a la lógica interna de usb_gamepad
}

void cp_play_pcm(const uint8_t * data, uint32_t size)
{
    // Llamar al mixer
}

// Optimización NEON para mezcla de colores (Alpha Blending)
uint32_t cp_alpha_blend_neon(uint32_t bg, uint32_t fg)
{
    // Cargar 1 píxel (ARGB)
    uint8x8_t v_bg = vld1_u8((uint8_t*)&bg);
    uint8x8_t v_fg = vld1_u8((uint8_t*)&fg);

    uint8_t alpha = fg >> 24;
    uint8_t inv_alpha = 255 - alpha;

    // Fórmula simple: (fg * alpha + bg * inv_alpha) / 256 (simplificado)
    uint16x8_t v_res = vmull_u8(v_fg, vdup_n_u8(alpha));
    v_res = vmlal_u8(v_res, v_bg, vdup_n_u8(inv_alpha));

    uint8x8_t v_final = vshrn_n_u16(v_res, 8);
    uint32_t result;
    vst1_u8((uint8_t*)&result, v_final);
    return result;
}
