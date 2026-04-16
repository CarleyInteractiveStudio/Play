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

    /* Instalación inalámbrica real */
    if(pkt.command == SYNC_CMD_SEND_GAME) {
        fat_file_t file;
        if(fat32_create("new_game.pg") == 0) {
            fat32_write(&file, 0, pkt.length, pkt.data);
            // Actualizar catálogo dinámico
            data_manager_load_data();
        }
    }
}
