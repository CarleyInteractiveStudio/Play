/**
 * @file app_manager.h
 * @brief Declaraciones de funciones para el Gestor de Aplicaciones.
 *
 * Gestiona la creación y visualización de la pantalla que permite
 * ver el almacenamiento y desinstalar aplicaciones.
 */

#ifndef APP_MANAGER_H
#define APP_MANAGER_H

#include "lvgl/lvgl.h"

// --- DECLARACIONES DE FUNCIONES ---

/**
 * @brief Muestra la pantalla del gestor de aplicaciones.
 *
 * Crea una nueva pantalla que lista las aplicaciones instaladas
 * y muestra el uso de almacenamiento simulado.
 */
void app_manager_show_screen(void);

#endif // APP_MANAGER_H