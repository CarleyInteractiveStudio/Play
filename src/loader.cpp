#include "loader.h"
#include "sdmmc.h"
#include "pg_format.h"
#include <string.h>

typedef void (*game_entry_t)(void);

void loader_run_game(uint32_t lba, uint32_t size_sectors, uint32_t load_addr)
{
    uint8_t * dest = (uint8_t *)load_addr;

    // 1. Preparar el entorno para un motor de juego (Unity/Unreal)
    // Liberar la mayor parte de la RAM (192MB para el juego)
    // kernel_prepare_engine_runtime();

    // 2. Leer Cabecera PG
    pg_header_t header;
    sd_read_block(lba, (uint8_t*)&header);

    if (strncmp(header.signature, PG_SIGNATURE, 2) != 0) {
        // No es un archivo .pg válido
        return;
    }

    // 3. Cargar el binario real (después de la cabecera)
    uint8_t * code_dest = (uint8_t *)header.entry_point;
    uint32_t start_lba = lba + (sizeof(pg_header_t) / 512) + 1;
    uint32_t num_sectors = (header.code_size + 511) / 512;

    for(uint32_t i = 0; i < num_sectors; i++) {
        sd_read_block(start_lba + i, code_dest + (i * 512));
    }

    // 4. Configurar puntero de pila y saltar
    // __asm__ volatile ("mov sp, %0" : : "r" (0x0FFFFFFF));

    game_entry_t start_game = (game_entry_t)load_addr;
    start_game();
}
