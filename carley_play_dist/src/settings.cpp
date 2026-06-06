#include "settings.h"
#include "ui.h"
#include "app_manager.h"

static void app_manager_event_handler(lv_event_t * e)
{
    app_manager_show_screen();
}

static void back_event_handler(lv_event_t * e)
{
    lv_obj_t * main_screen = lv_obj_create(NULL);
    ui_create_game_list(main_screen);
    lv_scr_load_anim(main_screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, true);
}

void settings_show_screen(void)
{
    lv_obj_t * screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x202020), LV_PART_MAIN);

    lv_obj_t * title = lv_label_create(screen);
    lv_label_set_text(title, "Ajustes de Carley Play");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_28, LV_PART_MAIN);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);

    lv_obj_t * list = lv_list_create(screen);
    lv_obj_set_size(list, 500, 400);
    lv_obj_center(list);

    // Ajuste de Volumen
    lv_list_add_text(list, "Audio");
    lv_obj_t * vol_slider = lv_slider_create(list);
    lv_obj_set_width(vol_slider, 200);
    lv_slider_set_value(vol_slider, 70, LV_ANIM_OFF);

    // Ajuste de Idioma
    lv_list_add_text(list, "Idioma");
    lv_obj_t * roller = lv_roller_create(list);
    lv_roller_set_options(roller, "Español\nEnglish\nPortuguês\nFrançais", LV_ROLLER_MODE_NORMAL);

    // Gestor de Aplicaciones
    lv_list_add_text(list, "Almacenamiento");
    lv_obj_t * btn_mgr = lv_list_add_btn(list, LV_SYMBOL_DIRECTORY, "Gestionar Aplicaciones");
    lv_obj_add_event_cb(btn_mgr, app_manager_event_handler, LV_EVENT_CLICKED, NULL);

    // Información del Sistema
    lv_list_add_text(list, "Sistema");
    lv_list_add_text(list, "Versión: Play OS v1.0 (Bare Metal)");
    lv_list_add_text(list, "Hardware: Carley Play (GB2)");
    lv_list_add_text(list, "RAM: 256MB DDR3");

    // Botón Volver
    lv_obj_t * back_btn = lv_btn_create(screen);
    lv_obj_align(back_btn, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_t * back_label = lv_label_create(back_btn);
    lv_label_set_text(back_label, "Volver");
    lv_obj_add_event_cb(back_btn, back_event_handler, LV_EVENT_CLICKED, NULL);

    lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 300, 0, true);
}
