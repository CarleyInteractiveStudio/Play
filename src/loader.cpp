#include "loader.h"
#include "sdmmc.h"

typedef void (*game_entry_t)(void);

void loader_run_game(uint32_t lba, uint32_t size_sectors, uint32_t load_addr)
{
    uint8_t * dest = (uint8_t *)load_addr;

    // 1. Detener el sistema (Timers, Video si es necesario)
    // kernel_stop();

    // 2. Cargar el juego de la SD a la RAM sector por sector
    for(uint32_t i = 0; i < size_sectors; i++) {
        sd_read_block(lba + i, dest + (i * 512));
    }

    // 3. Saltar a la dirección de ejecución
    game_entry_t start_game = (game_entry_t)load_addr;
    start_game();
}
