#include "app_manager.h"
#include "data_manager.h"
#include "ui.h"
#include <stdio.h>

void app_manager_show_screen(void)
{
    lv_obj_t * screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x101010), LV_PART_MAIN);

    lv_obj_t * title = lv_label_create(screen);
    lv_label_set_text(title, "Gestor de Aplicaciones");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);

    int used = data_manager_get_used_storage();
    char buf[64];
    snprintf(buf, sizeof(buf), "Espacio Usado: %d MB / 64000 MB", used);

    lv_obj_t * storage_info = lv_label_create(screen);
    lv_label_set_text(storage_info, buf);
    lv_obj_align(storage_info, LV_ALIGN_TOP_MID, 0, 60);

    lv_obj_t * bar = lv_bar_create(screen);
    lv_obj_set_size(bar, 400, 20);
    lv_obj_align(bar, LV_ALIGN_TOP_MID, 0, 90);
    lv_bar_set_range(bar, 0, 64000);
    lv_bar_set_value(bar, used, LV_ANIM_OFF);

    lv_obj_t * info = lv_label_create(screen);
    lv_label_set_text(info, "En Bare Metal, la desinstalación es solo temporal.");
    lv_obj_align(info, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t * back_btn = lv_btn_create(screen);
    lv_obj_align(back_btn, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_t * back_label = lv_label_create(back_btn);
    lv_label_set_text(back_label, "Volver");

    lv_obj_add_event_cb(back_btn, [](lv_event_t * e) {
        lv_obj_t * main_screen = lv_obj_create(NULL);
        ui_create_game_list(main_screen);
        lv_scr_load_anim(main_screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, true);
    }, LV_EVENT_CLICKED, NULL);

    lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 300, 0, true);
}
