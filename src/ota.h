#ifndef OTA_H
#define OTA_H

#include <stdint.h>

/**
 * @file ota.h
 * @brief Sistema de actualización Over-The-Air para Carley Play.
 */

/**
 * @brief Inicia la descarga y grabación de un nuevo firmware.
 */
void ota_update_system(const char * update_url);

#endif // OTA_H
