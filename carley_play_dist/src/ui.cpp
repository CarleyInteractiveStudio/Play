#include "ui.h"
#include "store.h"
#include "settings.h"
#include "data_manager.h"
#include "input_handler.h"
#include "audio_manager.h"

static void store_button_event_handler(lv_event_t * e)
{
    audio_play_click();
    store_show_screen();
}

static void settings_button_event_handler(lv_event_t * e)
{
    audio_play_click();
    settings_show_screen();
}

void ui_create_game_list(lv_obj_t * parent)
{
    lv_obj_t * list = lv_list_create(parent);
    lv_obj_set_size(list, lv_pct(100), lv_pct(100));
    lv_obj_center(list);

    lv_group_add_obj(cp_input_get_group(), list);

    lv_obj_set_style_bg_color(list, lv_color_hex(0x000030), LV_PART_MAIN);
    lv_obj_set_style_border_width(list, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(list, 10, LV_PART_MAIN);

    lv_list_add_text(list, "Carley Play - Mis Juegos");

    int count = 0;
    const cp_app_t* apps = data_manager_get_apps(&count);

    if (count == 0) {
        lv_list_add_text(list, "No hay juegos instalados.");
    } else {
        for (int i = 0; i < count; i++) {
            if(apps[i].installed) {
                lv_obj_t * btn = lv_list_add_btn(list, LV_SYMBOL_PLAY, apps[i].name);
                lv_obj_set_style_bg_color(btn, lv_color_hex(0x000030), LV_PART_MAIN);
                lv_obj_set_style_bg_color(btn, lv_color_hex(0x404080), LV_STATE_FOCUSED);
                lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN);
                lv_obj_set_style_text_color(btn, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
            }
        }
    }

    lv_list_add_text(list, "Sistema");

    lv_obj_t * store_btn = lv_list_add_btn(list, LV_SYMBOL_DOWNLOAD, "Game Store");
    lv_obj_set_style_bg_color(store_btn, lv_color_hex(0x000030), LV_PART_MAIN);
    lv_obj_set_style_bg_color(store_btn, lv_color_hex(0x404080), LV_STATE_FOCUSED);
    lv_obj_set_style_border_width(store_btn, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(store_btn, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_event_cb(store_btn, store_button_event_handler, LV_EVENT_CLICKED, NULL);

    lv_obj_t * settings_btn = lv_list_add_btn(list, LV_SYMBOL_SETTINGS, "Ajustes");
    lv_obj_set_style_bg_color(settings_btn, lv_color_hex(0x000030), LV_PART_MAIN);
    lv_obj_set_style_bg_color(settings_btn, lv_color_hex(0x404080), LV_STATE_FOCUSED);
    lv_obj_set_style_border_width(settings_btn, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(settings_btn, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_event_cb(settings_btn, settings_button_event_handler, LV_EVENT_CLICKED, NULL);
}
