#include "ota.h"
#include "carley_net.h"
#include "sdmmc.h"

void ota_update_system(const char * url)
{
    // 1. Descargar nueva versión a la RAM
    // net_download_file(url, "temp_fw.bin");

    // 2. Escribir directamente en los sectores de arranque de la SD
    // uint8_t fw_data[FW_SIZE];
    // sd_write_block(BOOT_SECTOR, fw_data);
}
