#ifndef CPL_FORMAT_H
#define CPL_FORMAT_H

#include <stdint.h>

/**
 * @file cpl_format.h
 * @brief Formato de Librería Compartida (.cpl) para Carley Play.
 */

#define CPL_SIGNATURE "CPL"

typedef struct {
    char signature[3];
    uint32_t num_exports;
    // Lista de nombres y direcciones de exportación
} cpl_header_t;

typedef struct {
    char name[32];
    uint32_t addr;
} cpl_export_t;

#endif // CPL_FORMAT_H
