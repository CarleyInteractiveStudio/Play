#include "loader.h"
#include "sdmmc.h"
#include "pg_format.h"
#include "lz4_decompress.h"
#include "kernel.h"
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

    if (header.compressed_size > 0) {
        // Carga con descompresión LZ4
        uint8_t * comp_buf = (uint8_t *)malloc(header.compressed_size);
        uint32_t num_comp_sectors = (header.compressed_size + 511) / 512;
        for(uint32_t i = 0; i < num_comp_sectors; i++) {
            sd_read_block(start_lba + i, comp_buf + (i * 512));
        }
        lz4_decompress(comp_buf, code_dest, header.compressed_size, header.code_size);
        free(comp_buf);
    } else {
        // Carga directa
        for(uint32_t i = 0; i < num_sectors; i++) {
            sd_read_block(start_lba + i, code_dest + (i * 512));
        }
    }

    // 4. Configurar puntero de pila y saltar
    // __asm__ volatile ("mov sp, %0" : : "r" (0x0FFFFFFF));

    game_entry_t start_game = (game_entry_t)load_addr;
    start_game();
}
