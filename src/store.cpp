/**
 * @file store.cpp
 * @brief Implementación de las funciones de la "Play Store".
 *
 * Esta versión corregida implementa un lector de JSON básico para
 * procesar el archivo `catalog.json` y mostrar su contenido real.
 *
 * NOTA: La funcionalidad de descarga no está implementada. Al hacer
 * clic en un elemento de la tienda, no ocurrirá nada.
 */

#include "store.h"
#include "ui.h" // Necesitamos acceso a la UI para volver a ella.
#include "cJSON.h" // Incluimos la biblioteca cJSON para analizar el catálogo.
#include <fstream>
#include <string>
#include <sstream>

// --- MANEJADORES DE EVENTOS ---

/**
 * @brief Manejador de eventos para el botón "Atrás".
 *
 * Cierra la pantalla actual (la tienda) y vuelve a la anterior (la lista de juegos).
 */
static void back_button_event_handler(lv_event_t *e)
{
    lv_obj_t *screen_to_close = (lv_obj_t *)lv_event_get_user_data(e);
    lv_obj_del_async(screen_to_close); // Elimina la pantalla de forma asíncrona para evitar fallos.
}

/**
 * @brief Lee el contenido del catálogo desde el archivo `catalog.json`.
 *
 * @return std::string con el contenido del archivo, o una cadena vacía si falla.
 */
static std::string read_catalog_file() {
    std::ifstream file("catalog.json");
    if (!file.is_open()) {
        return ""; // Falla si no se puede abrir el archivo.
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

/**
 * @brief Analiza el contenido JSON del catálogo y puebla la lista de la tienda.
 *
 * @param list El objeto de lista de LVGL que se va a poblar.
 * @param json_string El contenido del archivo catalog.json.
 */
static void parse_and_populate_store(lv_obj_t *list, const std::string& json_string) {
    cJSON *root = cJSON_Parse(json_string.c_str());
    if (root == NULL) {
        lv_list_add_text(list, "Error al leer el catalogo");
        return;
    }

    cJSON *items = cJSON_GetObjectItemCaseSensitive(root, "items");
    cJSON *item = NULL;

    cJSON_ArrayForEach(item, items) {
        cJSON *name = cJSON_GetObjectItemCaseSensitive(item, "name");
        if (cJSON_IsString(name) && (name->valuestring != NULL)) {
            lv_obj_t *btn = lv_list_add_btn(list, LV_SYMBOL_DOWNLOAD, name->valuestring);
            lv_obj_set_style_bg_color(btn, lv_color_hex(0x000030), LV_PART_MAIN);
            lv_obj_set_style_bg_color(btn, lv_color_hex(0x404080), LV_STATE_FOCUSED);
            lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN);
            lv_obj_set_style_text_color(btn, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
        }
    }

    cJSON_Delete(root);
}


// --- IMPLEMENTACIÓN DE FUNCIONES ---

/**
 * @brief Muestra la pantalla de la tienda.
 *
 * Crea una nueva pantalla y la puebla con los elementos del catálogo.
 * También añade un botón para volver a la lista de juegos.
 */
void store_show_screen(void)
{
    // Crear una nueva pantalla. No se asigna padre para que sea una pantalla completa.
    lv_obj_t *screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x000030), LV_PART_MAIN);

    // Crear un título
    lv_obj_t *label = lv_label_create(screen);
    lv_label_set_text(label, "Play Store");
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_22, LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 10);

    // Crear la lista de elementos descargables
    lv_obj_t *list = lv_list_create(screen);
    lv_obj_set_size(list, lv_pct(95), lv_pct(70));
    lv_obj_align(list, LV_ALIGN_CENTER, 0, 10);
    lv_obj_set_style_bg_color(list, lv_color_hex(0x000030), LV_PART_MAIN);
    lv_obj_set_style_border_width(list, 0, LV_PART_MAIN);

    // Leer, analizar y poblar la tienda desde el archivo JSON
    std::string catalog_content = read_catalog_file();
    if (catalog_content.empty()) {
        lv_list_add_text(list, "No se pudo encontrar catalog.json");
    } else {
        parse_and_populate_store(list, catalog_content);
    }

    // Crear un botón de "Atrás"
    lv_obj_t *back_btn = lv_btn_create(screen);
    lv_obj_align(back_btn, LV_ALIGN_BOTTOM_LEFT, 10, -10);
    // Pasamos la pantalla actual como dato de usuario para poder cerrarla.
    lv_obj_add_event_cb(back_btn, back_button_event_handler, LV_EVENT_CLICKED, screen);

    lv_obj_t *back_label = lv_label_create(back_btn);
    lv_label_set_text(back_label, "Atras");
    lv_obj_center(back_label);

    // Cargar la nueva pantalla
    lv_disp_load_scr(screen);
}