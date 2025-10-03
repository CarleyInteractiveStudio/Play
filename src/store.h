/**
 * @file store.h
 * @brief Declaraciones de funciones para la "Play Store".
 *
 * Gestiona la descarga, el análisis del catálogo de la tienda y la
 * presentación de los elementos disponibles para descargar.
 */

#ifndef STORE_H
#define STORE_H

#include "lvgl/lvgl.h"

// --- DECLARACIONES DE FUNCIONES ---

/**
 * @brief Muestra la pantalla de la tienda.
 *
 * Crea una nueva pantalla que lista los elementos disponibles
 * del catálogo.
 */
void store_show_screen(void);

#endif // STORE_H