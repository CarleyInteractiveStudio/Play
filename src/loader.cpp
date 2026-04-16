#include "loader.h"
#include "sdmmc.h"

typedef void (*game_entry_t)(void);

void loader_run_game(uint32_t lba, uint32_t size_sectors, uint32_t load_addr)
{
    uint8_t * dest = (uint8_t *)load_addr;

    // 1. Preparar el entorno para un motor de juego (Unity/Unreal)
    // Liberar la mayor parte de la RAM (192MB para el juego)
    // kernel_prepare_engine_runtime();

    // 2. Cargar el binario pesado (DMA habilitado si está disponible)
    for(uint32_t i = 0; i < size_sectors; i++) {
        sd_read_block(lba + i, dest + (i * 512));
    }

    // 3. Configurar puntero de pila y saltar
    // __asm__ volatile ("mov sp, %0" : : "r" (0x0FFFFFFF));

    game_entry_t start_game = (game_entry_t)load_addr;
    start_game();
}
