/**
 * @file app_manager.cpp
 * @brief Implementación de las funciones para el Gestor de Aplicaciones.
 *
 * Esta versión implementa una lógica de desinstalación real que interactúa
 * con el data_manager para eliminar aplicaciones y guardar los cambios
 * en el archivo catalog.json.
 */

#include "app_manager.h"
#include "data_manager.h" // Incluimos el gestor de datos para la lógica real.

// --- VARIABLES GLOBALES AL ARCHIVO ---
static lv_obj_t *storage_bar;
static lv_obj_t *storage_label;
static const float TOTAL_STORAGE_GB = 32.0f;

// --- DECLARACIONES DE FUNCIONES INTERNAS ---
static void update_storage_display();

// --- MANEJADORES DE EVENTOS ---

/**
 * @brief Manejador de eventos para el botón "Atrás".
 */
static void back_button_event_handler(lv_event_t *e)
{
    lv_obj_t *screen_to_close = (lv_obj_t *)lv_event_get_user_data(e);
    lv_obj_del_async(screen_to_close);
}

/**
 * @brief Manejador de eventos para el diálogo de confirmación de desinstalación.
 */
static void uninstall_confirm_event_handler(lv_event_t *e)
{
    lv_obj_t *mbox = lv_event_get_current_target(e);
    const char *btn_text = lv_msgbox_get_active_btn_text(mbox);

    if (btn_text != NULL && strcmp(btn_text, "Desinstalar") == 0) {
        lv_obj_t *list_item_to_delete = (lv_obj_t *)lv_event_get_user_data(e);
        int index = lv_list_get_btn_index(lv_obj_get_parent(list_item_to_delete), list_item_to_delete);

        // Lógica de desinstalación real:
        // 1. Eliminar de la estructura de datos en memoria.
        data_manager_delete_app(index);
        // 2. Guardar los cambios en el archivo catalog.json.
        data_manager_save_data();

        // 3. Actualizar la UI
        lv_obj_del(list_item_to_delete);
        update_storage_display();
    }

    lv_msgbox_close(mbox);
}

/**
 * @brief Manejador de eventos para cuando se hace clic en un elemento de la lista de apps.
 */
static void app_list_item_event_handler(lv_event_t *e)
{
    lv_obj_t *list_item = lv_event_get_target(e);
    lv_obj_t *list = lv_obj_get_parent(list_item);
    int index = lv_list_get_btn_index(list, list_item);

    const auto& apps = data_manager_get_apps();
    if (index < 0 || index >= apps.size()) return; // Safety check

    const char *app_name = apps[index].name.c_str();

    static const char *btns[] = {"Desinstalar", "Cancelar", ""};
    char msg[128];
    snprintf(msg, sizeof(msg), "¿Deseas desinstalar\n%s?", app_name);

    lv_obj_t *mbox = lv_msgbox_create(NULL, "Confirmar", msg, btns, true);
    lv_obj_add_event_cb(mbox, uninstall_confirm_event_handler, LV_EVENT_VALUE_CHANGED, list_item);
    lv_obj_center(mbox);
}

// --- IMPLEMENTACIÓN DE FUNCIONES ---

/**
 * @brief Actualiza la barra y la etiqueta de almacenamiento basándose en los datos reales.
 */
static void update_storage_display() {
    float used_mb = 0.0f;
    const auto& apps = data_manager_get_apps();
    for(const auto& app : apps) {
        used_mb += app.size_mb;
    }

    float used_gb = used_mb / 1024.0f;
    int percent_used = (int)((used_gb / TOTAL_STORAGE_GB) * 100.0f);
    lv_bar_set_value(storage_bar, percent_used, LV_ANIM_ON);

    char buf[64];
    snprintf(buf, sizeof(buf), "Almacenamiento: %.2f / %.1f GB", used_gb, TOTAL_STORAGE_GB);
    lv_label_set_text(storage_label, buf);
}

/**
 * @brief Muestra la pantalla del gestor de aplicaciones.
 */
void app_manager_show_screen(void)
{
    lv_obj_t *screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x000030), LV_PART_MAIN);

    lv_obj_t *title = lv_label_create(screen);
    lv_label_set_text(title, "Gestionar Aplicaciones");
    lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_22, LV_PART_MAIN);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);

    storage_label = lv_label_create(screen);
    lv_obj_set_style_text_color(storage_label, lv_color_hex(0xCCCCCC), LV_PART_MAIN);
    lv_obj_align(storage_label, LV_ALIGN_TOP_LEFT, 15, 45);

    storage_bar = lv_bar_create(screen);
    lv_obj_set_size(storage_bar, lv_pct(90), 20);
    lv_obj_align(storage_bar, LV_ALIGN_TOP_MID, 0, 70);

    lv_obj_t *list = lv_list_create(screen);
    lv_obj_set_size(list, lv_pct(95), lv_pct(60));
    lv_obj_align(list, LV_ALIGN_TOP_MID, 0, 110);
    lv_obj_set_style_bg_color(list, lv_color_hex(0x000030), LV_PART_MAIN);
    lv_obj_set_style_border_width(list, 0, LV_PART_MAIN);

    const auto& apps = data_manager_get_apps();
    for (const auto& app : apps) {
        char buf[256];
        snprintf(buf, sizeof(buf), "%s (%.1f MB)", app.name.c_str(), app.size_mb);
        lv_obj_t *btn = lv_list_add_btn(list, LV_SYMBOL_TRASH, buf);
        lv_obj_add_event_cb(btn, app_list_item_event_handler, LV_EVENT_CLICKED, NULL);
    }

    update_storage_display();

    lv_obj_t *back_btn = lv_btn_create(screen);
    lv_obj_align(back_btn, LV_ALIGN_BOTTOM_LEFT, 10, -10);
    lv_obj_add_event_cb(back_btn, back_button_event_handler, LV_EVENT_CLICKED, screen);

    lv_obj_t *back_label = lv_label_create(back_btn);
    lv_label_set_text(back_label, "Atras");
    lv_obj_center(back_label);

    lv_disp_load_scr(screen);
}