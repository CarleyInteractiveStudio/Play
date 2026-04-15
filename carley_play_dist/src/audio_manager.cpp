#include "audio_manager.h"
#include <stdint.h>

// --- REGISTROS DE AUDIO (Simulados para GB2) ---
#define AUDIO_BASE 0x1012A000
#define AUDIO_REG(offset) (*(volatile uint32_t *)(AUDIO_BASE + offset))

static int current_volume = 70;

void audio_init(void)
{
    // TODO: Inicializar I2S o Codec de audio del GB2
}

void audio_play_click(void)
{
    // En Bare Metal sin sistema de archivos, los sonidos serían
    // pequeños arrays de muestras PCM.
}

void audio_set_volume(int volume)
{
    current_volume = volume;
    // Aplicar al hardware...
}
