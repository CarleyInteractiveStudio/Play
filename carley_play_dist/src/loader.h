#ifndef LOADER_H
#define LOADER_H

#include <stdint.h>

/**
 * @file loader.h
 * @brief Cargador de binarios y ejecución de juegos para Carley Play.
 */

/**
 * @brief Carga un binario desde la SD a la RAM y lo ejecuta.
 * @param lba Sector de inicio en la SD.
 * @param size_sectors Tamaño del juego en sectores.
 * @param load_addr Dirección de memoria donde cargar (ej: 0x02000000).
 */
void loader_run_game(uint32_t lba, uint32_t size_sectors, uint32_t load_addr);

#endif // LOADER_H
