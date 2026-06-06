#ifndef VPU_RK_H
#define VPU_RK_H

#include <stdint.h>

/**
 * @file vpu_rk.h
 * @brief Driver de la Video Processing Unit (VPU) para RK3128.
 */

#define VPU_BASE 0x10100000

/**
 * @brief Inicializa el decodificador de video por hardware.
 */
void vpu_init(void);

/**
 * @brief Decodifica un frame de video (H.264/MPEG4).
 */
void vpu_decode_frame(const uint8_t * bitstream, uint32_t size, uint32_t out_addr);

#endif // VPU_RK_H
