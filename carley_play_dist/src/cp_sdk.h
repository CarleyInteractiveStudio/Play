#ifndef CP_SDK_H
#define CP_SDK_H

#include <stdint.h>

/**
 * @file cp_sdk.h
 * @brief Software Development Kit (SDK) para juegos nativos en Carley Play.
 *
 * Usa estas funciones para interactuar con el hardware de la consola.
 */

// --- VIDEO ---
#define CP_FB_WIDTH  1280
#define CP_FB_HEIGHT 720
#define CP_FB_ADDR   0x01000000

static inline void cp_draw_pixel(int x, int y, uint32_t color) {
    if(x >= 0 && x < CP_FB_WIDTH && y >= 0 && y < CP_FB_HEIGHT) {
        ((uint32_t*)CP_FB_ADDR)[y * CP_FB_WIDTH + x] = color;
    }
}

// --- INPUT ---
typedef struct {
    uint8_t up, down, left, right;
    uint8_t a, b, x, y;
    uint8_t start, select;
} cp_input_t;

void cp_get_input(cp_input_t * input);

// --- AUDIO ---
void cp_play_pcm(const uint8_t * data, uint32_t size);

#endif // CP_SDK_H
