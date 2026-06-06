#include "mmu.h"
#include <string.h>

static uint32_t ttb[4096] __attribute__((aligned(TTB_SIZE)));

void mmu_init(void)
{
    // Crear mapa 1:1 para los 4GB de espacio de direccionamiento
    for(uint32_t i = 0; i < 4096; i++) {
        // Atributos: Sección de 1MB, Cacheable, Bufferable
        ttb[i] = (i << 20) | (3 << 10) | (1 << 3) | (1 << 2) | 2;
    }

    // Cargar TTB base
    uint32_t base = (uint32_t)ttb;
    __asm__ volatile ("mcr p15, 0, %0, c2, c0, 0" : : "r" (base));

    // Configurar dominios y habilitar MMU
    __asm__ volatile ("mcr p15, 0, %0, c3, c0, 0" : : "r" (0xFFFFFFFF));
    uint32_t ctrl;
    __asm__ volatile ("mrc p15, 0, %0, c1, c0, 0" : "=r" (ctrl));
    __asm__ volatile ("mcr p15, 0, %0, c1, c0, 0" : : "r" (ctrl | 1));
}

void mmu_protect_game(uint32_t game_addr, uint32_t size)
{
    // Modificar los permisos de las secciones del juego en la TTB
}
