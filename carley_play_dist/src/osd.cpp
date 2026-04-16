#include "osd.h"
#include "ui.h"

static lv_obj_t * osd_layer = NULL;
static bool visible = false;

void osd_init(void)
{
    osd_layer = lv_obj_create(lv_layer_top());
    lv_obj_set_size(osd_layer, 400, lv_pct(100));
    lv_obj_align(osd_layer, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_set_style_bg_color(osd_layer, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(osd_layer, 200, LV_PART_MAIN);
    lv_obj_add_flag(osd_layer, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * title = lv_label_create(osd_layer);
    lv_label_set_text(title, "Menú de Sistema");
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);

    lv_obj_t * btn_exit = lv_btn_create(osd_layer);
    lv_obj_align(btn_exit, LV_ALIGN_CENTER, 0, 0);
    lv_obj_t * lbl_exit = lv_label_create(btn_exit);
    lv_label_set_text(lbl_exit, "Salir al Dashboard");

    lv_obj_add_event_cb(btn_exit, [](lv_event_t * e) {
        osd_toggle();
        // Lógica de retorno al menú principal
    }, LV_EVENT_CLICKED, NULL);
}

void osd_toggle(void)
{
    visible = !visible;
    if(visible) lv_obj_clear_flag(osd_layer, LV_OBJ_FLAG_HIDDEN);
    else lv_obj_add_flag(osd_layer, LV_OBJ_FLAG_HIDDEN);
}
