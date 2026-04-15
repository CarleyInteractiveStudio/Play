#include "localization.h"

static cp_lang_t current_lang = LANG_ES;

static const char* strings_es[STR_TOTAL_STRINGS] = {
    "Mis Juegos",
    "Tienda",
    "Ajustes",
    "Volver",
    "Volumen",
    "Idioma",
    "Sistema",
    "Almacenamiento",
    "Versión",
    "Hardware",
    "RAM Libre",
    "Cargando...",
    "Desinstalar"
};

static const char* strings_en[STR_TOTAL_STRINGS] = {
    "My Games",
    "Game Store",
    "Settings",
    "Back",
    "Volume",
    "Language",
    "System",
    "Storage",
    "Version",
    "Hardware",
    "Free RAM",
    "Loading...",
    "Uninstall"
};

void lang_set(cp_lang_t lang) {
    current_lang = lang;
}

cp_lang_t lang_get(void) {
    return current_lang;
}

const char* lang_str(cp_string_t str_id) {
    if (current_lang == LANG_EN) return strings_en[str_id];
    return strings_es[str_id];
}
