#ifndef GPU_MALI_H
#define GPU_MALI_H

#include <stdint.h>

/**
 * @file gpu_mali.h
 * @brief Driver base para la GPU Mali-400 del RK3128.
 */

/**
 * @brief Inicializa y enciende la GPU Mali.
 */
void gpu_init(void);

/**
 * @brief Reserva una sección de la RAM para uso exclusivo de la GPU (VRAM).
 */
void* vram_alloc(uint32_t size);

#endif // GPU_MALI_H
