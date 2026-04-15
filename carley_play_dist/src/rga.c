#include "rga.h"
#include "rk3128_regs.h"

void rga_init(void)
{
    // Reset y encendido del RGA
    RK_REG(CRU_SOFTRST_CON(0)) |= (1 << 8);
    for(volatile int i=0; i<1000; i++);
    RK_REG(CRU_SOFTRST_CON(0)) &= ~(1 << 8);
}

void rga_copy(uint32_t src, uint32_t dst, uint32_t w, uint32_t h, uint32_t stride)
{
    // TODO: Implementar el envío del comando RGA para copia de bloques
    // Esto acelera dramáticamente el refresco de la pantalla.
}
