/**
 * @file splash.cpp
 * @brief Implementación de la pantalla de bienvenida.
 */

#include "splash.h"
#include "localization.h"

/**
 * @brief Muestra la pantalla de bienvenida.
 *
 * Crea una pantalla simple con el nombre del sistema operativo en el centro.
 * Esta pantalla se mostrará durante unos segundos al inicio.
 */
void splash_show_screen(void)
{
    // Crear una nueva pantalla
    lv_obj_t *screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x000010), LV_PART_MAIN); // Un azul aún más oscuro

    // Crear la etiqueta principal "Carley Play"
    lv_obj_t *title_label = lv_label_create(screen);
    lv_label_set_text(title_label, "CP - Carley Play");
    lv_obj_set_style_text_color(title_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_font(title_label, &lv_font_montserrat_36, LV_PART_MAIN);
    lv_obj_align(title_label, LV_ALIGN_CENTER, 0, 0);

    // Animación de entrada para el título
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, title_label);
    lv_anim_set_values(&a, 0, 255);
    lv_anim_set_duration(&a, 1500);
    lv_anim_set_exec_cb(&a, [](void * var, int32_t v) {
        lv_obj_set_style_opa((lv_obj_t *)var, v, LV_PART_MAIN);
    });
    lv_anim_start(&a);

    // Crear una sub-etiqueta
    lv_obj_t *subtitle_label = lv_label_create(screen);
    lv_label_set_text(subtitle_label, lang_str(STR_LOADING));
    lv_obj_set_style_text_color(subtitle_label, lv_color_hex(0xAAAAAA), LV_PART_MAIN);
    lv_obj_set_style_text_font(subtitle_label, &lv_font_montserrat_16, LV_PART_MAIN);
    lv_obj_align(subtitle_label, LV_ALIGN_CENTER, 0, 30);

    // Cargar la pantalla
    lv_disp_load_scr(screen);
}