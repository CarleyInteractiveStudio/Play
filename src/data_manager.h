#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "catalog_data.h"

/**
 * @file data_manager.h
 * @brief Gestión de datos de aplicaciones para Bare Metal.
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Inicializa los datos del sistema.
 */
void data_manager_load_data(void);

/**
 * @brief Obtiene la lista de aplicaciones instaladas.
 */
const cp_app_t* data_manager_get_apps(int* count);

/**
 * @brief Calcula el espacio usado en MB.
 */
int data_manager_get_used_storage(void);

#ifdef __cplusplus
}
#endif

#endif // DATA_MANAGER_H
