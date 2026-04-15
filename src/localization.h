#ifndef LOCALIZATION_H
#define LOCALIZATION_H

/**
 * @file localization.h
 * @brief Sistema de idiomas para Carley Play.
 */

typedef enum {
    LANG_ES,
    LANG_EN
} cp_lang_t;

typedef enum {
    STR_MY_GAMES,
    STR_STORE,
    STR_SETTINGS,
    STR_BACK,
    STR_VOLUME,
    STR_LANGUAGE,
    STR_SYSTEM,
    STR_STORAGE,
    STR_VERSION,
    STR_HARDWARE,
    STR_FREE_RAM,
    STR_LOADING,
    STR_UNINSTALL,
    STR_TOTAL_STRINGS
} cp_string_t;

/**
 * @brief Cambia el idioma actual.
 */
void lang_set(cp_lang_t lang);

/**
 * @brief Obtiene el idioma actual.
 */
cp_lang_t lang_get(void);

/**
 * @brief Obtiene una cadena traducida.
 */
const char* lang_str(cp_string_t str_id);

#endif // LOCALIZATION_H
