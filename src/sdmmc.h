#ifndef SDMMC_H
#define SDMMC_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
void sd_init(void);
void sd_read_block(uint32_t lba, uint8_t * buffer);
#ifdef __cplusplus
}
#endif
#endif