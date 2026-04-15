/**
 * @file kernel.c
 * @brief Implementación del Kernel y Runtime para Carley Play (GB2 / ARM).
 */

#include "lvgl/lvgl.h"
#include "input_handler.h"
#include <stddef.h>

// --- HEAP ESTÁTICO PARA BARE METAL ---
#define HEAP_SIZE (16 * 1024 * 1024) // 16MB de Heap
static uint8_t heap[HEAP_SIZE];
static size_t heap_ptr = 0;

/**
 * @brief Implementación básica de malloc para Bare Metal.
 */
void * malloc(size_t size) {
    if (heap_ptr + size > HEAP_SIZE) return NULL;
    void * ptr = &heap[heap_ptr];
    heap_ptr += (size + 7) & ~7; // Alineación a 8 bytes
    return ptr;
}

void free(void * ptr) {
    // No implementado para este prototipo (Heap simple de solo crecimiento)
}

/**
 * @brief Inicializa el hardware de video (Placeholder).
 */
void kernel_init_video(void)
{
    // Aquí irían los registros del RK3128 para HDMI
}

/**
 * @brief Envía el buffer de píxeles a la pantalla real (Placeholder).
 */
void kernel_flush_area(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map)
{
    // Aquí iría la copia al Framebuffer real
    lv_display_flush_ready(disp);
}

/**
 * @brief Lee el estado de los botones del mando (Placeholder).
 */
void kernel_get_gamepad_state(cp_gamepad_state_t * state)
{
    state->up = false;
    state->down = false;
    state->left = false;
    state->right = false;
    state->ok = false;
    state->back = false;
}

// --- TICK DEL SISTEMA ---
/**
 * @brief LVGL necesita saber cuántos ms han pasado.
 */
uint32_t lv_tick_get_cb(void) {
    static uint32_t tick = 0;
    return tick++; // Simulación de tick
}

void _start(void)
{
    extern int main(void);
    main();
    while(1);
}
