/**
 * @file ui.cpp
 * @brief Implementación de las funciones de la interfaz de usuario para "Play OS".
 */

#include "ui.h"
#include "store.h" // Incluimos la tienda para poder llamarla.
#include "settings.h" // Incluimos los ajustes para poder llamarlos.
#include "data_manager.h" // Incluimos el gestor de datos.

// --- MANEJADORES DE EVENTOS ---

/**
 * @brief Manejador de eventos para el botón de la tienda.
 *
 * Llama a la función que muestra la pantalla de la tienda.
 */
static void store_button_event_handler(lv_event_t *e)
{
    store_show_screen();
}

/**
 * @brief Manejador de eventos para el botón de ajustes.
 *
 * Llama a la función que muestra la pantalla de ajustes.
 */
static void settings_button_event_handler(lv_event_t *e)
{
    settings_show_screen();
}

// --- IMPLEMENTACIÓN DE FUNCIONES ---

/**
 * @brief Crea la vista principal que muestra la lista de juegos.
 *
 * Esta función crea un objeto de lista de LVGL y lo puebla con los
 * datos reales del data_manager.
 */
void ui_create_game_list(lv_obj_t *parent)
{
    // Crear un objeto de lista
    lv_obj_t *list = lv_list_create(parent);
    lv_obj_set_size(list, lv_pct(100), lv_pct(100)); // Ocupar toda la pantalla
    lv_obj_center(list);

    // Estilo de la lista
    lv_obj_set_style_bg_color(list, lv_color_hex(0x000030), LV_PART_MAIN);
    lv_obj_set_style_border_width(list, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(list, 10, LV_PART_MAIN);

    // Añadir un título a la lista de juegos
    lv_list_add_text(list, "Juegos");

    // Obtener los datos reales y poblar la lista
    const auto& apps = data_manager_get_apps();
    if (apps.empty()) {
        lv_list_add_text(list, "No hay juegos instalados.");
    } else {
        for (const auto& app : apps) {
            lv_obj_t *btn = lv_list_add_btn(list, LV_SYMBOL_PLAY, app.name.c_str());

            // Estilo de los botones de la lista
            lv_obj_set_style_bg_color(btn, lv_color_hex(0x000030), LV_PART_MAIN);
            lv_obj_set_style_bg_color(btn, lv_color_hex(0x404080), LV_STATE_FOCUSED); // Color de resaltado al seleccionar
            lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN);
            lv_obj_set_style_text_color(btn, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
        }
    }

    // Añadir un separador y los botones de sistema
    lv_list_add_text(list, "Sistema");

    // Botón de la Tienda
    lv_obj_t *store_btn = lv_list_add_btn(list, LV_SYMBOL_DOWNLOAD, "Game Store");
    lv_obj_set_style_bg_color(store_btn, lv_color_hex(0x000030), LV_PART_MAIN);
    lv_obj_set_style_bg_color(store_btn, lv_color_hex(0x404080), LV_STATE_FOCUSED);
    lv_obj_set_style_border_width(store_btn, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(store_btn, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_event_cb(store_btn, store_button_event_handler, LV_EVENT_CLICKED, NULL);

    // Botón de Ajustes
    lv_obj_t *settings_btn = lv_list_add_btn(list, LV_SYMBOL_SETTINGS, "Ajustes");
    lv_obj_set_style_bg_color(settings_btn, lv_color_hex(0x000030), LV_PART_MAIN);
    lv_obj_set_style_bg_color(settings_btn, lv_color_hex(0x404080), LV_STATE_FOCUSED);
    lv_obj_set_style_border_width(settings_btn, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(settings_btn, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_event_cb(settings_btn, settings_button_event_handler, LV_EVENT_CLICKED, NULL);
}