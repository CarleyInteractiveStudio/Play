#ifndef CARLEY_NET_H
#define CARLEY_NET_H

#include <stdint.h>

/**
 * @file carley_net.h
 * @brief Pila de red virtual para Carley Play a través de USB (Carley Bridge).
 *
 * Como el hardware no tiene WiFi, usamos el puente USB para obtener red.
 */

/**
 * @brief Inicializa la pila de red TCP/IP.
 */
void net_init(void);

/**
 * @brief Procesa los paquetes entrantes de la red.
 */
void net_process(void);

/**
 * @brief Descarga un archivo desde una URL (Simulado sobre el puente).
 */
int net_download_file(const char * url, const char * local_path);

#endif // CARLEY_NET_H
