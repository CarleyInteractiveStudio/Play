/**
 * @file main.cpp
 * @brief Punto de entrada principal para "Play OS" en hardware real (Bare Metal).
 *
 * Este archivo inicializa LVGL y configura el dibujo directamente en el
 * Pantalla proporcionado por el kernel del Carley Play.
 * Compatible con LVGL v9.
 */

#include "lvgl/lvgl.h"
#include "ui.h"
#include "data_manager.h"
#include "splash.h"
#include "input_handler.h"

// --- CONFIGURACIÓN DE HARDWARE ---
#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

// --- PROTOTIPOS PARA EL KERNEL ---
extern "C" {
    void kernel_flush_area(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map);
    void kernel_init_video(void);
}

// --- FUNCIONES DE TRANSICIÓN ---
static void load_main_menu_cb(lv_timer_t * timer)
{
    lv_obj_t * main_screen = lv_obj_create(NULL);
    ui_create_game_list(main_screen);
    lv_scr_load_anim(main_screen, LV_SCR_LOAD_ANIM_FADE_OUT, 500, 0, true);
}

// --- FUNCIÓN PRINCIPAL ---
int main(void)
{
    // 1. Inicializar Hardware (Video)
    kernel_init_video();

    // 2. Inicializar LVGL
    lv_init();
    data_manager_load_data();

    // 3. Crear Pantalla (Display) para LVGL v9
    lv_display_t * disp = lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Configurar el buffer de dibujo (LVGL v9 maneja la memoria internamente o podemos pasarle una)
    // Usaremos memoria estática para Bare Metal
    static uint8_t buf1[SCREEN_WIDTH * 10 * 4]; // 10 líneas
    lv_display_set_buffers(disp, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);

    // Configurar el callback de refresco
    lv_display_set_flush_cb(disp, kernel_flush_area);

    // 4. Inicializar Entrada (Mandos)
    cp_input_init();

    // 5. Mostrar Splash Screen
    splash_show_screen();

    // 6. Temporizador para el Menú Principal
    lv_timer_t * timer = lv_timer_create(load_main_menu_cb, 3000, NULL);
    lv_timer_set_repeat_count(timer, 1);

    // 7. Bucle de ejecución infinito
    while(1) {
        lv_timer_handler();
        // En Bare Metal, el retardo depende de la implementación del kernel
        for(volatile int i = 0; i < 10000; i++);
    }

    return 0;
}
