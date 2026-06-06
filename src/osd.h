#ifndef OSD_H
#define OSD_H

#include "lvgl/lvgl.h"

/**
 * @file osd.h
 * @brief Menú de superposición (On-Screen Display) para Carley Play.
 */

/**
 * @brief Muestra u oculta el menú OSD.
 */
void osd_toggle(void);

/**
 * @brief Inicializa las capas del OSD.
 */
void osd_init(void);

#endif // OSD_H
