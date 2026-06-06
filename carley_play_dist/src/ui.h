/**
 * @file ui.h
 * @brief Declaraciones de funciones para crear y gestionar los componentes de la UI de "Play OS".
 */

#ifndef UI_H
#define UI_H

#include "lvgl/lvgl.h"

// --- DECLARACIONES DE FUNCIONES ---

/**
 * @brief Crea la vista principal que muestra la lista de juegos.
 *
 * @param parent El objeto padre sobre el que se creará la lista (normalmente, la pantalla principal).
 */
void ui_create_game_list(lv_obj_t *parent);

#endif // UI_H