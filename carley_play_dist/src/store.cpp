/**
 * @file store.cpp
 * @brief Implementación de las funciones de la "Game Store".
 *
 * Esta versión refactorizada obtiene los datos de las aplicaciones
 * directamente desde el data_manager, en lugar de leer el archivo
 * por su cuenta.
 */

#include "store.h"
#include "data_manager.h" // Incluimos el gestor de datos.

// --- MANEJADORES DE EVENTOS ---

/**
 * @brief Manejador de eventos para el botón "Atrás".
 */
static void back_button_event_handler(lv_event_t *e)
{
    lv_obj_t *screen_to_close = (lv_obj_t *)lv_event_get_user_data(e);
    lv_obj_del_async(screen_to_close);
}

// --- IMPLEMENTACIÓN DE FUNCIONES ---

/**
 * @brief Muestra la pantalla de la tienda.
 *
 * Crea una nueva pantalla y la puebla con los elementos del catálogo
 * obtenidos desde el data_manager.
 */
void store_show_screen(void)
{
    lv_obj_t *screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x000030), LV_PART_MAIN);

    lv_obj_t *label = lv_label_create(screen);
    lv_label_set_text(label, "Game Store");
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_22, LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 10);

    lv_obj_t *list = lv_list_create(screen);
    lv_obj_set_size(list, lv_pct(95), lv_pct(70));
    lv_obj_align(list, LV_ALIGN_CENTER, 0, 10);
    lv_obj_set_style_bg_color(list, lv_color_hex(0x000030), LV_PART_MAIN);
    lv_obj_set_style_border_width(list, 0, LV_PART_MAIN);

    // Poblar la lista desde el data_manager
    const auto& apps = data_manager_get_apps();
    if (apps.empty()) {
        lv_list_add_text(list, "La tienda esta vacia.");
    } else {
        for (const auto& app : apps) {
            lv_obj_t *btn = lv_list_add_btn(list, LV_SYMBOL_DOWNLOAD, app.name.c_str());
            lv_obj_set_style_bg_color(btn, lv_color_hex(0x000030), LV_PART_MAIN);
            lv_obj_set_style_bg_color(btn, lv_color_hex(0x404080), LV_STATE_FOCUSED);
            lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN);
            lv_obj_set_style_text_color(btn, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
        }
    }

    lv_obj_t *back_btn = lv_btn_create(screen);
    lv_obj_align(back_btn, LV_ALIGN_BOTTOM_LEFT, 10, -10);
    // Pasamos la pantalla actual como dato de usuario para poder cerrarla.
    lv_obj_add_event_cb(back_btn, back_button_event_handler, LV_EVENT_CLICKED, screen);

    lv_obj_t *back_label = lv_label_create(back_btn);
    lv_label_set_text(back_label, "Atras");
    lv_obj_center(back_label);

    // Cargar la nueva pantalla
    lv_disp_load_scr(screen);
}