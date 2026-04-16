#include "audio_mixer.h"
#include <string.h>

static audio_channel_t channels[MAX_CHANNELS];

void mixer_init(void)
{
    memset(channels, 0, sizeof(channels));
}

int mixer_play(const uint8_t * data, uint32_t size, bool loop)
{
    for(int i = 0; i < MAX_CHANNELS; i++) {
        if(!channels[i].active) {
            channels[i].data = data;
            channels[i].size = size;
            channels[i].pos = 0;
            channels[i].volume = 128;
            channels[i].active = true;
            channels[i].loop = loop;
            return i;
        }
    }
    return -1;
}

int16_t mixer_process(void)
{
    int32_t mixed = 0;

    for(int i = 0; i < MAX_CHANNELS; i++) {
        if(channels[i].active) {
            int16_t sample = (int16_t)((channels[i].data[channels[i].pos] - 128) << 8);
            mixed += (sample * channels[i].volume) >> 8;

            channels[i].pos++;
            if(channels[i].pos >= channels[i].size) {
                if(channels[i].loop) channels[i].pos = 0;
                else channels[i].active = false;
            }
        }
    }

    // Hard clipping
    if(mixed > 32767) mixed = 32767;
    if(mixed < -32768) mixed = -32768;

    return (int16_t)mixed;
}
