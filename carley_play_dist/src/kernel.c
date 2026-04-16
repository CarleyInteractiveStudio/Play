/**
 * @file kernel.c
 * @brief Implementación del Kernel y Runtime para Carley Play.
 */

#include "lvgl/lvgl.h"
#include "input_handler.h"
#include "rk3128_regs.h"
#include "kernel.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

// --- GESTIÓN DE MEMORIA DINÁMICA (Heap Avanzado) ---
#define HEAP_SIZE (64 * 1024 * 1024) // 64MB de Heap para LVGL y otros
static uint8_t heap[HEAP_SIZE];

typedef struct block_header {
    size_t size;
    int free;
    struct block_header *next;
} block_header_t;

static block_header_t *free_list = (block_header_t *)heap;

void kernel_init_malloc(void) {
    free_list->size = HEAP_SIZE - sizeof(block_header_t);
    free_list->free = 1;
    free_list->next = NULL;
}

void * malloc(size_t size) {
    size = (size + 7) & ~7;
    block_header_t *curr = free_list;
    while(curr) {
        if(curr->free && curr->size >= size) {
            if(curr->size > size + sizeof(block_header_t) + 8) {
                block_header_t *next = (block_header_t *)((uint8_t *)curr + sizeof(block_header_t) + size);
                next->size = curr->size - size - sizeof(block_header_t);
                next->free = 1;
                next->next = curr->next;
                curr->size = size;
                curr->next = next;
            }
            curr->free = 0;
            return (void *)((uint8_t *)curr + sizeof(block_header_t));
        }
        curr = curr->next;
    }
    return NULL;
}

void free(void * ptr) {
    if(!ptr) return;
    block_header_t *header = (block_header_t *)((uint8_t *)ptr - sizeof(block_header_t));
    header->free = 1;
}

char * strdup(const char * s) {
    size_t len = strlen(s) + 1;
    char * d = (char *)malloc(len);
    if (d) memcpy(d, s, len);
    return d;
}

// --- IMPLEMENTACIÓN POSIX LITE ---
int open(const char *pathname, int flags, ...) { return -1; }
int close(int fd) { return 0; }
long read(int fd, void *buf, size_t count) { return 0; }
long write(int fd, const void *buf, size_t count) { return 0; }
off_t lseek(int fd, off_t offset, int whence) { return 0; }

uint32_t kernel_get_free_ram(void) {
    uint32_t total_free = 0;
    block_header_t *curr = free_list;
    while(curr) {
        if(curr->free) total_free += curr->size;
        curr = curr->next;
    }
    return total_free;
}

// --- RESTO DE FUNCIONES DEL KERNEL ---

void * memcpy(void * dest, const void * src, size_t n) {
    uint8_t * d = (uint8_t *)dest;
    const uint8_t * s = (const uint8_t *)src;
    while (n--) *d++ = *s++;
    return dest;
}

void kernel_init_system(void) {
    // Overclock CPU a 1.2GHz (Configuración de APLL)
    // RK_REG(CRU_BASE + 0x0000) = ... ;

    RK_REG(CRU_CLKGATE_CON(0)) = 0;
    RK_REG(CRU_CLKGATE_CON(1)) = 0;
    kernel_init_malloc();
}

#define FB_ADDR 0x01000000
void kernel_init_video(void) {
    VOP_REG(VOP_WIN0_YRGB_MST) = FB_ADDR;
    VOP_REG(VOP_SYS_CTRL) |= (1 << 0);
    VOP_REG(VOP_REG_DONE_EN) |= (1 << 0);
}

void kernel_flush_area(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map) {
    uint32_t * fb = (uint32_t *)FB_ADDR;
    int32_t area_width = lv_area_get_width(area);

    // Uso de DMA para copias rápidas (Canal 0)
    for(int32_t y = area->y1; y <= area->y2; y++) {
        RK_REG(DMA_SRC(0)) = (uint32_t)&px_map[(y - area->y1) * area_width * 4];
        RK_REG(DMA_DST(0)) = (uint32_t)&fb[y * 1280 + area->x1];
        RK_REG(DMA_LEN(0)) = area_width * 4;
        RK_REG(DMA_CTRL) |= 0x1; // Iniciar transferencia
        while(RK_REG(DMA_CTRL) & 0x1); // Esperar a DMA
    }
    lv_display_flush_ready(disp);
}

// --- TICK Y HARDWARE ---
#define TIMER_BASE 0x20044000
#define TIMER_REG(offset) (*(volatile uint32_t *)(TIMER_BASE + offset))

void kernel_init_timer(void) {
    TIMER_REG(0x0004) = 24000;
    TIMER_REG(0x0010) = 3;
}

uint32_t lv_tick_get_cb(void) {
    // Leemos el registro de cuenta actual del Timer del RK3128
    // Dividimos por la frecuencia (ej: 24MHz) para obtener ms reales
    uint32_t current_count = TIMER_REG(0x0000);
    static uint32_t last_count = 0;
    static uint32_t elapsed_ms = 0;

    if (last_count == 0) last_count = current_count;

    // El timer suele ser decreciente
    uint32_t diff = last_count - current_count;
    if (diff >= 24000) { // 1ms a 24MHz
        elapsed_ms += (diff / 24000);
        last_count = current_count;
    }

    return elapsed_ms;
}

extern void uart_init(void);
extern void uart_print(const char* s);

void kernel_init_hardware(void) {
    kernel_init_system();
    uart_init();
    uart_print("Carley Play OS Booting...\n");
    kernel_init_video();
    kernel_init_timer();
    RK_REG(0x2003c010) |= 1;
}

void _startup_entry(void) {
    extern int main(void);
    main();
    while(1);
}
