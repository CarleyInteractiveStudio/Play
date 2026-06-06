#include "vpu_rk.h"
#include "rk3128_regs.h"

void vpu_init(void)
{
    // Habilitar reloj de la VPU
    RK_REG(CRU_CLKGATE_CON(1)) &= ~(1 << 1);

    // Reset del núcleo de video
}

void vpu_decode_frame(const uint8_t * bitstream, uint32_t size, uint32_t out_addr)
{
    // Cargar bitstream en registros de la VPU y disparar decodificación
}
