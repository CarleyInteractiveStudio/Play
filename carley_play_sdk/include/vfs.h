#ifndef VFS_H
#define VFS_H

#include <stdint.h>
#include "fat32.h"

/**
 * @file vfs.h
 * @brief Sistema de Archivos Virtual (VFS) para compatibilidad POSIX.
 */

#define MAX_FDS 16

typedef struct {
    int active;
    fat_file_t fat_file;
    uint32_t cursor;
} vfs_fd_t;

/**
 * @brief Inicializa la tabla de descriptores de archivos.
 */
void vfs_init(void);

#endif // VFS_H
