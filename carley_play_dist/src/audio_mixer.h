#ifndef AUDIO_MIXER_H
#define AUDIO_MIXER_H

#include <stdint.h>

/**
 * @file audio_mixer.h
 * @brief Mezclador de audio multicanal para Carley Play.
 */

#define MAX_CHANNELS 4

typedef struct {
    const uint8_t * data;
    uint32_t size;
    uint32_t pos;
    uint8_t volume;
    bool active;
    bool loop;
} audio_channel_t;

/**
 * @brief Inicializa el mezclador.
 */
void mixer_init(void);

/**
 * @brief Añade un sonido a un canal libre.
 */
int mixer_play(const uint8_t * data, uint32_t size, bool loop);

/**
 * @brief Decodifica y reproduce una pista MP3.
 */
void mixer_play_mp3(const uint8_t * mp3_data, uint32_t size);

/**
 * @brief Procesa y mezcla el audio de todos los canales.
 * @return Muestra mezclada de 16 bits.
 */
int16_t mixer_process(void);

#endif // AUDIO_MIXER_H
