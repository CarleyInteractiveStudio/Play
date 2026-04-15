#ifndef RGA_H
#define RGA_H

#include <stdint.h>

/**
 * @file rga.h
 * @brief Driver de aceleración gráfica 2D (RGA) para RK3128.
 */

#define RGA_BASE 0x10129000

void rga_init(void);

/**
 * @brief Copia un bloque de memoria con aceleración de hardware.
 */
void rga_copy(uint32_t src, uint32_t dst, uint32_t w, uint32_t h, uint32_t stride);

#endif // RGA_H
