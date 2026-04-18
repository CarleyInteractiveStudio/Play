#include "ui.h"
#include "store.h"
#include "settings.h"
#include "data_manager.h"
#include "input_handler.h"
#include "audio_manager.h"
#include "localization.h"
#include "loader.h"
#include "vpu_rk.h"
#include <stdio.h>

static lv_obj_t * game_info_cont;
static lv_obj_t * game_title_lbl;
static lv_obj_t * game_desc_lbl;
static lv_obj_t * game_icon_img;

static void game_click_event_handler(lv_event_t * e)
{
    lv_obj_t * obj = (lv_obj_t *)lv_event_get_target(e);
    int index = (intptr_t)lv_obj_get_user_data(obj);
    // Cargar juego real desde el sector asignado (ejemplo sector 1000)
    loader_run_game(1000 + (index * 5000), 5000, 0x02000000);
}

static void game_focus_event_handler(lv_event_t * e)
{
    lv_obj_t * btn = (lv_obj_t *)lv_event_get_target(e);
    int index = (intptr_t)lv_obj_get_user_data(btn);

    int count = 0;
    const cp_app_t* apps = data_manager_get_apps(&count);

    if(index < count) {
        audio_play_click();
        lv_label_set_text(game_title_lbl, apps[index].name);
        lv_label_set_text(game_desc_lbl, "Un juego increíble optimizado para Carley Play.");

        // Disparar reproducción de trailer por hardware
        // vpu_decode_frame(apps[index].trailer_data, apps[index].trailer_size, CP_FB_ADDR);
    }
}

void ui_create_game_list(lv_obj_t * parent)
{
    lv_obj_set_style_bg_color(parent, lv_color_hex(0x050505), LV_PART_MAIN);

    // --- PARTE IZQUIERDA: ICONO DEL JUEGO ---
    game_icon_img = lv_obj_create(parent);
    lv_obj_set_size(game_icon_img, 400, 400);
    lv_obj_align(game_icon_img, LV_ALIGN_LEFT_MID, 50, 0);
    lv_obj_set_style_bg_color(game_icon_img, lv_color_hex(0x202020), LV_PART_MAIN);
    lv_obj_set_style_radius(game_icon_img, 30, LV_PART_MAIN);
    lv_obj_set_style_border_color(game_icon_img, lv_color_hex(0x00FF00), LV_PART_MAIN);
    lv_obj_set_style_border_width(game_icon_img, 2, LV_PART_MAIN);

    lv_obj_t * icon_placeholder = lv_label_create(game_icon_img);
    lv_label_set_text(icon_placeholder, LV_SYMBOL_IMAGE);
    lv_obj_set_style_text_font(icon_placeholder, &lv_font_montserrat_48, LV_PART_MAIN);
    lv_obj_center(icon_placeholder);

    // --- PARTE DERECHA: INFORMACIÓN ---
    game_info_cont = lv_obj_create(parent);
    lv_obj_set_size(game_info_cont, 700, 500);
    lv_obj_align(game_info_cont, LV_ALIGN_RIGHT_MID, -50, 0);
    lv_obj_set_style_bg_opa(game_info_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(game_info_cont, 0, LV_PART_MAIN);

    game_title_lbl = lv_label_create(game_info_cont);
    lv_label_set_text(game_title_lbl, "Selecciona un juego");
    lv_obj_set_style_text_font(game_title_lbl, &lv_font_montserrat_48, LV_PART_MAIN);
    lv_obj_align(game_title_lbl, LV_ALIGN_TOP_LEFT, 0, 0);

    game_desc_lbl = lv_label_create(game_info_cont);
    lv_label_set_text(game_desc_lbl, "Usa el mando para navegar por tu catálogo nativo.");
    lv_obj_set_width(game_desc_lbl, 600);
    lv_obj_set_style_text_color(game_desc_lbl, lv_color_hex(0xAAAAAA), LV_PART_MAIN);
    lv_obj_align(game_desc_lbl, LV_ALIGN_TOP_LEFT, 0, 80);

    // Indicación de controles
    lv_obj_t * controls_lbl = lv_label_create(game_info_cont);
    lv_label_set_text(controls_lbl, "A: Iniciar Juego   B: Tienda   S: Ajustes");
    lv_obj_set_style_text_color(controls_lbl, lv_color_hex(0x00FF00), LV_PART_MAIN);
    lv_obj_align(controls_lbl, LV_ALIGN_BOTTOM_LEFT, 0, 0);

    // --- LISTA DE JUEGOS (Abajo) ---
    lv_obj_t * list = lv_obj_create(parent);
    lv_obj_set_size(list, lv_pct(100), 120);
    lv_obj_align(list, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_set_flex_flow(list, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_bg_opa(list, 50, LV_PART_MAIN);
    lv_obj_set_style_border_width(list, 0, LV_PART_MAIN);

    int count = 0;
    const cp_app_t* apps = data_manager_get_apps(&count);
    lv_group_t * g = cp_input_get_group();

    for (int i = 0; i < count; i++) {
        if(apps[i].installed) {
            lv_obj_t * btn = lv_btn_create(list);
            lv_obj_set_size(btn, 100, 80);
            lv_obj_set_user_data(btn, (void*)(intptr_t)i);

            lv_obj_t * lbl = lv_label_create(btn);
            lv_label_set_text(lbl, apps[i].name);
            lv_obj_center(lbl);

            lv_group_add_obj(g, btn);
            lv_obj_add_event_cb(btn, game_focus_event_handler, LV_EVENT_FOCUSED, NULL);
            lv_group_add_obj(g, btn);
            lv_obj_add_event_cb(btn, game_focus_event_handler, LV_EVENT_FOCUSED, NULL);
            lv_obj_add_event_cb(btn, game_click_event_handler, LV_EVENT_CLICKED, NULL);
        }
    }

    // Indicador de Sincronización (Online)
    lv_obj_t * sync_indicator = lv_label_create(parent);
    lv_label_set_text(sync_indicator, LV_SYMBOL_BLUETOOTH " Carley Sync Active");
    lv_obj_set_style_text_color(sync_indicator, lv_color_hex(0x00AAFF), LV_PART_MAIN);
    lv_obj_align(sync_indicator, LV_ALIGN_TOP_LEFT, 20, 20);
}
