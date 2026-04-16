#ifndef MMU_H
#define MMU_H

#include <stdint.h>

/**
 * @file mmu.h
 * @brief Gestión de la MMU y Tablas de Páginas para Carley Play.
 */

#define TTB_SIZE (16 * 1024) // 16KB para L1 Translation Table

/**
 * @brief Inicializa la MMU con un mapa de memoria 1:1 inicial.
 */
void mmu_init(void);

/**
 * @brief Habilita la protección de memoria para el proceso del juego.
 */
void mmu_protect_game(uint32_t game_addr, uint32_t size);

#endif // MMU_H
