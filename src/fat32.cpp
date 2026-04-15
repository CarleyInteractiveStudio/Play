#include "fat32.h"
#include "sdmmc.h"
#include <string.h>

static uint32_t partition_lba_start = 0;
static uint32_t fat_lba_start = 0;
static uint32_t cluster_lba_start = 0;
static uint32_t sectors_per_cluster = 0;

int fat32_init(void)
{
    uint8_t buffer[512];

    // 1. Leer MBR (Sector 0)
    sd_read_block(0, buffer);

    // Buscar partición FAT32 (ID 0x0C o 0x0B)
    // Simplificado: asumimos que la primera partición es nuestra FAT32
    partition_lba_start = *(uint32_t*)&buffer[446 + 8];

    // 2. Leer Boot Sector de la partición
    sd_read_block(partition_lba_start, buffer);

    sectors_per_cluster = buffer[13];
    uint16_t reserved_sectors = *(uint16_t*)&buffer[14];
    uint8_t num_fats = buffer[16];
    uint32_t sectors_per_fat = *(uint32_t*)&buffer[36];

    fat_lba_start = partition_lba_start + reserved_sectors;
    cluster_lba_start = fat_lba_start + (num_fats * sectors_per_fat);

    return 0;
}

int fat32_open(const char* filename, fat_file_t* file)
{
    // TODO: Implementar búsqueda en el directorio raíz
    return -1;
}

int fat32_read(fat_file_t* file, uint32_t offset, uint32_t size, uint8_t* buffer)
{
    // TODO: Implementar lectura usando la tabla FAT
    return 0;
}

int fat32_create(const char* filename)
{
    // TODO: Implementar creación de entrada de directorio
    return 0;
}

int fat32_write(fat_file_t* file, uint32_t offset, uint32_t size, const uint8_t* buffer)
{
    // TODO: Implementar escritura de bloques y actualización de la FAT
    return 0;
}
