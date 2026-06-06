#ifndef CREATIVE_BRIDGE_H
#define CREATIVE_BRIDGE_H

#include "cp_sdk.h"

/**
 * @file creative_bridge.h
 * @brief Capa de compatibilidad para el motor 'Creative Engine'.
 *
 * Facilita la integración de juegos hechos con tu motor propio.
 */

typedef struct {
    void (*on_start)(void);
    void (*on_update)(float dt);
    void (*on_render)(void);
} creative_engine_t;

/**
 * @brief Registra el motor y arranca el ciclo de juego.
 */
void creative_run(creative_engine_t * engine);

#endif // CREATIVE_BRIDGE_H
