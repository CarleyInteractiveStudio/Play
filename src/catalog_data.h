#ifndef CATALOG_DATA_H
#define CATALOG_DATA_H

/**
 * @file catalog_data.h
 * @brief Datos embebidos para los juegos de Carley Play.
 *
 * En un sistema Bare Metal sin SD/FS, los datos se incluyen en el código.
 */

typedef struct {
    const char* name;
    const char* developer;
    int size_mb;
    bool installed;
} cp_app_t;

#define MAX_APPS 10

static const cp_app_t embedded_apps[MAX_APPS] = {
    {"Aventura Espacial", "Estudio Galáctico", 120, true},
    {"Héroe del Reino", "Pixel Art Games", 85, true},
    {"Carreras Turbo", "Speed Masters", 210, true},
    {"Misterio en el Bosque", "Indie Dev", 45, true},
    {"Puzzle Maestro", "Logic Studio", 15, true},
    {"Laberinto Infinito", "Fun Factory", 30, true},
    {"Zombies Attack", "Dead Games", 180, true},
    {"Fútbol 2D", "Sport Sim", 55, true},
    {"Base de Datos de Consola", "System Tools", 5, true},
    {"Game Store", "Play OS Team", 25, true}
};

#endif // CATALOG_DATA_H
