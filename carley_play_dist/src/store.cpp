#include "store.h"
#include "data_manager.h"
#include "ui.h"

void store_show_screen(void)
{
    lv_obj_t * screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x002000), LV_PART_MAIN);

    lv_obj_t * title = lv_label_create(screen);
    lv_label_set_text(title, "Game Store");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_28, LV_PART_MAIN);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);

    lv_obj_t * list = lv_list_create(screen);
    lv_obj_set_size(list, 600, 400);
    lv_obj_center(list);

    int count = 0;
    const cp_app_t* apps = data_manager_get_apps(&count);

    for (int i = 0; i < count; i++) {
        lv_list_add_btn(list, LV_SYMBOL_PLUS, apps[i].name);
    }

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
