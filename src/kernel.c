/**
 * @file kernel.c
 * @brief Implementación del Kernel y Runtime para Carley Play (GB2 / ARM).
 */

#include "lvgl/lvgl.h"
#include "input_handler.h"
#include <stddef.h>
#include <stdint.h>

// --- MAPA DE REGISTROS RK3128 (GB2) ---
// Nota: Estas direcciones son típicas para la serie RK312X.
// Deben verificarse con el manual técnico específico del GB2.
#define VOP_BASE          0x10128000
#define VOP_REG(offset)   (*(volatile uint32_t *)(VOP_BASE + offset))

#define VOP_SYS_CTRL      0x0000
#define VOP_DSP_CTRL0     0x0010
#define VOP_DSP_CTRL1     0x0014
#define VOP_WIN0_CTRL0    0x0030
#define VOP_WIN0_YRGB_MST 0x005C // Dirección del Framebuffer en RAM

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
 * @brief Inicializa el hardware de video.
 * Configura el VOP (Video Output Processor) para apuntar a nuestro Framebuffer.
 */
#define FB_ADDR 0x01000000 // Dirección sugerida para el Framebuffer en los 256MB de RAM
void kernel_init_video(void)
{
    // 1. Habilitar el VOP
    VOP_REG(VOP_SYS_CTRL) |= (1 << 0);

    // 2. Configurar la dirección base de la imagen (Win0)
    VOP_REG(VOP_WIN0_YRGB_MST) = FB_ADDR;

    // 3. Activar cambios
    VOP_REG(VOP_SYS_CTRL) |= (1 << 31); // Config Done
}

/**
 * @brief Envía el buffer de píxeles a la pantalla real.
 * Copia los píxeles renderizados por LVGL a la memoria de video (FB_ADDR).
 */
void kernel_flush_area(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map)
{
    uint32_t * fb = (uint32_t *)FB_ADDR;
    int32_t x, y;
    int32_t width = lv_area_get_width(area);
    uint32_t * src = (uint32_t *)px_map;

    for(y = area->y1; y <= area->y2; y++) {
        for(x = area->x1; x <= area->x2; x++) {
            // Copia el píxel al Framebuffer (formato ARGB8888)
            fb[y * 1280 + x] = src[(y - area->y1) * width + (x - area->x1)];
        }
    }

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
