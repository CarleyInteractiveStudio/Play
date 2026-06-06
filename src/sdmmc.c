#include "rk3128_regs.h"
#include "sdmmc.h"

/**
 * @file sdmmc.c
 * @brief Driver avanzado de SDMMC para RK3128 (Sin simulaciones).
 */

#define SD_CMD_ALL_SEND_CID 2
#define SD_CMD_SET_REL_ADDR  3
#define SD_CMD_SELECT_CARD   7

static void sd_delay(uint32_t count) {
    for(volatile uint32_t i = 0; i < count; i++);
}

static int sd_wait_cmd_done(void) {
    int timeout = 100000;
    while((RK_REG(SDMMC_MINTSTS) & (1 << 2)) == 0 && timeout--);
    RK_REG(SDMMC_MINTSTS) = 0xFFFFFFFF; // Clear all
    return timeout > 0;
}

void sd_init(void)
{
    // 1. Encendido y Reset
    RK_REG(SDMMC_PWREN) = 1;
    RK_REG(SDMMC_CTRL) |= (1 << 0) | (1 << 1);
    sd_delay(1000);

    // 2. CMD0: Idle State
    RK_REG(SDMMC_CMDARG) = 0;
    RK_REG(SDMMC_CMD) = 0 | (1 << 31) | (1 << 29);
    sd_wait_cmd_done();

    // 3. CMD8: Check Voltage (Interface Condition)
    RK_REG(SDMMC_CMDARG) = 0x1AA;
    RK_REG(SDMMC_CMD) = 8 | (1 << 31) | (1 << 29) | (1 << 24);
    sd_wait_cmd_done();

    // 4. ACMD41: Negociar voltaje y esperar a que la tarjeta esté lista
    int ready = 0;
    while(!ready) {
        // APP_CMD (CMD55)
        RK_REG(SDMMC_CMDARG) = 0;
        RK_REG(SDMMC_CMD) = 55 | (1 << 31) | (1 << 29);
        sd_wait_cmd_done();

        // OP_COND (ACMD41)
        RK_REG(SDMMC_CMDARG) = 0x40FF8000; // HCS + Voltage Window
        RK_REG(SDMMC_CMD) = 41 | (1 << 31) | (1 << 29);
        sd_wait_cmd_done();

        if(RK_REG(SDMMC_RESP0) & (1 << 31)) ready = 1;
    }

    // 5. Obtener CID y RCA
    RK_REG(SDMMC_CMD) = 2 | (1 << 31) | (1 << 29); // CMD2
    sd_wait_cmd_done();

    RK_REG(SDMMC_CMD) = 3 | (1 << 31) | (1 << 29); // CMD3
    sd_wait_cmd_done();
    uint32_t rca = RK_REG(SDMMC_RESP0) & 0xFFFF0000;

    // 6. Seleccionar tarjeta
    RK_REG(SDMMC_CMDARG) = rca;
    RK_REG(SDMMC_CMD) = 7 | (1 << 31) | (1 << 29); // CMD7
    sd_wait_cmd_done();
}

void sd_read_block(uint32_t lba, uint8_t * buffer)
{
    RK_REG(SDMMC_BASE + 0x0010) = 512;
    RK_REG(SDMMC_CMDARG) = lba;
    RK_REG(SDMMC_CMD) = 17 | (1 << 31) | (1 << 29) | (1 << 24);

    uint32_t * buf32 = (uint32_t *)buffer;
    for(int i = 0; i < 128; i++) {
        while(RK_REG(SDMMC_BASE + 0x0048) & (1 << 2)); // Wait for data
        buf32[i] = RK_REG(SDMMC_BASE + 0x0100);
    }
}
