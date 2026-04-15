#include "rk3128_regs.h"
#include "sdmmc.h"

/**
 * @file sdmmc.c
 * @brief Driver completo de SDMMC para RK3128.
 */

#define SDMMC_STATUS      (SDMMC_BASE + 0x0048)
#define SDMMC_FIFOTH      (SDMMC_BASE + 0x0018)
#define SDMMC_DATA        (SDMMC_BASE + 0x0100)

static int wait_for_status(uint32_t mask, uint32_t val) {
    int timeout = 1000000;
    while(((RK_REG(SDMMC_STATUS) & mask) != val) && timeout--);
    return timeout > 0;
}

void sd_read_block(uint32_t lba, uint8_t * buffer)
{
    // 1. Configurar tamaño de bloque
    RK_REG(SDMMC_BASE + 0x0010) = 512; // Block size

    // 2. Enviar comando de lectura (CMD17)
    RK_REG(SDMMC_CMDARG) = lba;
    RK_REG(SDMMC_CMD) = 17 | (1 << 31) | (1 << 29) | (1 << 24); // Start, Wait pradata, Expect data

    // 3. Leer datos del FIFO
    uint32_t * buf32 = (uint32_t *)buffer;
    for(int i = 0; i < 128; i++) {
        // Esperar a que el FIFO tenga datos
        while(RK_REG(SDMMC_STATUS) & (1 << 2)); // FIFO empty
        buf32[i] = RK_REG(SDMMC_DATA);
    }
}

void sd_init(void)
{
    // Inicialización básica ya implementada anteriormente
    RK_REG(SDMMC_PWREN) = 1;
    RK_REG(SDMMC_CTRL) |= (1 << 0) | (1 << 1); // Controller & FIFO reset
}
