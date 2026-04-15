/**
 * @file main.cpp
 * @brief Punto de entrada principal para "Play OS" en hardware real (Bare Metal).
 *
 * Este archivo inicializa LVGL y configura el dibujo directamente en el
 * Framebuffer proporcionado por el kernel del Carley Play.
 */

#include "lvgl/lvgl.h"
#include "ui.h"
#include "data_manager.h"
#include "splash.h"
#include "input_handler.h"

// --- CONFIGURACIÓN DE HARDWARE ---
#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720
#define DISP_BUF_SIZE (SCREEN_WIDTH * 10) // Buffer de 10 líneas

// --- PROTOTIPOS PARA EL KERNEL ---
// Estas funciones deben ser proporcionadas por el kernel o implementadas por el usuario.
extern "C" {
    void kernel_draw_pixel(int32_t x, int32_t y, lv_color_t color);
    void kernel_flush_area(int32_t x1, int32_t y1, int32_t x2, int32_t y2, lv_color_t * color_p);
    void kernel_init_video(void);
}

// --- CALLBACK DE FLUSH PARA LVGL ---
/**
 * @brief Envía los datos renderizados por LVGL al Framebuffer del hardware.
 */
static void my_disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    // Llama a la función del kernel para copiar los píxeles al buffer de video real
    kernel_flush_area(area->x1, area->y1, area->x2, area->y2, color_p);

    // Indica a LVGL que el refresco ha terminado
    lv_disp_flush_ready(disp_drv);
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

    // 3. Configurar Buffer de Pantalla
    static lv_color_t buf[DISP_BUF_SIZE];
    static lv_disp_draw_buf_t draw_buf;
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, DISP_BUF_SIZE);

    // 4. Configurar Driver de Pantalla
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = SCREEN_WIDTH;
    disp_drv.ver_res = SCREEN_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    // 4b. Inicializar Entrada (Mandos)
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
        // pero usaremos una pequeña espera si el kernel lo permite.
        for(volatile int i = 0; i < 10000; i++);
    }

    return 0;
}
