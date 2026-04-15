#include "file_explorer.h"
#include "lvgl/lvgl.h"
#include "ui.h"
#include "fat32.h"
#include "localization.h"

static void back_event_handler(lv_event_t * e)
{
    lv_obj_t * main_screen = lv_obj_create(NULL);
    ui_create_game_list(main_screen);
    lv_scr_load_anim(main_screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, true);
}

void file_explorer_show(void)
{
    lv_obj_t * screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x101010), LV_PART_MAIN);

    lv_obj_t * title = lv_label_create(screen);
    lv_label_set_text(title, "SD Card Explorer");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_28, LV_PART_MAIN);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);

    lv_obj_t * list = lv_list_create(screen);
    lv_obj_set_size(list, 600, 400);
    lv_obj_center(list);

    // Listar archivos del directorio raíz (Ejemplo estático por ahora)
    lv_list_add_btn(list, LV_SYMBOL_FILE, "catalog.json");
    lv_list_add_btn(list, LV_SYMBOL_DIRECTORY, "roms/");
    lv_list_add_btn(list, LV_SYMBOL_DIRECTORY, "system/");

    lv_obj_t * back_btn = lv_btn_create(screen);
    lv_obj_align(back_btn, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_t * back_lbl = lv_label_create(back_btn);
    lv_label_set_text(back_lbl, lang_str(STR_BACK));
    lv_obj_add_event_cb(back_btn, back_event_handler, LV_EVENT_CLICKED, NULL);

    lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 300, 0, true);
}
