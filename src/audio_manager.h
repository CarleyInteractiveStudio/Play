#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

/**
 * @file audio_manager.h
 * @brief Gestión de audio para Bare Metal en Carley Play.
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Inicializa el hardware de sonido.
 */
void audio_init(void);

/**
 * @brief Reproduce un efecto de sonido corto (ej: click).
 */
void audio_play_click(void);

/**
 * @brief Cambia el volumen general (0-100).
 */
void audio_set_volume(int volume);

#ifdef __cplusplus
}
#endif

#endif // AUDIO_MANAGER_H
