#ifndef CARLEY_BRIDGE_H
#define CARLEY_BRIDGE_H

#include <stdint.h>

/**
 * @file carley_bridge.h
 * @brief Comunicación inalámbrica a través del dongle USB (WiFi/BT Bridge).
 */

/**
 * @brief Inicializa el puente de comunicación.
 */
void bridge_init(void);

/**
 * @brief Envía datos al PC/Celular conectado.
 */
void bridge_send(const uint8_t * data, uint32_t size);

/**
 * @brief Recibe datos del exterior.
 */
uint32_t bridge_receive(uint8_t * buffer, uint32_t max_size);

#endif // CARLEY_BRIDGE_H
