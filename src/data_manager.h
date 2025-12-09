/**
 * @file data_manager.h
 * @brief Declaraciones para el gestor de datos de aplicaciones.
 *
 * Este módulo se encarga de cargar, gestionar y guardar la lista de
 * aplicaciones desde y hacia el archivo `catalog.json`.
 */

#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <string>
#include <vector>

// Estructura para almacenar los datos de una aplicación.
struct AppData {
    std::string name;
    std::string description;
    std::string version;
    std::string author;
    std::string url;
    std::string icon;
    float size_mb; // Tamaño en megabytes para el cálculo de almacenamiento.
};

// --- FUNCIONES PÚBLICAS ---

/**
 * @brief Carga los datos de las aplicaciones desde el archivo catalog.json.
 *
 * Debe llamarse una vez al inicio del programa.
 * @return true si la carga fue exitosa, false en caso contrario.
 */
bool data_manager_load_data();

/**
 * @brief Obtiene la lista de todas las aplicaciones cargadas.
 *
 * @return Una referencia constante al vector de aplicaciones.
 */
const std::vector<AppData>& data_manager_get_apps();

/**
 * @brief Elimina una aplicación de la lista por su índice.
 *
 * @param index El índice de la aplicación a eliminar.
 */
void data_manager_delete_app(int index);

/**
 * @brief Guarda el estado actual de la lista de aplicaciones en catalog.json.
 *
 * @return true si el guardado fue exitoso, false en caso contrario.
 */
bool data_manager_save_data();

#endif // DATA_MANAGER_H