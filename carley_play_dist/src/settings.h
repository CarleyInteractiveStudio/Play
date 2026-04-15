/**
 * @file settings.h
 * @brief Declaraciones de funciones para la pantalla de Ajustes.
 *
 * Gestiona la creación y visualización de la pantalla de ajustes
 * y sus componentes.
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#include "lvgl/lvgl.h"

// --- DECLARACIONES DE FUNCIONES ---

/**
 * @brief Muestra la pantalla de ajustes.
 *
 * Crea una nueva pantalla que lista las opciones de configuración
 * disponibles en el sistema.
 */
void settings_show_screen(void);

#endif // SETTINGS_H