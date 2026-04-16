#include "fat32.h"
#include "sdmmc.h"
#include <string.h>

static uint32_t partition_lba_start = 0;
static uint32_t fat_lba_start = 0;
static uint32_t cluster_lba_start = 0;
static uint32_t sectors_per_cluster = 0;
static uint32_t root_cluster = 0;

int fat32_init(void)
{
    uint8_t buffer[512];
    sd_read_block(0, buffer);
    partition_lba_start = *(uint32_t*)&buffer[446 + 8];

    sd_read_block(partition_lba_start, buffer);
    sectors_per_cluster = buffer[13];
    uint16_t reserved_sectors = *(uint16_t*)&buffer[14];
    uint8_t num_fats = buffer[16];
    uint32_t sectors_per_fat = *(uint32_t*)&buffer[36];
    root_cluster = *(uint32_t*)&buffer[44];

    fat_lba_start = partition_lba_start + reserved_sectors;
    cluster_lba_start = fat_lba_start + (num_fats * sectors_per_fat);

    return 0;
}

static uint32_t cluster_to_lba(uint32_t cluster) {
    return cluster_lba_start + (cluster - 2) * sectors_per_cluster;
}

int fat32_open(const char* filename, fat_file_t* file)
{
    uint8_t buffer[512];
    uint32_t current_cluster = root_cluster;

    while(current_cluster < 0x0FFFFFF8) {
        uint32_t lba = cluster_to_lba(current_cluster);
        for(uint32_t s = 0; s < sectors_per_cluster; s++) {
            sd_read_block(lba + s, buffer);
            for(int i = 0; i < 512; i += 32) {
                if(buffer[i] == 0) return -1; // Fin
                if(buffer[i] == 0xE5) continue; // Borrado

                // Comparar nombre (Formato 8.3 simplificado)
                if(strncmp((char*)&buffer[i], filename, 8) == 0) {
                    file->first_cluster = (*(uint16_t*)&buffer[i + 20] << 16) | *(uint16_t*)&buffer[i + 26];
                    file->size = *(uint32_t*)&buffer[i + 28];
                    return 0;
                }
            }
        }
        // Buscar siguiente cluster en la FAT
        uint32_t fat_sector = fat_lba_start + (current_cluster * 4 / 512);
        uint32_t fat_offset = (current_cluster * 4) % 512;
        sd_read_block(fat_sector, buffer);
        current_cluster = *(uint32_t*)&buffer[fat_offset] & 0x0FFFFFFF;
    }
    return -1;
}

int fat32_read(fat_file_t* file, uint32_t offset, uint32_t size, uint8_t* buffer)
{
    // Implementación simplificada de lectura secuencial
    uint32_t current_cluster = file->first_cluster;
    uint32_t bytes_read = 0;
    uint8_t sector_buf[512];

    while(bytes_read < size && current_cluster < 0x0FFFFFF8) {
        uint32_t lba = cluster_to_lba(current_cluster);
        for(uint32_t s = 0; s < sectors_per_cluster && bytes_read < size; s++) {
            sd_read_block(lba + s, sector_buf);
            uint32_t to_copy = (size - bytes_read > 512) ? 512 : size - bytes_read;
            memcpy(buffer + bytes_read, sector_buf, to_copy);
            bytes_read += to_copy;
        }
        // Siguiente cluster
        uint8_t fat_buf[512];
        uint32_t fat_sector = fat_lba_start + (current_cluster * 4 / 512);
        uint32_t fat_offset = (current_cluster * 4) % 512;
        sd_read_block(fat_sector, fat_buf);
        current_cluster = *(uint32_t*)&fat_buf[fat_offset] & 0x0FFFFFFF;
    }
    return bytes_read;
}

int fat32_create(const char* filename) { return 0; }
int fat32_write(fat_file_t* file, uint32_t offset, uint32_t size, const uint8_t* buffer) { return 0; }
