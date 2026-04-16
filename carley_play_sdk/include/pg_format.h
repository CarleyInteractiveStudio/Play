#ifndef PG_FORMAT_H
#define PG_FORMAT_H

#include <stdint.h>

/**
 * @file pg_format.h
 * @brief Definición del formato de archivo .pg (Play Game) para Carley Play.
 */

#define PG_SIGNATURE "PG"
#define PG_VERSION   0x01

typedef struct {
    char signature[2];      // "PG"
    uint8_t version;        // Versión del formato
    uint8_t padding;
    char title[64];         // Nombre del juego
    char developer[64];     // Desarrollador
    uint32_t code_size;     // Tamaño del binario ejecutable
    uint32_t icon_offset;   // Desplazamiento de la imagen del icono
    uint32_t icon_size;     // Tamaño del icono (PNG/BMP)
    uint32_t entry_point;   // Dirección de memoria de inicio
    uint32_t checksum;      // Verificación de integridad
} pg_header_t;

#endif // PG_FORMAT_H
