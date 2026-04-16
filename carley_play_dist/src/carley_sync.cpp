#include "carley_sync.h"
#include "usb_gamepad.h" // Supongamos que aquí está la lectura de datos USB
#include "fat32.h"
#include <string.h>

void sync_init(void)
{
    // Preparar canal de datos sobre el dongle USB 2.4G
}

void sync_process(void)
{
    sync_packet_t pkt;
    // Leer paquete del buffer USB real

    /* Ejemplo de recepción de juego */
    if(pkt.command == SYNC_CMD_SEND_GAME) {
        // Crear archivo .pg y escribir datos recibidos del PC
        fat32_create("download.pg");
        // fat32_write(...)
    }
}
