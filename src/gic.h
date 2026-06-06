#ifndef GIC_H
#define GIC_H

#include <stdint.h>

/**
 * @file gic.h
 * @brief Controlador de Interrupciones (GIC) para Carley Play (ARM).
 */

#define GIC_DIST_BASE 0x10139000
#define GIC_CPU_BASE  0x10138000

/**
 * @brief Inicializa el GIC.
 */
void gic_init(void);

/**
 * @brief Habilita una interrupción específica.
 */
void gic_enable_interrupt(uint32_t irq);

#endif // GIC_H
