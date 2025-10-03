/**
 * @file settings.cpp
 * @brief Implementación de las funciones para la pantalla de Ajustes.
 */

#include "settings.h"

// --- MANEJADORES DE EVENTOS ---

/**
 * @brief Manejador de eventos para el botón "Atrás" de la pantalla de ajustes.
 *
 * Cierra la pantalla actual (ajustes) y vuelve a la anterior (la lista de juegos).
 */
static void settings_back_button_event_handler(lv_event_t *e)
{
    lv_obj_t *screen_to_close = (lv_obj_t *)lv_event_get_user_data(e);
    lv_obj_del_async(screen_to_close); // Elimina la pantalla de forma asíncrona.
}

// --- IMPLEMENTACIÓN DE FUNCIONES ---

/**
 * @brief Muestra la pantalla de ajustes.
 *
 * Crea una nueva pantalla y la puebla con widgets de configuración de ejemplo.
 */
void settings_show_screen(void)
{
    // Crear una nueva pantalla.
    lv_obj_t *screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x000030), LV_PART_MAIN);

    // Crear un título
    lv_obj_t *title = lv_label_create(screen);
    lv_label_set_text(title, "Ajustes");
    lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_22, LV_PART_MAIN);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);

    // Crear un contenedor para los elementos de ajuste
    lv_obj_t *cont = lv_obj_create(screen);
    lv_obj_set_size(cont, lv_pct(95), lv_pct(70));
    lv_obj_align(cont, LV_ALIGN_CENTER, 0, 10);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN); // Organizar elementos en una columna
    lv_obj_set_style_bg_color(cont, lv_color_hex(0x000030), LV_PART_MAIN);
    lv_obj_set_style_border_width(cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(cont, 10, LV_PART_MAIN);

    // --- Opción 1: Idioma (Dropdown) ---
    lv_obj_t *lang_label = lv_label_create(cont);
    lv_label_set_text(lang_label, "Idioma");
    lv_obj_set_style_text_color(lang_label, lv_color_hex(0xCCCCCC), LV_PART_MAIN);

    lv_obj_t *lang_dd = lv_dropdown_create(cont);
    lv_dropdown_set_options(lang_dd, "Espanol\nIngles\nPortugues");
    lv_obj_set_width(lang_dd, lv_pct(90));

    // --- Opción 2: Sonido (Switch) ---
    lv_obj_t *sound_label = lv_label_create(cont);
    lv_label_set_text(sound_label, "Sonido");
    lv_obj_set_style_text_color(sound_label, lv_color_hex(0xCCCCCC), LV_PART_MAIN);
    lv_obj_set_style_pad_top(sound_label, 15, LV_PART_MAIN);

    lv_obj_t *sound_switch = lv_switch_create(cont);

    // Crear un botón de "Atrás"
    lv_obj_t *back_btn = lv_btn_create(screen);
    lv_obj_align(back_btn, LV_ALIGN_BOTTOM_LEFT, 10, -10);
    lv_obj_add_event_cb(back_btn, settings_back_button_event_handler, LV_EVENT_CLICKED, screen);

    lv_obj_t *back_label = lv_label_create(back_btn);
    lv_label_set_text(back_label, "Atras");
    lv_obj_center(back_label);

    // Cargar la nueva pantalla
    lv_disp_load_scr(screen);
}