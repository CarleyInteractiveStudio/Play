#include "ui.h"
#include "store.h"
#include "settings.h"
#include "data_manager.h"
#include "input_handler.h"
#include "audio_manager.h"
#include "localization.h"
#include <stdio.h>

extern "C" uint32_t kernel_get_free_ram(void);

// --- CAROUSEL MENU (Estilo PlayStation) ---

static void carousel_event_handler(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_FOCUSED) {
        audio_play_click();
        // Escalar el icono enfocado
        lv_obj_set_style_transform_scale(obj, 300, LV_STATE_FOCUSED); // 1.2x aprox
    } else if(code == LV_EVENT_DEFOCUSED) {
        lv_obj_set_style_transform_scale(obj, 256, LV_PART_MAIN);
    }
}

void ui_create_game_list(lv_obj_t * parent)
{
    // Fondo
    lv_obj_set_style_bg_color(parent, lv_color_hex(0x000020), LV_PART_MAIN);

    // Contenedor del Carrusel
    lv_obj_t * cont = lv_obj_create(parent);
    lv_obj_set_size(cont, lv_pct(100), 300);
    lv_obj_align(cont, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_bg_opa(cont, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(cont, 0, LV_PART_MAIN);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_column(cont, 40, LV_PART_MAIN);

    lv_group_t * g = cp_input_get_group();

    // Obtener aplicaciones
    int count = 0;
    const cp_app_t* apps = data_manager_get_apps(&count);

    for (int i = 0; i < count; i++) {
        if(apps[i].installed) {
            lv_obj_t * btn = lv_btn_create(cont);
            lv_obj_set_size(btn, 180, 180);
            lv_obj_set_style_radius(btn, 20, LV_PART_MAIN);
            lv_obj_set_style_bg_color(btn, lv_color_hex(0x404080), LV_PART_MAIN);
            lv_obj_set_style_bg_color(btn, lv_color_hex(0x0000FF), LV_STATE_FOCUSED);

            lv_obj_t * label = lv_label_create(btn);
            lv_label_set_text(label, apps[i].name);
            lv_obj_center(label);
            lv_obj_set_style_text_font(label, &lv_font_montserrat_14, LV_PART_MAIN);

            lv_group_add_obj(g, btn);
            lv_obj_add_event_cb(btn, carousel_event_handler, LV_EVENT_ALL, NULL);
        }
    }

    // Botones de Sistema
    lv_obj_t * store_btn = lv_btn_create(cont);
    lv_obj_set_size(store_btn, 120, 120);
    lv_obj_set_style_bg_color(store_btn, lv_color_hex(0x008000), LV_PART_MAIN);
    lv_obj_t * store_lbl = lv_label_create(store_btn);
    lv_label_set_text(store_lbl, LV_SYMBOL_DOWNLOAD);
    lv_obj_center(store_lbl);
    lv_group_add_obj(g, store_btn);
    lv_obj_add_event_cb(store_btn, [](lv_event_t * e) { store_show_screen(); }, LV_EVENT_CLICKED, NULL);

    lv_obj_t * sett_btn = lv_btn_create(cont);
    lv_obj_set_size(sett_btn, 120, 120);
    lv_obj_set_style_bg_color(sett_btn, lv_color_hex(0x808080), LV_PART_MAIN);
    lv_obj_t * sett_lbl = lv_label_create(sett_btn);
    lv_label_set_text(sett_lbl, LV_SYMBOL_SETTINGS);
    lv_obj_center(sett_lbl);
    lv_group_add_obj(g, sett_btn);
    lv_obj_add_event_cb(sett_btn, [](lv_event_t * e) { settings_show_screen(); }, LV_EVENT_CLICKED, NULL);

    // Etiqueta de Título arriba
    lv_obj_t * top_label = lv_label_create(parent);
    lv_label_set_text(top_label, lang_str(STR_MY_GAMES));
    lv_obj_set_style_text_font(top_label, &lv_font_montserrat_36, LV_PART_MAIN);
    lv_obj_align(top_label, LV_ALIGN_TOP_MID, 0, 40);

    // Barra de Estado Superior (RAM Real)
    char ram_buf[32];
    uint32_t free_ram = kernel_get_free_ram() / 1024; // KB
    snprintf(ram_buf, sizeof(ram_buf), "RAM: %u KB", (unsigned int)free_ram);

    lv_obj_t * ram_label = lv_label_create(parent);
    lv_label_set_text(ram_label, ram_buf);
    lv_obj_align(ram_label, LV_ALIGN_TOP_RIGHT, -20, 20);
}
