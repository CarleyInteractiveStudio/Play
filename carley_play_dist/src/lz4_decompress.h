#ifndef LZ4_DECOMPRESS_H
#define LZ4_DECOMPRESS_H

#include <stdint.h>

/**
 * @file lz4_decompress.h
 * @brief Descompresor LZ4 ultra-ligero para el cargador de Carley Play.
 */

int lz4_decompress(const uint8_t* source, uint8_t* dest, uint32_t source_size, uint32_t max_dest_size);

#endif // LZ4_DECOMPRESS_H
