#include "carley_bridge.h"
#include "rk3128_regs.h"

void bridge_init(void)
{
    // Configurar canal de datos virtual sobre el dongle USB
}

void bridge_send(const uint8_t * data, uint32_t size)
{
    // Empaquetar y enviar por el protocolo de radio del dongle
}

uint32_t bridge_receive(uint8_t * buffer, uint32_t max_size)
{
    return 0;
}
