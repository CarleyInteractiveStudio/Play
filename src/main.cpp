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
#include "lv_drivers/display/sdl.h" // Usaremos el backend de SDL2.
#include <unistd.h>
#include "ui.h"                     // Incluimos nuestro propio módulo de UI.
#include "data_manager.h"           // Incluimos el gestor de datos.

// --- DEFINICIONES ---
// Las resoluciones ahora se tomarán de la configuración de SDL.
#define DISP_BUF_SIZE (128 * 1024)

// --- FUNCIÓN PRINCIPAL ---
int main(void)
{
    // 1. Inicializar la biblioteca LVGL y el gestor de datos
    lv_init();
    data_manager_load_data(); // Cargar los datos de las apps al inicio

    // 2. Inicializar SDL y los drivers de LVGL para SDL.
    // sdl_init() crea la ventana y el renderizador de SDL.
    sdl_init();

    // Crear un buffer de pantalla para LVGL
    static lv_color_t buf1[DISP_BUF_SIZE];
    static lv_color_t buf2[DISP_BUF_SIZE];
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf1, buf2, DISP_BUF_SIZE);

    // Crear un controlador de pantalla para LVGL
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;
    disp_drv.flush_cb = sdl_display_flush; // Asignamos la función de volcado de SDL.
    disp_drv.hor_res = SDL_HOR_RES;        // Usamos la resolución horizontal de SDL.
    disp_drv.ver_res = SDL_VER_RES;        // Usamos la resolución vertical de SDL.
    lv_disp_drv_register(&disp_drv);

    // Crear un controlador de entrada para el ratón/mando de SDL
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER; // SDL maneja el mando como un puntero/ratón.
    indev_drv.read_cb = sdl_mouse_read;
    lv_indev_drv_register(&indev_drv);

    // 3. Crear la interfaz de usuario principal
    lv_obj_t *scr = lv_scr_act();
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x000030), LV_PART_MAIN); // Fondo azul oscuro, estilo PS.

    // Llamamos a nuestra función para crear la lista de juegos.
    ui_create_game_list(scr);

    // 4. Bucle principal
    // Este bucle se encarga de procesar los eventos de LVGL (dibujar, leer entrada, etc.).
    while(1) {
        lv_timer_handler();
        usleep(5000); // Pequeña pausa para no consumir el 100% de la CPU.
    }

    return 0;
}