#ifndef CP_SDK_H
#define CP_SDK_H

#include <stdint.h>

/**
 * @file cp_sdk.h
 * @brief Software Development Kit (SDK) para juegos nativos en Carley Play.
 *
 * Usa estas funciones para interactuar con el hardware de la consola.
 */

// --- VIDEO ---
#define CP_FB_WIDTH  1280
#define CP_FB_HEIGHT 720
#define CP_FB_ADDR   0x01000000

static inline void cp_draw_pixel(int x, int y, uint32_t color) {
    if(x >= 0 && x < CP_FB_WIDTH && y >= 0 && y < CP_FB_HEIGHT) {
        ((uint32_t*)CP_FB_ADDR)[y * CP_FB_WIDTH + x] = color;
    }
}

// --- INPUT ---
typedef struct {
    uint8_t up, down, left, right;
    uint8_t a, b, x, y;
    uint8_t start, select;
} cp_input_t;

void cp_get_input(cp_input_t * input);

// --- AUDIO ---
void cp_play_pcm(const uint8_t * data, uint32_t size);

// --- PERSISTENCE ---
int cp_save_data(const char* key, const void* data, uint32_t size);
int cp_load_data(const char* key, void* data, uint32_t size);

// --- 3D GPU ENGINE (Mali-400) ---
typedef struct {
    float x, y, z;
    float u, v;
    uint32_t color;
} cp_vertex_t;

typedef struct {
    uint8_t * data;
    uint32_t width;
    uint32_t height;
    uint8_t format;
} cp_texture_t;

void cp_gpu_draw_mesh(cp_vertex_t * vertices, uint32_t count, cp_texture_t * tex);
void cp_gpu_set_matrix(float * matrix); // 4x4 matrix

// --- SHADERS (Mali-400) ---
void cp_gpu_load_shader(const char * vertex_code, const char * fragment_code);
void cp_gpu_set_uniform(const char * name, float value);

#endif // CP_SDK_H
