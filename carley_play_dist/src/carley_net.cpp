#include "carley_net.h"
#include "carley_bridge.h"
#include <string.h>

void net_init(void)
{
    bridge_init();
    // Inicializar estructuras de control IP
}

void net_process(void)
{
    uint8_t buffer[1500];
    uint32_t len = bridge_receive(buffer, sizeof(buffer));

    if(len > 0) {
        // Analizar paquete Ethernet/IP y responder
    }
}

int net_download_file(const char * url, const char * local_path)
{
    // Enviar comando de descarga al Bridge (PC/Celular)
    // El Bridge se encarga de la parte pesada de Internet
    return 0;
}
