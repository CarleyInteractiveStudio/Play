#ifndef FAT32_H
#define FAT32_H

#include <stdint.h>

/**
 * @file fat32.h
 * @brief Lector de archivos FAT32 para Bare Metal (Carley Play).
 */

typedef struct {
    char name[11];
    uint8_t attr;
    uint32_t first_cluster;
    uint32_t size;
} fat_file_t;

/**
 * @brief Inicializa el sistema de archivos buscando la partición FAT32.
 * @return 0 si éxito.
 */
int fat32_init(void);

/**
 * @brief Abre un archivo por nombre.
 */
int fat32_open(const char* filename, fat_file_t* file);

/**
 * @brief Lee datos de un archivo.
 */
int fat32_read(fat_file_t* file, uint32_t offset, uint32_t size, uint8_t* buffer);

#endif // FAT32_H
