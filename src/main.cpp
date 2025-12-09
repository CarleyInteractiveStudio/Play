/**
 * @file main.cpp
 * @brief Punto de entrada principal para el sistema operativo "Play OS".
 *
 * Este archivo inicializa la biblioteca de gráficos LVGL, configura el
 * backend de SDL2 para la pantalla y la entrada, y muestra la interfaz principal.
 * Esta versión está corregida para usar SDL2, asegurando la consistencia
 * con las instrucciones de compilación.
 */

// --- INCLUDES ---
#include "lvgl/lvgl.h"
#include "lv_drivers/display/sdl.h"
#include <unistd.h>
#include "ui.h"
#include "data_manager.h"
#include "splash.h" // Incluimos la nueva pantalla de bienvenida.

// --- DEFINICIONES ---
#define DISP_BUF_SIZE (128 * 1024)

// --- FUNCIONES DE TRANSICIÓN ---

/**
 * @brief Callback del temporizador que se ejecuta después de la pantalla de bienvenida.
 *
 * Crea el menú principal y lo carga con una animación, eliminando la
 * pantalla de bienvenida anterior.
 */
static void load_main_menu_cb(lv_timer_t *timer)
{
    // Crear la pantalla del menú principal
    lv_obj_t *main_screen = lv_obj_create(NULL);
    ui_create_game_list(main_screen);

    // Cargar la nueva pantalla con una animación de fundido
    // El último parámetro 'true' asegura que la pantalla anterior (splash) se elimine.
    lv_scr_load_anim(main_screen, LV_SCR_LOAD_ANIM_FADE_OUT, 500, 0, true);
}

// --- FUNCIÓN PRINCIPAL ---
int main(void)
{
    // 1. Inicializar bibliotecas
    lv_init();
    data_manager_load_data();

    // 2. Inicializar SDL y los drivers de LVGL
    sdl_init();

    static lv_color_t buf1[DISP_BUF_SIZE];
    static lv_color_t buf2[DISP_BUF_SIZE];
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf1, buf2, DISP_BUF_SIZE);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;
    disp_drv.flush_cb = sdl_display_flush;
    disp_drv.hor_res = SDL_HOR_RES;
    disp_drv.ver_res = SDL_VER_RES;
    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = sdl_mouse_read;
    lv_indev_drv_register(&indev_drv);

    // 3. Mostrar la pantalla de bienvenida e iniciar el temporizador
    splash_show_screen();

    // Crear un temporizador de un solo uso para cambiar al menú principal después de 3 segundos
    lv_timer_t *timer = lv_timer_create(load_main_menu_cb, 3000, NULL);
    lv_timer_set_repeat_count(timer, 1);

    // 4. Bucle principal
    while(1) {
        lv_timer_handler();
        usleep(5000); // Pequeña pausa para no consumir el 100% de la CPU.
    }

    return 0;
}