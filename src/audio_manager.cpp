#include "audio_manager.h"
#include <stdint.h>

// --- SONIDO DE CLICK EMBEBIDO (8-bit PCM, 8000Hz, 0.1s) ---
// Pequeño pulso sonoro para la interfaz.
static const uint8_t click_sfx[] = {
    128, 140, 160, 180, 200, 220, 240, 255, 240, 220, 200, 180, 160, 140, 128,
    110, 90, 70, 50, 30, 15, 0, 15, 30, 50, 70, 90, 110, 128
};

// --- REGISTROS DE AUDIO (GB2) ---
#define AUDIO_BASE 0x1012A000
#define AUDIO_DATA 0x0004

static int current_volume = 70;

#define I2S_BASE 0x10200000
#define I2S_TX_CTRL (I2S_BASE + 0x0004)

void audio_init(void)
{
    // Configurar I2S para HDMI
    RK_REG(CRU_CLKGATE_CON(1)) &= ~(1 << 5); // Habilitar reloj I2S
    RK_REG(I2S_TX_CTRL) = 0x03; // Habilitar transmisión
}

void audio_play_click(void)
{
    // Enviar el array click_sfx al hardware de audio
    for(int i = 0; i < sizeof(click_sfx); i++) {
        // En un sistema real, esperaríamos a que el buffer I2S esté vacío
        // AUDIO_REG(AUDIO_DATA) = click_sfx[i];
    }
}

void audio_set_volume(int volume)
{
    current_volume = volume;
}
