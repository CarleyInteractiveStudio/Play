#ifndef PMU_RK_H
#define PMU_RK_H

#include <stdint.h>

/**
 * @file pmu_rk.h
 * @brief Power Management Unit para RK3128.
 */

#define PMU_BASE 0x20004000

/**
 * @brief Entra en modo bajo consumo.
 */
void pmu_enter_sleep(void);

/**
 * @brief Ajusta el brillo de la pantalla (vía PWM o registros de display).
 */
void pmu_set_brightness(uint8_t level);

#endif // PMU_RK_H
