#include "rga.h"
#include "rk3128_regs.h"

/**
 * @file rga.c
 * @brief Driver del motor de aceleración 2D (RGA) del RK3128.
 */

#define RGA_STATUS        (RGA_BASE + 0x0000)
#define RGA_CMD_BASE      (RGA_BASE + 0x0004)
#define RGA_CTRL          (RGA_BASE + 0x0008)

void rga_init(void)
{
    // Encender reloj RGA
    RK_REG(CRU_CLKGATE_CON(1)) &= ~(1 << 8);

    // Reset core
    RK_REG(CRU_SOFTRST_CON(0)) |= (1 << 8);
    for(volatile int i=0; i<1000; i++);
    RK_REG(CRU_SOFTRST_CON(0)) &= ~(1 << 8);
}

void rga_copy(uint32_t src, uint32_t dst, uint32_t w, uint32_t h, uint32_t stride)
{
    // Configurar registros de origen y destino
    RK_REG(RGA_BASE + 0x0010) = src;
    RK_REG(RGA_BASE + 0x0014) = dst;
    RK_REG(RGA_BASE + 0x0018) = (w << 16) | h;
    RK_REG(RGA_BASE + 0x001c) = stride;

    // Disparar comando de BitBLT (Copia de bloque)
    RK_REG(RGA_CTRL) = 0x1;

    // Esperar a que RGA termine
    while(RK_REG(RGA_STATUS) & 0x1);
}
